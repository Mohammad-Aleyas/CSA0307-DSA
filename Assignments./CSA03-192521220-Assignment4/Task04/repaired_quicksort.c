#include <stdio.h>
#include <stdlib.h>

long comparisons = 0;
int max_depth = 0;

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int median_of_three(int a[], int lo, int hi) {
    int mid = lo + (hi - lo) / 2;
    if (a[mid] < a[lo]) swap(&a[lo], &a[mid]);
    if (a[hi] < a[lo]) swap(&a[lo], &a[hi]);
    if (a[mid] < a[hi]) swap(&a[mid], &a[hi]);
    return a[hi];
}

void repaired_quick(int a[], int lo, int hi, int depth) {
    while (lo < hi) {
        if (depth > max_depth) max_depth = depth;
        int p = median_of_three(a, lo, hi);
        int i = lo - 1;
        for (int j = lo; j < hi; j++) {
            comparisons++;
            if (a[j] <= p) {
                i++;
                swap(&a[i], &a[j]);
            }
        }
        swap(&a[i + 1], &a[hi]);
        int pivot_idx = i + 1;

        /* Recurse on smaller half first, loop on larger half to guarantee O(log n) stack */
        if (pivot_idx - lo < hi - pivot_idx) {
            repaired_quick(a, lo, pivot_idx - 1, depth + 1);
            lo = pivot_idx + 1;
        } else {
            repaired_quick(a, pivot_idx + 1, hi, depth + 1);
            hi = pivot_idx - 1;
        }
    }
}

int main(void) {
    int n = 10000;
    int *sorted = malloc(sizeof(int) * n);
    int *random = malloc(sizeof(int) * n);
    srand(42);

    for (int i = 0; i < n; i++) {
        sorted[i] = i;
        random[i] = rand() % 101;
    }

    comparisons = 0;
    max_depth = 0;
    repaired_quick(sorted, 0, n - 1, 1);
    printf("Repaired Quicksort (10,000 sorted): comparisons = %ld, max stack depth = %d\n",
           comparisons, max_depth);

    comparisons = 0;
    max_depth = 0;
    repaired_quick(random, 0, n - 1, 1);
    printf("Repaired Quicksort (10,000 random): comparisons = %ld, max stack depth = %d\n",
           comparisons, max_depth);

    free(sorted);
    free(random);
    return 0;
}
