#include <stdio.h>

#define MAX 32

typedef struct {
    int severity;
    int patient;
} Case; /* higher = more urgent */

Case heap[MAX];
int size = 0;

void swap(Case *a, Case *b) {
    Case t = *a;
    *a = *b;
    *b = t;
}

void push(int severity, int patient) {
    if (size == MAX) return;
    heap[size] = (Case){severity, patient};
    int i = size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent].severity < heap[i].severity) {
            swap(&heap[parent], &heap[i]);
            i = parent;
        } else {
            break;
        }
    }
}

Case pop(void) {
    Case top = heap[0];
    heap[0] = heap[--size];
    int i = 0;
    for (;;) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if (left < size && heap[left].severity > heap[largest].severity) largest = left;
        if (right < size && heap[right].severity > heap[largest].severity) largest = right;
        if (largest != i) {
            swap(&heap[i], &heap[largest]);
            i = largest;
        } else {
            break;
        }
    }
    return top;
}

int main(void) {
    int sev[] = {3, 9, 5, 7, 1, 8};
    for (int p = 0; p < 6; p++) push(sev[p], 101 + p);

    while (size) {
        Case c = pop();
        printf("P%d(%d) ", c.patient, c.severity);
    }
    printf("\n");
    return 0;
}
