#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKETS 7

typedef struct Member {
    char id[12];
    char name[20];
    struct Member *next;
} Member;

Member *table[BUCKETS];

unsigned hash(const char *s) {
    unsigned h = 0;
    while (*s) h = h * 31 + (unsigned char)*s++;
    return h % BUCKETS;
}

void put(const char *id, const char *name) {
    unsigned b = hash(id);
    Member *m = malloc(sizeof(Member));
    if (!m) return;
    strncpy(m->id, id, sizeof(m->id) - 1);
    m->id[sizeof(m->id) - 1] = '\0';
    strncpy(m->name, name, sizeof(m->name) - 1);
    m->name[sizeof(m->name) - 1] = '\0';
    m->next = table[b];
    table[b] = m;
}

const char *get(const char *id, int *probes) {
    *probes = 0;
    unsigned b = hash(id);
    for (Member *curr = table[b]; curr != NULL; curr = curr->next) {
        (*probes)++;
        if (strcmp(curr->id, id) == 0) {
            return curr->name;
        }
    }
    return NULL;
}

int main(void) {
    const char *ids[] = {"CSE1043", "ECE2210", "MEC3307",
                         "CSE1044", "BME4120", "CIV5009"};
    const char *names[] = {"Kavya", "Arjun", "Fathima", "Rahul", "Deepa", "Manoj"};

    for (int i = 0; i < 6; i++) put(ids[i], names[i]);

    for (int b = 0; b < BUCKETS; b++) {
        int len = 0;
        for (Member *m = table[b]; m; m = m->next) len++;
        printf("%d", len);
    }

    int p;
    const char *who = get("CSE1044", &p);
    printf("\nCSE1044 -> %s (%d probes)\n", who ? who : "not found", p);
    who = get("CSE9999", &p);
    printf("CSE9999 -> %s (%d probes)\n", who ? who : "not found", p);

    for (int b = 0; b < BUCKETS; b++) {
        while (table[b]) {
            Member *n = table[b]->next;
            free(table[b]);
            table[b] = n;
        }
    }
    return 0;
}
