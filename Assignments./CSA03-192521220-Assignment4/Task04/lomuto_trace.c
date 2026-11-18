#include <stdio.h>

int main(void) {
    int a[] = {7, 2, 9, 4, 3, 8, 5};
    int n = 7, pivot = a[n - 1], i = -1, swaps = 0;

    for (int j = 0; j < n - 1; j++) {
        if (a[j] <= pivot) {
            i++;
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
            swaps++;
        }
    }
    int t = a[i + 1];
    a[i + 1] = a[n - 1];
    a[n - 1] = t;

    for (int k = 0; k < n; k++) printf("%d ", a[k]);
    printf("| pivot at %d, swaps %d\n", i + 1, swaps);
    return 0;
}
