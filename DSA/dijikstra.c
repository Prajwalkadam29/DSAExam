#include <stdio.h>
#define MAX 20
#define INF 9999

int n;

int minDist(int dist[], int visited[]) {
    int min = INF, min_index = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void dijkstra(int graph[MAX][MAX], int src) {
    int dist[MAX], visited[MAX] = {0};

    for (int i = 0; i < n; i++)
        dist[i] = INF;
    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDist(dist, visited);
        visited[u] = 1;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    printf("Vertex\tDistance from Source %d\n", src);
    for (int i = 0; i < n; i++)
        printf("%d\t%d\n", i, dist[i]);
}

int main() {
    int graph[MAX][MAX], edges, u, v, w;

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
        // For undirected graph, also add:
        // graph[v][u] = w;
    }

    printf("Enter source vertex: ");
    scanf("%d", &u);

    dijkstra(graph, u);

    return 0;
}