#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Stack for iterative traversals
typedef struct Stack {
    Node** arr;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->arr = (Node**) malloc(sizeof(Node*) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, Node* node) {
    if (stack->top < stack->capacity - 1)
        stack->arr[++stack->top] = node;
}

Node* pop(Stack* stack) {
    if (!isEmpty(stack))
        return stack->arr[stack->top--];
    return NULL;
}

Node* peek(Stack* stack) {
    if (!isEmpty(stack))
        return stack->arr[stack->top];
    return NULL;
}

// Create new node
Node* newNode(int val) {
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->data = val;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert in BST
Node* insert(Node* root, int val) {
    if (!root) return newNode(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

// Iterative Preorder traversal
void preorder(Node* root) {
    if (!root) {
        printf("Tree is empty.\n");
        return;
    }
    Stack* stack = createStack(100);
    push(stack, root);
    printf("Preorder: ");
    while (!isEmpty(stack)) {
        Node* curr = pop(stack);
        printf("%d ", curr->data);
        if (curr->right) push(stack, curr->right);
        if (curr->left) push(stack, curr->left);
    }
    printf("\n");
    free(stack->arr);
    free(stack);
}

// Iterative Inorder traversal
void inorder(Node* root) {
    if (!root) {
        printf("Tree is empty.\n");
        return;
    }
    Stack* stack = createStack(100);
    Node* curr = root;
    printf("Inorder: ");
    while (curr || !isEmpty(stack)) {
        while (curr) {
            push(stack, curr);
            curr = curr->left;
        }
        curr = pop(stack);
        printf("%d ", curr->data);
        curr = curr->right;
    }
    printf("\n");
    free(stack->arr);
    free(stack);
}

// Count leaf nodes using iterative traversal
int countLeafNodes(Node* root) {
    if (!root) return 0;
    int count = 0;
    Stack* stack = createStack(100);
    push(stack, root);
    while (!isEmpty(stack)) {
        Node* curr = pop(stack);
        if (!curr->left && !curr->right)
            count++;
        if (curr->right) push(stack, curr->right);
        if (curr->left) push(stack, curr->left);
    }
    free(stack->arr);
    free(stack);
    return count;
}

// Mirror the tree (recursive)
Node* mirror(Node* root) {
    if (!root) return NULL;
    Node* leftM = mirror(root->left);
    Node* rightM = mirror(root->right);
    root->left = rightM;
    root->right = leftM;
    return root;
}

// Free the tree memory
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    Node* root = NULL;
    int choice, val;
    int mirrored = 0;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Insert node\n");
        printf("2. Preorder traversal\n");
        printf("3. Inorder traversal\n");
        printf("4. Display number of leaf nodes\n");
        printf("5. Mirror the tree\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                root = insert(root, val);
                mirrored = 0;  // tree changed
                break;
            case 2:
                preorder(root);
                break;
            case 3:
                inorder(root);
                break;
            case 4:
                printf("Number of leaf nodes: %d\n", countLeafNodes(root));
                break;
            case 5:
                root = mirror(root);
                mirrored = !mirrored;
                printf("Tree mirrored.\n");
                break;
            case 6:
                printf("Exiting...\n");
                freeTree(root);
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
