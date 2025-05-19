#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// Structure for task
typedef struct {
    int id;          // Task id (just a number)
    char taskName[20];
} Task;

// Queues for three priorities
Task downloadQueue[MAX], musicQueue[MAX], gameQueue[MAX];
int dFront = 0, dRear = -1;
int mFront = 0, mRear = -1;
int gFront = 0, gRear = -1;

// Enqueue functions
void enqueue(Task queue[], int *rear, Task t) {
    if (*rear == MAX - 1) {
        printf("Queue is full! Cannot add more tasks.\n");
        return;
    }
    queue[++(*rear)] = t;
}

// Dequeue functions
Task dequeue(Task queue[], int *front, int *rear) {
    Task t = {"", -1};
    if (*front > *rear) {
        return t;  // Empty task
    }
    t = queue[(*front)++];
    return t;
}

// Check if queue empty
int isEmpty(int front, int rear) {
    return (front > rear);
}

// Function to simulate task processing
void processQueue(Task queue[], int *front, int *rear, char *taskType) {
    while (!isEmpty(*front, *rear)) {
        Task t = dequeue(queue, front, rear);
        printf("Processing %s task ID %d\n", taskType, t.id);
    }
}

int main() {
    int n, choice;
    Task t;
    printf("Enter total number of tasks to add: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter task type:\n");
        printf("1. Download (Highest priority)\n");
        printf("2. Listen Music (Medium priority)\n");
        printf("3. Play Game (Lowest priority)\n");
        printf("Choice: ");
        scanf("%d", &choice);

        t.id = i + 1;

        switch (choice) {
            case 1:
                sprintf(t.taskName, "Download");
                enqueue(downloadQueue, &dRear, t);
                break;
            case 2:
                sprintf(t.taskName, "Music");
                enqueue(musicQueue, &mRear, t);
                break;
            case 3:
                sprintf(t.taskName, "Game");
                enqueue(gameQueue, &gRear, t);
                break;
            default:
                printf("Invalid task type! Try again.\n");
                i--;  // Repeat this iteration
        }
    }

    printf("\n--- Starting task processing by priority ---\n");

    // Process in priority order
    processQueue(downloadQueue, &dFront, &dRear, "Download");
    processQueue(musicQueue, &mFront, &mRear, "Music");
    processQueue(gameQueue, &gFront, &gRear, "Game");

    printf("All tasks completed!\n");

    return 0;
}
