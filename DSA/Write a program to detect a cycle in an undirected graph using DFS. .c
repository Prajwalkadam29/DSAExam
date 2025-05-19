#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int visited[MAX];

// Adjacency list node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Graph structure
typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

// Create a node
Node* createNode(int v) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Create graph
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**) malloc(vertices * sizeof(Node*));
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        visited[i] = 0;
    }
    return graph;
}

// Add edge (undirected)
void addEdge(Graph* graph, int src, int dest) {
    // Add edge src -> dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge dest -> src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// DFS function to detect cycle
int dfsCycleDetect(Graph* graph, int v, int parent) {
    visited[v] = 1;

    Node* temp = graph->adjLists[v];
    while (temp != NULL) {
        int adjVertex = temp->vertex;

        if (!visited[adjVertex]) {
            if (dfsCycleDetect(graph, adjVertex, v))
                return 1;
        }
        else if (adjVertex != parent) {
            // Visited node that is not parent -> cycle found
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

// Check cycle in graph
int hasCycle(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            if (dfsCycleDetect(graph, i, -1))
                return 1;
        }
    }
    return 0;
}

int main() {
    int vertices, edges;
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    Graph* graph = createGraph(vertices);

    printf("Enter edges (source destination):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    if (hasCycle(graph))
        printf("Graph contains cycle\n");
    else
        printf("Graph does not contain cycle\n");

    // Free memory (optional here)

    return 0;
}
