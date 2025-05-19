#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[MAX];
int visited[MAX];
int n; // number of vertices

// Create a new adjacency list node
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Add edge to adjacency list
void addEdge(int src, int dest, int directed) {
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = adjList[src];
    adjList[src] = newNode;

    // If undirected, add edge from dest to src
    if (!directed) {
        newNode = createNode(src);
        newNode->next = adjList[dest];
        adjList[dest] = newNode;
    }
}

// BFS using queue
int queue[MAX], front = -1, rear = -1;

void enqueue(int v) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = v;
}

int dequeue() {
    if (front == -1) return -1;
    int v = queue[front];
    if (front == rear) front = rear = -1;
    else front++;
    return v;
}

int isEmpty() {
    return front == -1;
}

void BFS(int start) {
    int v;
    for (v = 0; v < n; v++) visited[v] = 0;

    enqueue(start);
    visited[start] = 1;

    printf("BFS: ");
    while (!isEmpty()) {
        int curr = dequeue();
        printf("%d ", curr);
        Node* temp = adjList[curr];
        while (temp != NULL) {
            int adjV = temp->vertex;
            if (!visited[adjV]) {
                enqueue(adjV);
                visited[adjV] = 1;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

void DFS_util(int v) {
    visited[v] = 1;
    printf("%d ", v);
    Node* temp = adjList[v];
    while (temp != NULL) {
        if (!visited[temp->vertex])
            DFS_util(temp->vertex);
        temp = temp->next;
    }
}

void DFS(int start) {
    int v;
    for (v = 0; v < n; v++) visited[v] = 0;

    printf("DFS: ");
    DFS_util(start);
    printf("\n");
}

int main() {
    int edges, u, v, directed, i;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) adjList[i] = NULL;

    printf("Is the graph directed? (1 for Yes / 0 for No): ");
    scanf("%d", &directed);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v, directed);
    }

    printf("\nAdjacency List:\n");
    for (i = 0; i < n; i++) {
        printf("%d: ", i);
        Node* temp = adjList[i];
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }

    printf("\nEnter starting vertex for BFS and DFS: ");
    scanf("%d", &u);

    BFS(u);
    DFS(u);

    return 0;
}