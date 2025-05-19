#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

// Stack structure
typedef struct {
    int data[SIZE];
    int top;
} Stack;

// Stack operations
void push(Stack *s, int val) {
    if (s->top == SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    s->data[++(s->top)] = val;
}

int pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->data[(s->top)--];
}

// A. Factorial using Stack
void factorialUsingStack(int num) {
    Stack s;
    s.top = -1;
    int result = 1;

    for (int i = 1; i <= num; i++) {
        push(&s, i);
    }

    while (s.top != -1) {
        result *= pop(&s);
    }

    printf("Factorial of %d is: %d\n", num, result);
}

// B. Fibonacci Series using Stack
void fibonacciUsingStack(int n) {
    Stack s;
    s.top = -1;

    int a = 0, b = 1, c;
    printf("Fibonacci Series (%d terms):\n", n);

    if (n >= 1) printf("%d ", a);
    if (n >= 2) printf("%d ", b);

    for (int i = 3; i <= n; i++) {
        c = a + b;
        push(&s, c); // store in stack (optional)
        printf("%d ", c);
        a = b;
        b = c;
    }
    printf("\n");
}

// Main function
int main() {
    int choice, number;

    do {
        printf("\n--- STACK BASED MENU ---\n");
        printf("1. Factorial using Stack\n");
        printf("2. Fibonacci using Stack\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number to find factorial: ");
                scanf("%d", &number);
                factorialUsingStack(number);
                break;
            case 2:
                printf("Enter number of terms for Fibonacci: ");
                scanf("%d", &number);
                fibonacciUsingStack(number);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 3);

    return 0;
}
