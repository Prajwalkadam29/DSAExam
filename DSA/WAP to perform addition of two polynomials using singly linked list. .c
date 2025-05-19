#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int exp;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert node at the end
void appendNode(struct Node** head, int coeff, int exp) {
    struct Node* newNode = createNode(coeff, exp);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
}

// Function to print the polynomial
void printPoly(struct Node* poly) {
    while (poly != NULL) {
        printf("%dx^%d", poly->coeff, poly->exp);
        poly = poly->next;
        if (poly != NULL)
            printf(" + ");
    }
    printf("\n");
}

// Function to add two polynomials
struct Node* addPolynomials(struct Node* p1, struct Node* p2) {
    struct Node* result = NULL;

    while (p1 && p2) {
        if (p1->exp == p2->exp) {
            appendNode(&result, p1->coeff + p2->coeff, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->exp > p2->exp) {
            appendNode(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        } else {
            appendNode(&result, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }

    // Remaining terms
    while (p1) {
        appendNode(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    while (p2) {
        appendNode(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

// Main function
int main() {
    struct Node *poly1 = NULL, *poly2 = NULL, *sum = NULL;

    // Example: 5x^2 + 4x^1 + 2
    appendNode(&poly1, 5, 2);
    appendNode(&poly1, 4, 1);
    appendNode(&poly1, 2, 0);

    // Example: 5x^1 + 5
    appendNode(&poly2, 5, 1);
    appendNode(&poly2, 5, 0);

    printf("Polynomial 1: ");
    printPoly(poly1);

    printf("Polynomial 2: ");
    printPoly(poly2);

    sum = addPolynomials(poly1, poly2);

    printf("Sum = ");
    printPoly(sum);

    return 0;
}
