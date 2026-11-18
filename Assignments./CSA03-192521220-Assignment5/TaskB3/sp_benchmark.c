#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define INF 1000000000

typedef struct Edge {
    int to, weight;
    struct Edge *next;
} Edge;

typedef struct {
    int node, dist;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
} MinHeap;

void push(MinHeap *h, int node, int dist) {
    int i = h->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->data[p].dist <= dist) break;
        h->data[i] = h->data[p];
        i = p;
    }
    h->data[i].node = node;
    h->data[i].dist = dist;
}

HeapNode pop(MinHeap *h) {
    HeapNode top = h->data[0];
    HeapNode last = h->data[--h->size];
    int i = 0;
    while (2 * i + 1 < h->size) {
        int l = 2 * i + 1, r = l + 1, s = l;
        if (r < h->size && h->data[r].dist < h->data[l].dist) s = r;
        if (last.dist <= h->data[s].dist) break;
        h->data[i] = h->data[s];
        i = s;
    }
    if (h->size > 0) h->data[i] = last;
    return top;
}

void dijkstra_heap(int V, Edge **adj, int src, int *dist) {
    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[src] = 0;
    MinHeap h;
    h.data = malloc(sizeof(HeapNode) * (V * 4 + 10));
    h.size = 0;
    push(&h, src, 0);

    while (h.size > 0) {
        HeapNode curr = pop(&h);
        int u = curr.node;
        if (curr.dist > dist[u]) continue;
        for (Edge *e = adj[u]; e != NULL; e = e->next) {
            if (dist[u] + e->weight < dist[e->to]) {
                dist[e->to] = dist[u] + e->weight;
                push(&h, e->to, dist[e->to]);
            }
        }
    }
    free(h.data);
}

int main(void) {
    int sizes[] = {100, 1000, 10000};
    srand(42);

    printf("V\tHeap Dijkstra (ms)\n");
    for (int s = 0; s < 3; s++) {
        int V = sizes[s];
        Edge **adj = calloc(V, sizeof(Edge *));
        for (int u = 0; u < V; u++) {
            for (int k = 0; k < 3; k++) {
                int v = rand() % V;
                if (u != v) {
                    Edge *e = malloc(sizeof(Edge));
                    e->to = v;
                    e->weight = 1 + rand() % 20;
                    e->next = adj[u];
                    adj[u] = e;
                }
            }
        }

        int *dist = malloc(sizeof(int) * V);
        clock_t start = clock();
        dijkstra_heap(V, adj, 0, dist);
        clock_t end = clock();
        double ms = 1000.0 * (end - start) / CLOCKS_PER_SEC;
        printf("%d\t%.3f ms\n", V, ms);

        free(dist);
        for (int u = 0; u < V; u++) {
            Edge *curr = adj[u];
            while (curr) {
                Edge *tmp = curr;
                curr = curr->next;
                free(tmp);
            }
        }
        free(adj);
    }
    return 0;
}
