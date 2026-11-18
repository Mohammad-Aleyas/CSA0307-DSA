#include <stdio.h>

#define V 6

int g[V][V] = {
    {0, 1, 1, 0, 0, 0},
    {1, 0, 0, 1, 1, 0},
    {1, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 1},
    {0, 1, 1, 0, 0, 1},
    {0, 0, 0, 1, 1, 0}
};

void bfs(int start) {
    int visited[V] = {0};
    int queue[V];
    int head = 0, tail = 0;

    visited[start] = 1;
    queue[tail++] = start;

    while (head < tail) {
        int u = queue[head++];
        printf("%d ", u);
        for (int v = 0; v < V; v++) {
            if (g[u][v] && !visited[v]) {
                visited[v] = 1;
                queue[tail++] = v;
            }
        }
    }
    printf("\n");
}

int main(void) {
    bfs(0);
    return 0;
}
