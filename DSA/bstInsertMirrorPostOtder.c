#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

// Create new node
struct Node* newNode(int val) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = val;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert node
struct Node* insert(struct Node* root, int val) {
    if (root == NULL)
        return newNode(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);
    return root;
}

// Find node
struct Node* find(struct Node* root, int key) {
    while (root != NULL) {
        if (key == root->data)
            return root;
        else if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

// Mirror image
void mirror(struct Node* root) {
    if (root == NULL) return;
    // Swap left and right
    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    // Recur for children
    mirror(root->left);
    mirror(root->right);
}

// Stack for non-recursive postorder
#define MAX 100
struct Node* stack1[MAX], *stack2[MAX];
int top1 = -1, top2 = -1;

void push1(struct Node* node) { stack1[++top1] = node; }
struct Node* pop1() { return stack1[top1--]; }
int isEmpty1() { return top1 == -1; }

void push2(struct Node* node) { stack2[++top2] = node; }
struct Node* pop2() { return stack2[top2--]; }
int isEmpty2() { return top2 == -1; }

// Postorder non-recursive
void postorder(struct Node* root) {
    if (root == NULL) return;
    push1(root);
    while (!isEmpty1()) {
        struct Node* temp = pop1();
        push2(temp);
        if (temp->left) push1(temp->left);
        if (temp->right) push1(temp->right);
    }
    while (!isEmpty2())
        printf("%d ", pop2()->data);
}

int main() {
    struct Node* root = NULL;
    int ch, val;

    do {
        printf("\n1.Insert 2.Find 3.Mirror Image 4.Postorder (nonrec) 5.Exit\nEnter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter number to insert: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;
            case 2:
                printf("Enter number to find: ");
                scanf("%d", &val);
                if (find(root, val))
                    printf("Found!\n");
                else
                    printf("Not found!\n");
                break;
            case 3:
                mirror(root);
                printf("Mirror image created!\n");
                break;
            case 4:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;
        }
    } while (ch != 5);

    return 0;
}