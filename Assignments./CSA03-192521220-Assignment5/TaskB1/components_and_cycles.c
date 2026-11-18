#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int v;
    struct Node *next;
} Node;

typedef struct {
    int V;
    Node **adj;
} Graph;

Graph *create_graph(int V) {
    Graph *g = malloc(sizeof(Graph));
    g->V = V;
    g->adj = calloc(V, sizeof(Node *));
    return g;
}

void add_edge(Graph *g, int u, int v) {
    Node *n1 = malloc(sizeof(Node));
    n1->v = v;
    n1->next = g->adj[u];
    g->adj[u] = n1;

    Node *n2 = malloc(sizeof(Node));
    n2->v = u;
    n2->next = g->adj[v];
    g->adj[v] = n2;
}

int dfs_cycle(Graph *g, int u, int parent, int *vis) {
    vis[u] = 1;
    for (Node *curr = g->adj[u]; curr != NULL; curr = curr->next) {
        int v = curr->v;
        if (!vis[v]) {
            if (dfs_cycle(g, v, u, vis)) return 1;
        } else if (v != parent) {
            return 1;
        }
    }
    return 0;
}

void free_graph(Graph *g) {
    for (int i = 0; i < g->V; i++) {
        Node *curr = g->adj[i];
        while (curr) {
            Node *tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}

int main(void) {
    int V = 6;
    Graph *g = create_graph(V);
    /* Remaining roads after flood closes bridges between {0,1,2} and {3,4,5} */
    add_edge(g, 0, 1);
    add_edge(g, 1, 2);
    add_edge(g, 2, 0); /* Cycle in component 1 */
    add_edge(g, 3, 4);
    add_edge(g, 4, 5);

    int *vis = calloc(V, sizeof(int));
    int components = 0;
    int has_cycle = 0;

    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            components++;
            if (dfs_cycle(g, i, -1, vis)) {
                has_cycle = 1;
            }
        }
    }

    printf("Connected Regions after flood: %d\n", components);
    printf("Cycle detected in network: %s\n", has_cycle ? "Yes" : "No");

    free(vis);
    free_graph(g);
    return 0;
}
