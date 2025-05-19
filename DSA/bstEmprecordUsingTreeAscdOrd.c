#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int empID;
    char name[50];
    struct Employee* left;
    struct Employee* right;
};

// Create new node
struct Employee* createNode(int id, char name[]) {
    struct Employee* newNode = (struct Employee*)malloc(sizeof(struct Employee));
    newNode->empID = id;
    strcpy(newNode->name, name);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert into BST
struct Employee* insert(struct Employee* root, int id, char name[]) {
    if (root == NULL) return createNode(id, name);
    if (id < root->empID)
        root->left = insert(root->left, id, name);
    else
        root->right = insert(root->right, id, name);
    return root;
}

// Inorder traversal (sorted by empID)
void inorder(struct Employee* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("EmpID: %d, Name: %s\n", root->empID, root->name);
    inorder(root->right);
}

// Search employee by ID
struct Employee* search(struct Employee* root, int id) {
    while (root != NULL) {
        if (id == root->empID) return root;
        else if (id < root->empID) root = root->left;
        else root = root->right;
    }
    return NULL;
}

int main() {
    struct Employee* root = NULL;
    int choice, id;
    char name[50];

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Add employee\n");
        printf("2. Search employee by ID\n");
        printf("3. Display all employees (sorted by ID)\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &id);
                printf("Enter Name: ");
                getchar(); // consume newline
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // remove newline
                root = insert(root, id, name);
                break;
            case 2:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                struct Employee* found = search(root, id);
                if (found)
                    printf("Found! EmpID: %d, Name: %s\n", found->empID, found->name);
                else
                    printf("Employee not found.\n");
                break;
            case 3:
                printf("Employee List (sorted by ID):\n");
                inorder(root);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}