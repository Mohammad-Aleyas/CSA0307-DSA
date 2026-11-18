#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_RECORDS 100000
#define POOR_BUCKETS 1000
#define GOOD_BUCKETS 131071

unsigned poor_hash(const char *reg) {
    return (unsigned)(reg[0] + reg[1]) % POOR_BUCKETS;
}

unsigned poly_hash(const char *reg) {
    unsigned h = 0;
    while (*reg) {
        h = h * 31u + (unsigned char)(*reg++);
    }
    return h % GOOD_BUCKETS;
}

unsigned fnv1a_hash(const char *reg) {
    unsigned h = 2166136261u;
    while (*reg) {
        h ^= (unsigned char)(*reg++);
        h *= 16777619u;
    }
    return h % GOOD_BUCKETS;
}

void measure_distribution(const char *label, unsigned (*fn)(const char *), int buckets, char regs[][12]) {
    int *counts = calloc(buckets, sizeof(int));
    for (int i = 0; i < NUM_RECORDS; i++) {
        counts[fn(regs[i])]++;
    }

    int max_chain = 0;
    int non_empty = 0;
    for (int b = 0; b < buckets; b++) {
        if (counts[b] > 0) {
            non_empty++;
            if (counts[b] > max_chain) max_chain = counts[b];
        }
    }
    double avg_non_empty = non_empty > 0 ? (double)NUM_RECORDS / non_empty : 0.0;
    printf("%-22s | Buckets: %6d | Max Chain: %6d | Avg Chain (non-empty): %.2f\n",
           label, buckets, max_chain, avg_non_empty);
    free(counts);
}

int main(void) {
    static char regs[NUM_RECORDS][12];
    const char *states[] = {"TN", "KA", "KL", "AP", "MH"};
    srand(42);

    for (int i = 0; i < NUM_RECORDS; i++) {
        /* 80% registered in TN to simulate realistic regional skew */
        const char *st = (rand() % 10 < 8) ? "TN" : states[rand() % 5];
        snprintf(regs[i], sizeof(regs[i]), "%s%02d%c%c%04d",
                 st, rand() % 99 + 1, 'A' + rand() % 26, 'A' + rand() % 26, rand() % 10000);
    }

    printf("=== Hash Function Benchmark (%d Registrations) ===\n", NUM_RECORDS);
    measure_distribution("Poor 2-Char Hash", poor_hash, POOR_BUCKETS, regs);
    measure_distribution("Polynomial Rolling", poly_hash, GOOD_BUCKETS, regs);
    measure_distribution("FNV-1a Hash", fnv1a_hash, GOOD_BUCKETS, regs);
    return 0;
}
