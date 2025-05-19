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

// Function to simulate room movement
void moveForward() {
    printf("Moving from Room 1 → Room 5:\n");
    for (int i = 1; i <= 5; i++)
        printf("Entered Room %d\n", i);
}

void moveBackward() {
    printf("Returning from Room 5 → Room 1:\n");
    for (int i = 4; i >= 1; i--)
        printf("Back to Room %d\n", i);
}

// Function to convert decimal to binary using stack
void convertToBinary(int number) {
    Stack s;
    s.top = -1;

    printf("\nDecimal number found in Room 5: %d\n", number);

    // Convert to binary using stack
    while (number > 0) {
        push(&s, number % 2);
        number = number / 2;
    }

    printf("Binary code to unlock treasure: ");
    while (s.top != -1) {
        printf("%d", pop(&s));
    }
    printf("\n");
}

// Main function
int main() {
    int decimal;

    moveForward();

    printf("\nYou found a box in Room 5! Enter the decimal number written on it: ");
    scanf("%d", &decimal);

    convertToBinary(decimal);

    moveBackward();

    printf("\nTreasure unlocked in Room 1 using binary code!\n");
    return 0;
}
