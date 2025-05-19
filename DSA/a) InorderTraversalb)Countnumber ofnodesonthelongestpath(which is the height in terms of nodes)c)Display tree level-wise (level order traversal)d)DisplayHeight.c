#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left, *right;
} Node;

typedef struct {
    Node* arr[100];
    int top;
} Stack;

typedef struct {
    Node* arr[100];
    int front, rear;
} Queue;

// Stack functions
void push(Stack *s, Node* n) {
    s->arr[++s->top] = n;
}

Node* pop(Stack *s) {
    if (s->top == -1) return NULL;
    return s->arr[s->top--];
}

int isEmptyStack(Stack *s) {
    return s->top == -1;
}

// Queue functions
void enqueue(Queue* q, Node* n) {
    q->arr[q->rear++] = n;
}

Node* dequeue(Queue* q) {
    if (q->front == q->rear) return NULL;
    return q->arr[q->front++];
}

int isEmptyQueue(Queue* q) {
    return q->front == q->rear;
}

// Create new node
Node* newNode(int d) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = d; n->left = n->right = NULL;
    return n;
}

// Insert node (BST style)
Node* insert(Node* root, int d) {
    if (!root) return newNode(d);
    if (d < root->data)
        root->left = insert(root->left, d);
    else
        root->right = insert(root->right, d);
    return root;
}

// Non-recursive Inorder traversal
void inorder(Node* root) {
    Stack s; s.top = -1;
    Node* curr = root;
    printf("Inorder: ");
    while (curr != NULL || !isEmptyStack(&s)) {
        while (curr != NULL) {
            push(&s, curr);
            curr = curr->left;
        }
        curr = pop(&s);
        printf("%d ", curr->data);
        curr = curr->right;
    }
    printf("\n");
}

// Count nodes on longest path (height in nodes)
int longestPathNodes(Node* root) {
    if (!root) return 0;
    Queue q; q.front = q.rear = 0;
    enqueue(&q, root);
    int count = 0;
    while (!isEmptyQueue(&q)) {
        int size = q.rear - q.front;
        count = size;  // number of nodes at current level
        while (size--) {
            Node* curr = dequeue(&q);
            if (curr->left) enqueue(&q, curr->left);
            if (curr->right) enqueue(&q, curr->right);
        }
    }
    return count;
}

// Level order traversal (display tree level-wise)
void levelOrder(Node* root) {
    if (!root) return;
    Queue q; q.front = q.rear = 0;
    enqueue(&q, root);
    printf("Level order: ");
    while (!isEmptyQueue(&q)) {
        Node* curr = dequeue(&q);
        printf("%d ", curr->data);
        if (curr->left) enqueue(&q, curr->left);
        if (curr->right) enqueue(&q, curr->right);
    }
    printf("\n");
}

// Height of tree (levels count)
int height(Node* root) {
    if (!root) return 0;
    Queue q; q.front = q.rear = 0;
    enqueue(&q, root);
    int h = 0;
    while (!isEmptyQueue(&q)) {
        int size = q.rear - q.front;
        while (size--) {
            Node* curr = dequeue(&q);
            if (curr->left) enqueue(&q, curr->left);
            if (curr->right) enqueue(&q, curr->right);
        }
        h++;
    }
    return h;
}

int main() {
    Node* root = NULL;
    int n, val;
    printf("Number of nodes: ");
    scanf("%d", &n);
    printf("Enter values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insert(root, val);
    }

    inorder(root);
    printf("Nodes on longest path: %d\n", height(root));  // height in nodes = longest path nodes
    levelOrder(root);
    printf("Height of tree: %d\n", height(root));

    return 0;
}