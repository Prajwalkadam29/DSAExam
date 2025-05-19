#include <stdio.h>

#define MAX 20

int adj[MAX][MAX], visited[MAX], n;

// Queue for BFS
int queue[MAX], front = -1, rear = -1;

void enqueue(int v) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = v;
}

int dequeue() {
    if (front == -1) return -1;
    int v = queue[front];
    if (front == rear)
        front = rear = -1;
    else
        front++;
    return v;
}

int isEmpty() {
    return front == -1;
}

// BFS Traversal
void BFS(int start) {
    int i, v;
    for (i = 0; i < n; i++) visited[i] = 0;
    enqueue(start);
    visited[start] = 1;

    printf("BFS: ");
    while (!isEmpty()) {
        v = dequeue();
        printf("%d ", v);
        for (i = 0; i < n; i++) {
            if (adj[v][i] && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

// DFS Traversal
void DFS_util(int v) {
    int i;
    visited[v] = 1;
    printf("%d ", v);
    for (i = 0; i < n; i++) {
        if (adj[v][i] && !visited[i])
            DFS_util(i);
    }
}

void DFS(int start) {
    int i;
    for (i = 0; i < n; i++) visited[i] = 0;
    printf("DFS: ");
    DFS_util(start);
    printf("\n");
}

int main() {
    int i, j, edges, u, v, directed;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Initialize adjacency matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Is the graph directed? (1 for Yes / 0 for No): ");
    scanf("%d", &directed);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v) where u and v are vertices (0 to %d):\n", n-1);
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        if (!directed)
            adj[v][u] = 1;
    }

    printf("\nAdjacency Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%d ", adj[i][j]);
        printf("\n");
    }

    printf("\nEnter starting vertex for BFS and DFS: ");
    scanf("%d", &u);

    BFS(u);
    DFS(u);

    return 0;
}