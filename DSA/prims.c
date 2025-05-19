#include <stdio.h>
#include <stdbool.h>
#define MAX 20
#define INF 9999

int n; // number of vertices

// Find vertex with minimum key value not yet included in MST
int minKey(int key[], bool mstSet[]) {
    int min = INF, minIndex = -1;
    for (int v = 0; v < n; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Print MST stored in parent[]
void printMST(int parent[], int graph[MAX][MAX]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++)
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
}

// Prim's algorithm
void primMST(int graph[MAX][MAX]) {
    int parent[MAX];    // Store MST
    int key[MAX];       // Key values used to pick minimum edge
    bool mstSet[MAX];   // To represent set of vertices included in MST

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }

    key[0] = 0;      // Start from first vertex
    parent[0] = -1;  // First node is root of MST

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph);
}

int main() {
    int graph[MAX][MAX];
    int edges, u, v, w;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v weight):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;  // Since undirected graph
    }

    printf("\nMinimum Spanning Tree (Prim's Algorithm):\n");
    primMST(graph);

    return 0;
}