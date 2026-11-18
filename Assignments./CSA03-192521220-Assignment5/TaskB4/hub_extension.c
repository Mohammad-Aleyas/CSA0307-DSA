#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define HUBS 20
#define INF 1000000

int run_prim(int cost[HUBS][HUBS], int print_edges) {
    int key[HUBS], parent[HUBS], in_mst[HUBS] = {0};
    for (int i = 0; i < HUBS; i++) {
        key[i] = INF;
        parent[i] = -1;
    }
    key[0] = 0;
    int total = 0;

    for (int count = 0; count < HUBS; count++) {
        int u = -1;
        for (int v = 0; v < HUBS; v++) {
            if (!in_mst[v] && (u == -1 || key[v] < key[u])) u = v;
        }
        if (u == -1 || key[u] == INF) return -1;
        in_mst[u] = 1;
        total += key[u];

        for (int v = 0; v < HUBS; v++) {
            if (!in_mst[v] && cost[u][v] > 0 && cost[u][v] < key[v]) {
                key[v] = cost[u][v];
                parent[v] = u;
            }
        }
    }

    if (print_edges) {
        for (int v = 1; v < HUBS; v++) {
            printf("Hub %02d -- Hub %02d (Cost: %d lakh)\n", parent[v], v, cost[parent[v]][v]);
        }
    }
    return total;
}

int main(void) {
    int cost[HUBS][HUBS] = {0};
    srand(108);

    /* Generate connected 20-hub inter-city backbone candidates */
    for (int i = 0; i < HUBS - 1; i++) {
        int w = 4 + (rand() % 10);
        cost[i][i + 1] = cost[i + 1][i] = w;
    }
    for (int i = 0; i < HUBS; i++) {
        for (int j = i + 2; j < HUBS; j++) {
            if (rand() % 4 == 0) {
                int w = 6 + (rand() % 15);
                cost[i][j] = cost[j][i] = w;
            }
        }
    }

    printf("=== Primary 20-Hub Fibre Cabling Plan ===\n");
    int initial_cost = run_prim(cost, 1);
    printf("Total Primary Cabling Cost: %d Rs lakh\n\n", initial_cost);

    /* Simulate fibre link outage between Hub 0 and Hub 1 */
    int backup_w = cost[0][1];
    cost[0][1] = cost[1][0] = 0;
    printf("=== Rerouted Plan After Link (0-1, cost %d) Outage ===\n", backup_w);
    int new_cost = run_prim(cost, 0);
    printf("Total Rerouted Cabling Cost: %d Rs lakh (+%d lakh delta)\n",
           new_cost, new_cost - initial_cost);

    return 0;
}
