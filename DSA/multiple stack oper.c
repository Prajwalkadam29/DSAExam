#include <stdio.h>
#include <stdlib.h>

#define SIZE 100  // total size of array
#define K 3       // number of stacks

int arr[SIZE];           // shared array
int top[K];              // tops of each stack
int start[K + 1];        // start boundaries for each stack

// Initialize stack limits
void init() {
    int part = SIZE / K;
    for (int i = 0; i < K; i++) {
        top[i] = -1;
        start[i] = i * part;
    }
    start[K] = SIZE; // end boundary for last stack
}

// PUSH operation
void push(int stackNum, int value) {
    if (stackNum < 0 || stackNum >= K) {
        printf("Invalid stack number!\n");
        return;
    }

    if (top[stackNum] == -1)
        top[stackNum] = start[stackNum];
    else
        top[stackNum]++;

    if (top[stackNum] >= start[stackNum + 1]) {
        printf("Stack %d is FULL!\n", stackNum);
        top[stackNum]--;  // rollback
        return;
    }

    arr[top[stackNum]] = value;
    printf("Pushed %d to Stack %d\n", value, stackNum);
}

// POP operation
void pop(int stackNum) {
    if (stackNum < 0 || stackNum >= K || top[stackNum] == -1) {
        printf("Stack %d is EMPTY!\n", stackNum);
        return;
    }

    printf("Popped %d from Stack %d\n", arr[top[stackNum]], stackNum);
    if (top[stackNum] == start[stackNum])
        top[stackNum] = -1;
    else
        top[stackNum]--;
}

// Check if stack is full
int isFull(int stackNum) {
    if (top[stackNum] + 1 >= start[stackNum + 1])
        return 1;
    return 0;
}

// Check if stack is empty
int isEmpty(int stackNum) {
    return top[stackNum] == -1;
}

// Display stack elements
void display(int stackNum) {
    if (isEmpty(stackNum)) {
        printf("Stack %d is EMPTY\n", stackNum);
        return;
    }

    printf("Stack %d: ", stackNum);
    for (int i = start[stackNum]; i <= top[stackNum]; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main menu
int main() {
    int choice, snum, val;
    init();

    while (1) {
        printf("\nMenu:\n1. PUSH\n2. POP\n3. isFull\n4. isEmpty\n5. Display\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 6) break;

        printf("Enter stack number (0 to %d): ", K - 1);
        scanf("%d", &snum);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                push(snum, val);
                break;
            case 2:
                pop(snum);
                break;
            case 3:
                if (isFull(snum))
                    printf("Stack %d is FULL\n", snum);
                else
                    printf("Stack %d is NOT full\n", snum);
                break;
            case 4:
                if (isEmpty(snum))
                    printf("Stack %d is EMPTY\n", snum);
                else
                    printf("Stack %d is NOT empty\n", snum);
                break;
            case 5:
                display(snum);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
