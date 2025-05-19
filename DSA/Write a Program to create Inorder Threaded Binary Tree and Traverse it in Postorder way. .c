#include <stdio.h>
#include <stdlib.h>

// Define node structure
typedef struct Node {
    int data;
    struct Node *left, *right;
    int lthread, rthread;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    temp->lthread = temp->rthread = 1;
    return temp;
}

// Insert a node into the Threaded Binary Tree
Node* insert(Node* root, int key) {
    Node* ptr = root;
    Node* par = NULL;

    while (ptr != NULL) {
        if (key == ptr->data) {
            printf("Duplicate Key!\n");
            return root;
        }

        par = ptr;

        if (key < ptr->data) {
            if (ptr->lthread == 0)
                ptr = ptr->left;
            else
                break;
        } else {
            if (ptr->rthread == 0)
                ptr = ptr->right;
            else
                break;
        }
    }

    Node* temp = createNode(key);

    if (par == NULL) {
        root = temp;
        temp->left = temp->right = NULL;
    } else if (key < par->data) {
        temp->left = par->left;
        temp->right = par;
        par->lthread = 0;
        par->left = temp;
    } else {
        temp->left = par;
        temp->right = par->right;
        par->rthread = 0;
        par->right = temp;
    }

    return root;
}

// Stack structure for postorder traversal
typedef struct Stack {
    Node* data[100];
    int top;
} Stack;

void push(Stack* s, Node* node) {
    s->data[++(s->top)] = node;
}

Node* pop(Stack* s) {
    return s->data[(s->top)--];
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

// Helper to find the leftmost node
Node* leftmost(Node* node) {
    if (!node) return NULL;
    while (node->lthread == 0)
        node = node->left;
    return node;
}

// Helper to find the rightmost node
Node* rightmost(Node* node) {
    if (!node) return NULL;
    while (node->rthread == 0)
        node = node->right;
    return node;
}

// Postorder traversal using stack
void postorder(Node* root) {
    if (!root) return;
    Stack s;
    s.top = -1;
    Node* curr = root;
    Node* prev = NULL;

    while (curr || !isEmpty(&s)) {
        while (curr) {
            push(&s, curr);
            if (curr->lthread == 0)
                curr = curr->left;
            else
                break;
        }

        while (!isEmpty(&s)) {
            curr = s.data[s.top];

            if (curr->rthread == 1 || curr->right == prev || curr->rthread == 0 && curr->right == NULL) {
                printf("%d ", curr->data);
                pop(&s);
                prev = curr;
            } else {
                curr = curr->right;
                break;
            }
        }
    }
}

// Main function
int main() {
    Node* root = NULL;
    int n, val;

    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insert(root, val);
    }

    printf("\nPostorder Traversal of Inorder Threaded Binary Tree:\n");
    postorder(root);

    return 0;
}
