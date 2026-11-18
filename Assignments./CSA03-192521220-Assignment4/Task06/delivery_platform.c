#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 131071
#define MAX_ORDERS 105000

typedef struct Order {
    int order_id;
    int restaurant_id;
    int amount;
    int deadline;
    int heap_idx;
    int cancelled;
    struct Order *next;
} Order;

Order *hash_table[TABLE_SIZE];
Order *heap[MAX_ORDERS];
int heap_size = 0;

unsigned hash_id(int id) {
    return ((unsigned)id * 2654435761u) % TABLE_SIZE;
}

void heap_swap(int i, int j) {
    Order *tmp = heap[i];
    heap[i] = heap[j];
    heap[j] = tmp;
    heap[i]->heap_idx = i;
    heap[j]->heap_idx = j;
}

void sift_up(int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[i]->deadline < heap[p]->deadline) {
            heap_swap(i, p);
            i = p;
        } else break;
    }
}

void sift_down(int i) {
    for (;;) {
        int l = 2 * i + 1, r = 2 * i + 2, s = i;
        if (l < heap_size && heap[l]->deadline < heap[s]->deadline) s = l;
        if (r < heap_size && heap[r]->deadline < heap[s]->deadline) s = r;
        if (s != i) {
            heap_swap(i, s);
            i = s;
        } else break;
    }
}

void place_order(Order *o) {
    unsigned b = hash_id(o->order_id);
    o->next = hash_table[b];
    hash_table[b] = o;

    o->heap_idx = heap_size;
    heap[heap_size++] = o;
    sift_up(o->heap_idx);
}

Order *lookup_order(int order_id) {
    unsigned b = hash_id(order_id);
    for (Order *curr = hash_table[b]; curr; curr = curr->next) {
        if (curr->order_id == order_id) return curr;
    }
    return NULL;
}

void cancel_order(int order_id) {
    Order *o = lookup_order(order_id);
    if (!o || o->cancelled || o->heap_idx == -1) return;
    o->cancelled = 1;
    int idx = o->heap_idx;
    heap_swap(idx, --heap_size);
    o->heap_idx = -1;
    if (idx < heap_size) {
        sift_up(idx);
        sift_down(idx);
    }
}

Order *assign_next_rider(void) {
    if (heap_size == 0) return NULL;
    Order *urgent = heap[0];
    heap_swap(0, --heap_size);
    urgent->heap_idx = -1;
    if (heap_size > 0) sift_down(0);
    return urgent;
}

int cmp_report(const Order *a, const Order *b) {
    if (a->restaurant_id != b->restaurant_id)
        return a->restaurant_id - b->restaurant_id;
    return a->amount - b->amount;
}

void merge_report(Order **arr, Order **tmp, int lo, int mid, int hi) {
    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
        if (cmp_report(arr[i], arr[j]) <= 0) tmp[k++] = arr[i++];
        else tmp[k++] = arr[j++];
    }
    while (i <= mid) tmp[k++] = arr[i++];
    while (j <= hi) tmp[k++] = arr[j++];
    for (int idx = lo; idx <= hi; idx++) arr[idx] = tmp[idx];
}

void sort_report(Order **arr, Order **tmp, int lo, int hi) {
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;
    sort_report(arr, tmp, lo, mid);
    sort_report(arr, tmp, mid + 1, hi);
    merge_report(arr, tmp, lo, mid, hi);
}

void run_simulation(int n_orders) {
    memset(hash_table, 0, sizeof(hash_table));
    heap_size = 0;

    Order *pool = malloc(sizeof(Order) * n_orders);
    Order **report_list = malloc(sizeof(Order *) * n_orders);
    Order **tmp_list = malloc(sizeof(Order *) * n_orders);
    srand(42);

    clock_t t0 = clock();
    for (int i = 0; i < n_orders; i++) {
        pool[i].order_id = 100000 + i;
        pool[i].restaurant_id = rand() % 500;
        pool[i].amount = 100 + (rand() % 1900);
        pool[i].deadline = 1000 + (rand() % 3600);
        pool[i].cancelled = 0;
        place_order(&pool[i]);
        report_list[i] = &pool[i];
    }
    clock_t t1 = clock();

    for (int i = 0; i < n_orders; i++) {
        volatile Order *found = lookup_order(100000 + (rand() % n_orders));
        (void)found;
    }
    clock_t t2 = clock();

    int cancels = n_orders / 20;
    for (int i = 0; i < cancels; i++) {
        cancel_order(100000 + (i * 17) % n_orders);
    }
    clock_t t3 = clock();

    int assigned = 0;
    while (heap_size > 0) {
        assign_next_rider();
        assigned++;
    }
    clock_t t4 = clock();

    sort_report(report_list, tmp_list, 0, n_orders - 1);
    clock_t t5 = clock();

    printf("=== Simulation Load: %d Orders ===\n", n_orders);
    printf("Place %d orders:      %.3f ms\n", n_orders, 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
    printf("Lookup %d orders:     %.3f ms\n", n_orders, 1000.0 * (t2 - t1) / CLOCKS_PER_SEC);
    printf("Cancel %d orders:      %.3f ms\n", cancels, 1000.0 * (t3 - t2) / CLOCKS_PER_SEC);
    printf("Assign %d riders:     %.3f ms\n", assigned, 1000.0 * (t4 - t3) / CLOCKS_PER_SEC);
    printf("Hourly Merge Report:   %.3f ms\n\n", 1000.0 * (t5 - t4) / CLOCKS_PER_SEC);

    free(pool);
    free(report_list);
    free(tmp_list);
}

int main(void) {
    run_simulation(50000);
    run_simulation(100000);
    return 0;
}
