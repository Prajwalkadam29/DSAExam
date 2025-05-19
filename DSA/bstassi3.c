#include <stdio.h>
#include <stdlib.h>

// Define node structure
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Queue structure for level-order traversal
typedef struct Queue {
    Node *node;
    struct Queue *next;
} Queue;

// Stack structure for mirror operation
typedef struct Stack {
    Node *node;
    struct Stack *next;
} Stack;

// Function to create new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert into BST
Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL) return newNode;

    Node* current = root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

// Queue operations
void enqueue(Queue **front, Queue **rear, Node *node) {
    Queue* temp = (Queue*)malloc(sizeof(Queue));
    temp->node = node;
    temp->next = NULL;
    if (*rear) (*rear)->next = temp;
    else *front = temp;
    *rear = temp;
}

Node* dequeue(Queue **front, Queue **rear) {
    if (*front == NULL) return NULL;
    Queue* temp = *front;
    Node* node = temp->node;
    *front = temp->next;
    if (*front == NULL) *rear = NULL;
    free(temp);
    return node;
}

// Stack operations
void push(Stack **top, Node *node) {
    Stack* temp = (Stack*)malloc(sizeof(Stack));
    temp->node = node;
    temp->next = *top;
    *top = temp;
}

Node* pop(Stack **top) {
    if (*top == NULL) return NULL;
    Stack* temp = *top;
    Node* node = temp->node;
    *top = temp->next;
    free(temp);
    return node;
}

// a. Level-wise display
void levelOrderDisplay(Node* root) {
    if (root == NULL) return;

    Queue *front = NULL, *rear = NULL;
    enqueue(&front, &rear, root);

    printf("Level Order: ");
    while (front != NULL) {
        Node* temp = dequeue(&front, &rear);
        printf("%d ", temp->data);
        if (temp->left) enqueue(&front, &rear, temp->left);
        if (temp->right) enqueue(&front, &rear, temp->right);
    }
    printf("\n");
}

// b. Mirror image (non-recursive)
void mirrorImage(Node* root) {
    if (root == NULL) return;

    Stack* stack = NULL;
    push(&stack, root);

    while (stack != NULL) {
        Node* temp = pop(&stack);
        // Swap left and right
        Node* t = temp->left;
        temp->left = temp->right;
        temp->right = t;

        if (temp->left) push(&stack, temp->left);
        if (temp->right) push(&stack, temp->right);
    }
}

// c. Height of tree (non-recursive)
int treeHeight(Node* root) {
    if (root == NULL) return 0;

    Queue *front = NULL, *rear = NULL;
    enqueue(&front, &rear, root);
    int height = 0;

    while (1) {
        int nodeCount = 0;
        Queue *tempFront = front;

        while (tempFront != NULL) {
            nodeCount++;
            tempFront = tempFront->next;
        }

        if (nodeCount == 0) break;
        height++;

        while (nodeCount > 0) {
            Node* node = dequeue(&front, &rear);
            if (node->left) enqueue(&front, &rear, node->left);
            if (node->right) enqueue(&front, &rear, node->right);
            nodeCount--;
        }
    }

    return height;
}

// Main function
int main() {
    Node* root = NULL;
    int choice, value;

    do {
        printf("\n1. Insert\n2. Levelwise Display\n3. Mirror Image\n4. Display Height\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                levelOrderDisplay(root);
                break;
            case 3:
                mirrorImage(root);
                printf("Tree mirrored.\n");
                break;
            case 4:
                printf("Height of tree: %d\n", treeHeight(root));
                break;
        }
    } while(choice != 5);

    return 0;
}