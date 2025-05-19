#include <stdio.h>
#include <stdlib.h>

/* ----------  Node definition ---------- */
typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node;

/* ----------  Head pointer ---------- */
Node *head = NULL;

/* ----------  Utility: create node ---------- */
Node* newNode(int data) {
    Node *t = (Node*)malloc(sizeof(Node));
    t->data = data;
    t->prev = t->next = NULL;
    return t;
}

/* ----------  INSERT OPERATIONS ---------- */
void insertAtBeginning(int data) {
    Node *t = newNode(data);
    if (head) {
        t->next = head;
        head->prev = t;
    }
    head = t;
}

void insertAtEnd(int data) {
    Node *t = newNode(data);
    if (!head) { head = t; return; }
    Node *p = head;
    while (p->next) p = p->next;
    p->next = t;
    t->prev  = p;
}

void insertAfterValue(int key, int data) {
    Node *p = head;
    while (p && p->data != key) p = p->next;
    if (!p) { printf("Value %d not found!\n", key); return; }

    Node *t = newNode(data);
    t->next = p->next;
    t->prev = p;
    if (p->next) p->next->prev = t;
    p->next = t;
}

/* ----------  DELETE OPERATIONS ---------- */
void deleteFromBeginning(void) {
    if (!head) { printf("List empty!\n"); return; }
    Node *t = head;
    head = head->next;
    if (head) head->prev = NULL;
    free(t);
}

void deleteFromEnd(void) {
    if (!head) { printf("List empty!\n"); return; }
    Node *p = head;
    while (p->next) p = p->next;
    if (p->prev) p->prev->next = NULL;
    else head = NULL;          /* only one node */
    free(p);
}

void deleteByValue(int key) {
    Node *p = head;
    while (p && p->data != key) p = p->next;
    if (!p) { printf("Value %d not found!\n", key); return; }

    if (p->prev) p->prev->next = p->next;
    else head = p->next;       /* deleting head */

    if (p->next) p->next->prev = p->prev;
    free(p);
}

/* ----------  DISPLAY ---------- */
void display(void) {
    if (!head) { printf("List empty!\n"); return; }
    Node *p = head;
    printf("List: ");
    while (p) { printf("%d ", p->data); p = p->next; }
    printf("\n");
}

/* ----------  MAIN / MENU ---------- */
int main(void) {
    int choice, val, key;

    while (1) {
        printf(
            "\n--- DOUBLY LINKED LIST MENU ---\n"
            "1. Insert at beginning\n"
            "2. Insert at end\n"
            "3. Insert after a value\n"
            "4. Delete from beginning\n"
            "5. Delete from end\n"
            "6. Delete by value\n"
            "7. Display list\n"
            "8. Exit\n"
            "Enter choice: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                printf("Value to insert: ");  scanf("%d", &val);
                insertAtBeginning(val);
                break;
            case 2:
                printf("Value to insert: ");  scanf("%d", &val);
                insertAtEnd(val);
                break;
            case 3:
                printf("Insert after value: "); scanf("%d", &key);
                printf("New value: ");          scanf("%d", &val);
                insertAfterValue(key, val);
                break;
            case 4:
                deleteFromBeginning();
                break;
            case 5:
                deleteFromEnd();
                break;
            case 6:
                printf("Value to delete: "); scanf("%d", &key);
                deleteByValue(key);
                break;
            case 7:
                display();
                break;
            case 8:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
