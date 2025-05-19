#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct {
    int u, v, w;
} Edge;

int parent[MAX];
int n, edges;

// Find set of an element i (with path compression)
int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

// Union of two sets x and y
void unionSet(int x, int y) {
    int xset = find(x);
    int yset = find(y);
    parent[yset] = xset;
}

// Comparator for qsort to sort edges by weight
int cmp(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->w - e2->w;
}

void kruskal(Edge edgeList[]) {
    int count = 0, i = 0;
    printf("Edges in MST:\n");
    while (count < n - 1 && i < edges) {
        Edge current = edgeList[i++];
        int setU = find(current.u);
        int setV = find(current.v);

        if (setU != setV) {
            printf("%d - %d : %d\n", current.u, current.v, current.w);
            unionSet(setU, setV);
            count++;
        }
    }
}

int main() {
    int graph[MAX][MAX], u, v, w;
    Edge edgeList[MAX * MAX];

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
        graph[v][u] = w; // Undirected graph
        edgeList[i].u = u;
        edgeList[i].v = v;
        edgeList[i].w = w;
    }

    // Initialize parent for union-find
    for (int i = 0; i < n; i++)
        parent[i] = i;

    // Sort edges by weight
    qsort(edgeList, edges, sizeof(Edge), cmp);

    kruskal(edgeList);

    return 0;
}