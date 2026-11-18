#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#define N 10000000
#define TASK_THRESHOLD 10000

void merge(int *a, int *tmp, int lo, int mid, int hi) {
    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else tmp[k++] = a[j++];
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= hi) tmp[k++] = a[j++];
    for (int idx = lo; idx <= hi; idx++) a[idx] = tmp[idx];
}

void parallel_msort(int *a, int *tmp, int lo, int hi) {
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;

#ifdef _OPENMP
    if (hi - lo >= TASK_THRESHOLD) {
        #pragma omp task shared(a, tmp)
        parallel_msort(a, tmp, lo, mid);
        #pragma omp task shared(a, tmp)
        parallel_msort(a, tmp, mid + 1, hi);
        #pragma omp taskwait
    } else
#endif
    {
        parallel_msort(a, tmp, lo, mid);
        parallel_msort(a, tmp, mid + 1, hi);
    }
    merge(a, tmp, lo, mid, hi);
}

int main(void) {
    int *base = malloc(sizeof(int) * N);
    int *arr = malloc(sizeof(int) * N);
    int *tmp = malloc(sizeof(int) * N);

    srand(42);
    for (int i = 0; i < N; i++) base[i] = rand();

    int threads[] = {1, 2, 4, 8};
    for (int t = 0; t < 4; t++) {
        for (int i = 0; i < N; i++) arr[i] = base[i];
#ifdef _OPENMP
        omp_set_num_threads(threads[t]);
        double t0 = omp_get_wtime();
        #pragma omp parallel
        {
            #pragma omp single
            parallel_msort(arr, tmp, 0, N - 1);
        }
        double t1 = omp_get_wtime();
        printf("Threads: %d | Time: %.4f s\n", threads[t], t1 - t0);
#else
        clock_t t0 = clock();
        parallel_msort(arr, tmp, 0, N - 1);
        clock_t t1 = clock();
        printf("Threads: %d (Sequential fallback) | Time: %.4f s\n",
               threads[t], (double)(t1 - t0) / CLOCKS_PER_SEC);
#endif
    }

    free(base);
    free(arr);
    free(tmp);
    return 0;
}
