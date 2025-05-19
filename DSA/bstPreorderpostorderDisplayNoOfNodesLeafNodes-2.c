#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int val) {
    if (root == NULL)
        return createNode(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

// Stack implementation for Node pointers
#define MAX 100

struct Stack {
    int top;
    struct Node* arr[MAX];
};

void initStack(struct Stack* s) {
    s->top = -1;
}

int isEmpty(struct Stack* s) {
    return s->top == -1;
}

void push(struct Stack* s, struct Node* node) {
    if (s->top < MAX - 1)
        s->arr[++(s->top)] = node;
}

struct Node* pop(struct Stack* s) {
    if (!isEmpty(s))
        return s->arr[(s->top)--];
    return NULL;
}

struct Node* peek(struct Stack* s) {
    if (!isEmpty(s))
        return s->arr[s->top];
    return NULL;
}

// Nonrecursive Preorder traversal
void preorder(struct Node* root) {
    if (root == NULL) return;
    struct Stack s;
    initStack(&s);
    push(&s, root);

    printf("Preorder: ");
    while (!isEmpty(&s)) {
        struct Node* curr = pop(&s);
        printf("%d ", curr->data);
        if (curr->right) push(&s, curr->right);
        if (curr->left) push(&s, curr->left);
    }
    printf("\n");
}

// Nonrecursive Postorder traversal
void postorder(struct Node* root) {
    if (root == NULL) return;
    struct Stack s1, s2;
    initStack(&s1);
    initStack(&s2);
    push(&s1, root);

    while (!isEmpty(&s1)) {
        struct Node* curr = pop(&s1);
        push(&s2, curr);
        if (curr->left) push(&s1, curr->left);
        if (curr->right) push(&s1, curr->right);
    }

    printf("Postorder: ");
    while (!isEmpty(&s2)) {
        struct Node* curr = pop(&s2);
        printf("%d ", curr->data);
    }
    printf("\n");
}

// Count total nodes (nonrecursive)
int countNodes(struct Node* root) {
    if (root == NULL) return 0;
    struct Stack s;
    initStack(&s);
    push(&s, root);
    int count = 0;

    while (!isEmpty(&s)) {
        struct Node* curr = pop(&s);
        count++;
        if (curr->left) push(&s, curr->left);
        if (curr->right) push(&s, curr->right);
    }
    return count;
}

// Display leaf nodes (nonrecursive)
void printLeafNodes(struct Node* root) {
    if (root == NULL) return;
    struct Stack s;
    initStack(&s);
    push(&s, root);

    printf("Leaf nodes: ");
    while (!isEmpty(&s)) {
        struct Node* curr = pop(&s);
        if (curr->left == NULL && curr->right == NULL)
            printf("%d ", curr->data);
        if (curr->right) push(&s, curr->right);
        if (curr->left) push(&s, curr->left);
    }
    printf("\n");
}

int main() {
    struct Node* root = NULL;
    int n, val, i;

    printf("Enter number of nodes to insert: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter value %d: ", i + 1);
        scanf("%d", &val);
        root = insert(root, val);
    }

    preorder(root);
    postorder(root);

    printf("Total number of nodes: %d\n", countNodes(root));
    printLeafNodes(root);

    return 0;
}