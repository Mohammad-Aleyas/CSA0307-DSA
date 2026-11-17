#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define N 100000
#define M 131071
#define OLD_M 1000

static unsigned poor_hash(const char *s) { return ((unsigned char)s[0] + (unsigned char)s[1]) % OLD_M; }
static unsigned poly_hash(const char *s) {
    uint32_t h = 0;
    while (*s) h = h * 31u + (unsigned char)*s++;
    return h % M;
}
static unsigned fnv1a(const char *s) {
    uint32_t h = 2166136261u;
    while (*s) { h ^= (unsigned char)*s++; h *= 16777619u; }
    return h % M;
}
static void make_reg(char *s, unsigned i) {
    /* Deterministic synthetic TN registrations: two-letter series + four digits. */
    unsigned x = i;
    s[0]='T'; s[1]='N'; s[2]='0'; s[3]='9';
    s[4]=(char)('A'+(x/260000)%26); s[5]=(char)('A'+(x/10000)%26);
    s[6]=(char)('0'+(x/1000)%10); s[7]=(char)('0'+(x/100)%10);
    s[8]=(char)('0'+(x/10)%10); s[9]=(char)('0'+x%10); s[10]='\0';
}
static void measure(unsigned (*hf)(const char *), unsigned mod, const char *label) {
    unsigned *counts = calloc(mod, sizeof(*counts));
    char s[16];
    for (unsigned i=0;i<N;i++) { make_reg(s,i); counts[hf(s)]++; }
    unsigned longest=0, used=0; unsigned long total=0;
    for (unsigned i=0;i<mod;i++) if(counts[i]) { used++; total+=counts[i]; if(counts[i]>longest)longest=counts[i]; }
    printf("%s: buckets=%u used=%u longest_chain=%u average_nonempty_chain=%.3f average_per_bucket=%.3f\n",
           label,mod,used,longest,used?(double)total/used:0.0,(double)total/mod);
    free(counts);
}
static unsigned poly_adapter(const char *s) { return poly_hash(s); }
static unsigned fnv_adapter(const char *s) { return fnv1a(s); }
int main(void) {
    measure(poor_hash,OLD_M,"Poor state-only hash");
    measure(poly_adapter,M,"Polynomial hash");
    measure(fnv_adapter,M,"FNV-1a hash");
    return 0;
}
