#include <stdio.h>

#define M 10

int main(void) {
    int table[M];
    for (int i = 0; i < M; i++) table[i] = -1;

    int keys[] = {42, 17, 52, 27, 99, 62};
    for (int k = 0; k < 6; k++) {
        int i = keys[k] % M, probes = 1;
        while (table[i] != -1) {
            i = (i + 1) % M;
            probes++;
        }
        table[i] = keys[k];
        printf("%d@%d(%d) ", keys[k], i, probes);
    }
    printf("\n");
    return 0;
}
