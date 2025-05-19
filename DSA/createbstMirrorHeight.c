#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create new node
struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert node in BST
struct Node* insert(struct Node* root, int val) {
    if (root == NULL)
        return createNode(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

// Level order traversal
void levelOrder(struct Node* root) {
    if (!root) {
        printf("Tree is empty.\n");
        return;
    }

    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    printf("Level order: ");
    while (front < rear) {
        struct Node* curr = queue[front++];
        printf("%d ", curr->data);
        if (curr->left)
            queue[rear++] = curr->left;
        if (curr->right)
            queue[rear++] = curr->right;
    }
    printf("\n");
}

// Mirror tree (in-place)
void mirrorInPlace(struct Node* root) {
    if (!root) return;

    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct Node* curr = queue[front++];
        struct Node* temp = curr->left;
        curr->left = curr->right;
        curr->right = temp;

        if (curr->left)
            queue[rear++] = curr->left;
        if (curr->right)
            queue[rear++] = curr->right;
    }
}

// Copy tree
struct Node* copyTree(struct Node* root) {
    if (!root) return NULL;
    struct Node* newNode = createNode(root->data);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);
    return newNode;
}

// Non-recursive height
int height(struct Node* root) {
    if (!root) return 0;

    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int h = 0;
    while (front < rear) {
        int levelSize = rear - front;
        for (int i = 0; i < levelSize; i++) {
            struct Node* curr = queue[front++];
            if (curr->left)
                queue[rear++] = curr->left;
            if (curr->right)
                queue[rear++] = curr->right;
        }
        h++;
    }
    return h;
}

// Main menu
int main() {
    struct Node* root = NULL;
    int choice, val;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Insert Node\n");
        printf("2. Display Tree (Level Order)\n");
        printf("3. Mirror Tree (Change Original)\n");
        printf("4. Mirror Tree (Keep Original)\n");
        printf("5. Height of Tree (Non-recursive)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;
            case 2:
                levelOrder(root);
                break;
            case 3:
                mirrorInPlace(root);
                printf("Mirrored Tree:\n");
                levelOrder(root);
                break;
            case 4: {
                struct Node* copy = copyTree(root);
                mirrorInPlace(copy);
                printf("Mirror Image (Original Tree Unchanged):\n");
                levelOrder(copy);
                break;
            }
            case 5:
                printf("Height of Tree: %d\n", height(root));
                break;
            case 6:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}