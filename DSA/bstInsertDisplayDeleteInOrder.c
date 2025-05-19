#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* newNode(int val) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = val;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node* insert(struct Node* root, int val) {
    if (root == NULL) return newNode(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);
    return root;
}

void inorder(struct Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

struct Node* find(struct Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;
    if (key < root->data)
        return find(root->left, key);
    else
        return find(root->right, key);
}

struct Node* minValue(struct Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

struct Node* delete(struct Node* root, int key) {
    if (root == NULL) return NULL;
    if (key < root->data)
        root->left = delete(root->left, key);
    else if (key > root->data)
        root->right = delete(root->right, key);
    else {
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
        struct Node* temp = minValue(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

int main() {
    struct Node* root = NULL;
    int ch, x;

    do {
        printf("\n1.Insert 2.Delete 3.Find 4.Inorder 5.Exit\nEnter choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter number: ");
                scanf("%d", &x);
                root = insert(root, x);
                break;
            case 2:
                printf("Enter number to delete: ");
                scanf("%d", &x);
                root = delete(root, x);
                break;
            case 3:
                printf("Enter number to find: ");
                scanf("%d", &x);
                if (find(root, x))
                    printf("Found\n");
                else
                    printf("Not Found\n");
                break;
            case 4:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;
        }
    } while (ch != 5);

    return 0;
}