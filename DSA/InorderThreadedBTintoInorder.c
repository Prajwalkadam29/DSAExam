#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
    int lThread, rThread;  // 1 if thread, 0 if child
} Node;

// Create new node
Node* createNode(int key) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = key;
    temp->left = temp->right = NULL;
    temp->lThread = temp->rThread = 1;
    return temp;
}

// Insert into Inorder Threaded Binary Tree
Node* insert(Node* root, int key) {
    Node *ptr = root, *parent = NULL;

    while (ptr != NULL) {
        if (key == ptr->data) return root; // no duplicates
        parent = ptr;
        if (key < ptr->data) {
            if (!ptr->lThread)
                ptr = ptr->left;
            else
                break;
        } else {
            if (!ptr->rThread)
                ptr = ptr->right;
            else
                break;
        }
    }

    Node* newNode = createNode(key);

    if (parent == NULL) {
        // Tree was empty
        return newNode;
    }

    if (key < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->lThread = 0;
        parent->left = newNode;
    } else {
        newNode->right = parent->right;
        newNode->left = parent;
        parent->rThread = 0;
        parent->right = newNode;
    }

    return root;
}

// Find leftmost node
Node* leftMost(Node* node) {
    if (node == NULL) return NULL;
    while (!node->lThread)
        node = node->left;
    return node;
}

// Inorder traversal of threaded binary tree
void inorder(Node* root) {
    Node* cur = leftMost(root);
    while (cur != NULL) {
        printf("%d ", cur->data);

        if (cur->rThread)
            cur = cur->right;
        else
            cur = leftMost(cur->right);
    }
}

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

    printf("Inorder Traversal: ");
    inorder(root);
    return 0;
}