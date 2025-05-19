#include <stdio.h>
#include <stdlib.h>

/* -------- Node definition -------- */
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

/* -------- Create a new node -------- */
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

/* -------- Insert at end -------- */
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!(*head)) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

/* -------- Display the list -------- */
void displayList(Node* head) {
    Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

/* -------- Merge two sorted DLLs -------- */
Node* mergeSortedLists(Node* head1, Node* head2) {
    Node* merged = NULL;
    Node* tail = NULL;

    while (head1 && head2) {
        Node* temp;
        if (head1->data <= head2->data) {
            temp = head1;
            head1 = head1->next;
        } else {
            temp = head2;
            head2 = head2->next;
        }

        temp->prev = temp->next = NULL;

        if (!merged) {
            merged = tail = temp;
        } else {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }

    Node* remaining = head1 ? head1 : head2;
    while (remaining) {
        Node* temp = remaining;
        remaining = remaining->next;
        temp->next = NULL;
        temp->prev = tail;
        if (tail)
            tail->next = temp;
        else
            merged = temp;
        tail = temp;
    }

    return merged;
}

/* -------- Main Function -------- */
int main() {
    Node *head1 = NULL, *head2 = NULL, *mergedHead = NULL;
    int n, val;

    printf("Enter number of elements in first sorted list: ");
    scanf("%d", &n);
    printf("Enter %d sorted elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        insertAtEnd(&head1, val);
    }

    printf("Enter number of elements in second sorted list: ");
    scanf("%d", &n);
    printf("Enter %d sorted elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        insertAtEnd(&head2, val);
    }

    printf("\nFirst List: ");
    displayList(head1);
    printf("Second List: ");
    displayList(head2);

    mergedHead = mergeSortedLists(head1, head2);
    printf("\nMerged Sorted List: ");
    displayList(mergedHead);

    return 0;
}
