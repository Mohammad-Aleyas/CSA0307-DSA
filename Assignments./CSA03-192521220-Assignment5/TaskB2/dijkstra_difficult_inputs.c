#include <stdio.h>
#include <limits.h>

#define INF 1000000000

void test_unreachable(void) {
    int V = 4;
    int w[4][4] = {
        {0, 5, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 2},
        {0, 0, 0, 0}
    };
    int dist[4] = {0, INF, INF, INF}, done[4] = {0};
    for (int r = 0; r < V; r++) {
        int u = -1;
        for (int v = 0; v < V; v++)
            if (!done[v] && dist[v] < INF && (u == -1 || dist[v] < dist[u])) u = v;
        if (u == -1) break;
        done[u] = 1;
        for (int v = 0; v < V; v++)
            if (w[u][v] > 0 && !done[v] && dist[u] + w[u][v] < dist[v])
                dist[v] = dist[u] + w[u][v];
    }
    printf("[Test 1 - Unreachable] Node 3 distance: %s\n",
           dist[3] == INF ? "UNREACHABLE" : "REACHABLE");
}

void test_negative_edge(void) {
    /* 0 -> 1 (cost 5), 0 -> 2 (cost 2), 1 -> 2 (cost -10) */
    int V = 3;
    int w[3][3] = {
        {0, 5, 2},
        {0, 0, -10},
        {0, 0, 0}
    };
    int dist[3] = {0, INF, INF}, done[3] = {0};
    for (int r = 0; r < V; r++) {
        int u = -1;
        for (int v = 0; v < V; v++)
            if (!done[v] && dist[v] < INF && (u == -1 || dist[v] < dist[u])) u = v;
        if (u == -1) break;
        done[u] = 1;
        for (int v = 0; v < V; v++)
            if (w[u][v] != 0 && !done[v] && dist[u] + w[u][v] < dist[v])
                dist[v] = dist[u] + w[u][v];
    }
    printf("[Test 2 - Negative Edge] Dijkstra dist[2] = %d (True shortest via 0->1->2 = -5)\n", dist[2]);
}

void test_overflow_prevention(void) {
    int d_u = INT_MAX - 10;
    int weight = 50;
    int d_v = INT_MAX;
    if (d_u <= INT_MAX - weight && d_u + weight < d_v) {
        d_v = d_u + weight;
    }
    printf("[Test 3 - Overflow Guard] Safe check prevented signed overflow (d_v = %d)\n", d_v);
}

int main(void) {
    test_unreachable();
    test_negative_edge();
    test_overflow_prevention();
    return 0;
}
