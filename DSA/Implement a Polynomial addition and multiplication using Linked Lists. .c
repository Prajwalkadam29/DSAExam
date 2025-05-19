#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int exp;
    struct Node* next;
} Node;

// Create a new node
Node* createNode(int c, int e) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->coeff = c;
    newNode->exp = e;
    newNode->next = NULL;
    return newNode;
}

// Insert node in descending order of exponent
void insertTerm(Node** poly, int coeff, int exp) {
    Node *newNode = createNode(coeff, exp);
    if (*poly == NULL || (*poly)->exp < exp) {
        newNode->next = *poly;
        *poly = newNode;
    } else {
        Node* temp = *poly;
        while (temp->next != NULL && temp->next->exp > exp)
            temp = temp->next;
        if (temp->next != NULL && temp->next->exp == exp) {
            // Same exponent, add coefficients
            temp->next->coeff += coeff;
            free(newNode);
        } else {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
}

// Display polynomial
void printPoly(Node* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    Node* temp = poly;
    while (temp != NULL) {
        if (temp->coeff > 0 && temp != poly) printf("+");
        if (temp->exp == 0)
            printf("%d ", temp->coeff);
        else if (temp->exp == 1)
            printf("%dx ", temp->coeff);
        else
            printf("%dx^%d ", temp->coeff, temp->exp);
        temp = temp->next;
    }
    printf("\n");
}

// Add two polynomials
Node* addPoly(Node* p1, Node* p2) {
    Node* result = NULL;
    Node *t1 = p1, *t2 = p2;

    while (t1 != NULL && t2 != NULL) {
        if (t1->exp > t2->exp) {
            insertTerm(&result, t1->coeff, t1->exp);
            t1 = t1->next;
        } else if (t2->exp > t1->exp) {
            insertTerm(&result, t2->coeff, t2->exp);
            t2 = t2->next;
        } else {
            // Exponents are equal
            int sum = t1->coeff + t2->coeff;
            if (sum != 0)
                insertTerm(&result, sum, t1->exp);
            t1 = t1->next;
            t2 = t2->next;
        }
    }

    // Add remaining terms
    while (t1 != NULL) {
        insertTerm(&result, t1->coeff, t1->exp);
        t1 = t1->next;
    }
    while (t2 != NULL) {
        insertTerm(&result, t2->coeff, t2->exp);
        t2 = t2->next;
    }
    return result;
}

// Multiply two polynomials
Node* multiplyPoly(Node* p1, Node* p2) {
    Node* result = NULL;
    for (Node* t1 = p1; t1 != NULL; t1 = t1->next) {
        for (Node* t2 = p2; t2 != NULL; t2 = t2->next) {
            int coeff = t1->coeff * t2->coeff;
            int exp = t1->exp + t2->exp;
            insertTerm(&result, coeff, exp);
        }
    }
    return result;
}

// Free the polynomial list
void freePoly(Node* poly) {
    Node* temp;
    while (poly != NULL) {
        temp = poly;
        poly = poly->next;
        free(temp);
    }
}

int main() {
    Node *p1 = NULL, *p2 = NULL, *sum = NULL, *product = NULL;
    int n, coeff, exp;

    // Input first polynomial
    printf("Enter number of terms in first polynomial: ");
    scanf("%d", &n);
    printf("Enter terms (coeff exponent) in descending order of exponents:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        insertTerm(&p1, coeff, exp);
    }

    // Input second polynomial
    printf("Enter number of terms in second polynomial: ");
    scanf("%d", &n);
    printf("Enter terms (coeff exponent) in descending order of exponents:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        insertTerm(&p2, coeff, exp);
    }

    printf("\nFirst Polynomial: ");
    printPoly(p1);
    printf("Second Polynomial: ");
    printPoly(p2);

    // Add polynomials
    sum = addPoly(p1, p2);
    printf("\nSum of Polynomials: ");
    printPoly(sum);

    // Multiply polynomials
    product = multiplyPoly(p1, p2);
    printf("Product of Polynomials: ");
    printPoly(product);

    // Free memory
    freePoly(p1);
    freePoly(p2);
    freePoly(sum);
    freePoly(product);

    return 0;
}
