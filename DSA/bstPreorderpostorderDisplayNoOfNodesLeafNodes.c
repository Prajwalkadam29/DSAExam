#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node {
    int data;
    struct Node *left, *right;
};

// Queue for level order
struct Node* queue[MAX];
int front = 0, rear = -1;

void enqueue(struct Node* node) { queue[++rear] = node; }
struct Node* dequeue() { return queue[front++]; }
int isQueueEmpty() { return front > rear; }

struct Node* newNode(int val) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = val;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node* insert(struct Node* root, int val) {
    struct Node* temp = newNode(val);
    struct Node *parent = NULL, *cur = root;

    while (cur != NULL) {
        parent = cur;
        if (val < cur->data)
            cur = cur->left;
        else
            cur = cur->right;
    }

    if (parent == NULL)
        return temp;
    else if (val < parent->data)
        parent->left = temp;
    else
        parent->right = temp;

    return root;
}

// Recursive preorder (since no stack allowed)
void preorder(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

// Recursive postorder
void postorder(struct Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

// Count nodes using queue (level order)
int countNodes(struct Node* root) {
    if (root == NULL) return 0;
    front = 0; rear = -1;
    enqueue(root);
    int count = 0;

    while (!isQueueEmpty()) {
        struct Node* temp = dequeue();
        count++;
        if (temp->left) enqueue(temp->left);
        if (temp->right) enqueue(temp->right);
    }
    return count;
}

// Display leaf nodes using queue (level order)
void displayLeafNodes(struct Node* root) {
    if (root == NULL) return;
    front = 0; rear = -1;
    enqueue(root);
    printf("Leaf nodes: ");

    while (!isQueueEmpty()) {
        struct Node* temp = dequeue();
        if (temp->left == NULL && temp->right == NULL)
            printf("%d ", temp->data);
        if (temp->left) enqueue(temp->left);
        if (temp->right) enqueue(temp->right);
    }
    printf("\n");
}

int main() {
    struct Node* root = NULL;
    int ch, val;

    do {
        printf("\n1.Insert\n2.Preorder\n3.Postorder\n4.Total Nodes\n5.Display Leaf Nodes\n6.Exit\nEnter choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 3:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 4:
                printf("Total nodes: %d\n", countNodes(root));
                break;
            case 5:
                displayLeafNodes(root);
                break;
        }
    } while(ch != 6);

    return 0;
}