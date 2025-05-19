#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to append node at end
void append(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
}

// Function to print linked list
void printList(struct Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Iterative function to reverse the list
void Reverse(struct Node** head) {
    struct Node *prev = NULL, *curr = *head, *next = NULL;
    while (curr != NULL) {
        next = curr->next;   // store next node
        curr->next = prev;   // reverse pointer
        prev = curr;         // move prev ahead
        curr = next;         // move curr ahead
    }
    *head = prev; // update head pointer
}

// Main function
int main() {
    struct Node* head = NULL;

    // Creating list: 10 -> 20 -> 30 -> 40
    append(&head, 10);
    append(&head, 20);
    append(&head, 30);
    append(&head, 40);

    printf("Original list: ");
    printList(head);

    Reverse(&head);

    printf("Reversed list: ");
    printList(head);

    return 0;
}
