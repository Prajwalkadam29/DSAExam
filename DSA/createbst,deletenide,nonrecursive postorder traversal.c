#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

struct Node* insert(struct Node* root, int val) {
    if (root == NULL) return createNode(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);
    return root;
}

// Find minimum value node in right subtree
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct Node* deleteNode(struct Node* root, int val) {
    if (root == NULL) return root;

    if (val < root->data)
        root->left = deleteNode(root->left, val);
    else if (val > root->data)
        root->right = deleteNode(root->right, val);
    else {
        // Node found
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children
        struct Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Stack for nodes
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

// Nonrecursive postorder traversal using two stacks
void postorder(struct Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
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

int main() {
    struct Node* root = NULL;
    int choice, val;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Insert node\n");
        printf("2. Delete node\n");
        printf("3. Postorder traversal\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                root = deleteNode(root, val);
                break;
            case 3:
                postorder(root);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}