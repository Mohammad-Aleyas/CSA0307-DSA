#include <stdio.h>

void sift_down(int a[], int n, int i) {
    for (;;) {
        int l = 2 * i + 1, r = l + 1, s = i;
        if (l < n && a[l] < a[s]) s = l;
        if (r < n && a[r] < a[s]) s = r;
        if (s == i) return;
        int t = a[i];
        a[i] = a[s];
        a[s] = t;
        i = s;
    }
}

int main(void) {
    int a[] = {9, 4, 7, 1, 8, 2, 6};
    int n = 7;
    for (int i = n / 2 - 1; i >= 0; i--) sift_down(a, n, i);
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}
