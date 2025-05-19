#include <stdio.h>
#include <stdlib.h>

// Linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// Function to print a list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to split list into front and back halves
void FrontBackSplit(struct Node* source, struct Node** frontRef, struct Node** backRef) {
    struct Node *slow, *fast;

    // Special case: 0 or 1 elements
    if (source == NULL || source->next == NULL) {
        *frontRef = source;
        *backRef = NULL;
        return;
    }

    slow = source;
    fast = source->next;

    // Advance fast by 2 and slow by 1
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // Split
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

// Helper function to append at the end
void append(struct Node** headRef, int data) {
    struct Node* new_node = newNode(data);
    if (*headRef == NULL) {
        *headRef = new_node;
        return;
    }
    struct Node* last = *headRef;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}

// Main function for testing
int main() {
    struct Node* head = NULL;
    struct Node* front = NULL;
    struct Node* back = NULL;

    // Test case: change these values to test other cases
    append(&head, 2);
    append(&head, 3);
    append(&head, 5);
    append(&head, 7);
    append(&head, 11);

    printf("Original list:\n");
    printList(head);

    FrontBackSplit(head, &front, &back);

    printf("\nFront half:\n");
    printList(front);

    printf("Back half:\n");
    printList(back);

    return 0;
}
