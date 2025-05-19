#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node *left, *right;
    int lThread, rThread;
} Node;

// Create a new node
Node* createNode(int key) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = key;
    temp->lThread = temp->rThread = 1;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert a node into TBT
Node* insert(Node* root, int key) {
    Node *ptr = root, *par = NULL;

    while (ptr != NULL) {
        if (key == ptr->data) return root;  // duplicate
        par = ptr;
        if (key < ptr->data) {
            if (!ptr->lThread) ptr = ptr->left;
            else break;
        } else {
            if (!ptr->rThread) ptr = ptr->right;
            else break;
        }
    }

    Node* newNode = createNode(key);

    if (!par) return newNode;  // first node

    if (key < par->data) {
        newNode->left = par->left;
        newNode->right = par;
        par->lThread = 0;
        par->left = newNode;
    } else {
        newNode->right = par->right;
        newNode->left = par;
        par->rThread = 0;
        par->right = newNode;
    }

    return root;
}

// Preorder traversal in threaded binary tree
void preorder(Node* root) {
    Node* cur = root;
    while (cur) {
        printf("%d ", cur->data);

        if (!cur->lThread)
            cur = cur->left;
        else if (!cur->rThread)
            cur = cur->right;
        else {
            while (cur && cur->rThread)
                cur = cur->right;
            if (cur) cur = cur->right;
        }
    }
}

// Driver
int main() {
    Node* root = NULL;
    int n, val;

    printf("How many nodes? ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter value %d: ", i + 1);
        scanf("%d", &val);
        root = insert(root, val);
    }

    printf("Preorder Traversal: ");
    preorder(root);
    return 0;
}