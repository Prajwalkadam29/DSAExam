#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIMULATION_TIME 120
#define REQUEST_INTERVAL 5
#define OPERATION_TIME 15
#define MAX_REQUESTS (SIMULATION_TIME / REQUEST_INTERVAL)

typedef struct {
    int id;
    int time_stamp;
} Request;

typedef struct {
    Request queue[100];
    int front, rear;
} Queue;

// Initialize queue
void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

// Check if queue is empty
int isEmpty(Queue *q) {
    return q->front == -1;
}

// Enqueue request
void enqueue(Queue *q, Request r) {
    if (q->rear == 99) return;
    if (q->front == -1) q->front = 0;
    q->queue[++q->rear] = r;
}

// Dequeue request
Request dequeue(Queue *q) {
    Request r = q->queue[q->front++];
    if (q->front > q->rear)
        q->front = q->rear = -1;
    return r;
}

int main() {
    Queue landingQueue, takeoffQueue;
    initQueue(&landingQueue);
    initQueue(&takeoffQueue);

    int runway1_time = 0, runway2_time = 0;
    int takeoffs = 0, landings = 0;
    int total_takeoff_wait = 0, total_landing_wait = 0;
    int current_time = 0;
    int request_id = 1;

    srand(time(NULL));

    for (current_time = 0; current_time < SIMULATION_TIME; current_time += REQUEST_INTERVAL) {
        // Generate one request (landing or takeoff)
        Request req;
        req.id = request_id++;
        req.time_stamp = current_time;

        int type = rand() % 2; // 0 = landing, 1 = takeoff
        if (type == 0)
            enqueue(&landingQueue, req);
        else
            enqueue(&takeoffQueue, req);

        // Assign requests to runway1
        if (runway1_time <= current_time) {
            if (!isEmpty(&landingQueue)) {
                Request r = dequeue(&landingQueue);
                total_landing_wait += current_time - r.time_stamp;
                runway1_time = current_time + OPERATION_TIME;
                landings++;
                printf("[Time %3d] Runway 1: Landing plane #%d\n", current_time, r.id);
            } else if (!isEmpty(&takeoffQueue)) {
                Request r = dequeue(&takeoffQueue);
                total_takeoff_wait += current_time - r.time_stamp;
                runway1_time = current_time + OPERATION_TIME;
                takeoffs++;
                printf("[Time %3d] Runway 1: Takeoff plane #%d\n", current_time, r.id);
            }
        }

        // Assign requests to runway2
        if (runway2_time <= current_time) {
            if (!isEmpty(&landingQueue)) {
                Request r = dequeue(&landingQueue);
                total_landing_wait += current_time - r.time_stamp;
                runway2_time = current_time + OPERATION_TIME;
                landings++;
                printf("[Time %3d] Runway 2: Landing plane #%d\n", current_time, r.id);
            } else if (!isEmpty(&takeoffQueue)) {
                Request r = dequeue(&takeoffQueue);
                total_takeoff_wait += current_time - r.time_stamp;
                runway2_time = current_time + OPERATION_TIME;
                takeoffs++;
                printf("[Time %3d] Runway 2: Takeoff plane #%d\n", current_time, r.id);
            }
        }
    }

    // Output results
    printf("\n=== Simulation Summary ===\n");
    printf("Total Landings Completed: %d\n", landings);
    printf("Total Takeoffs Completed: %d\n", takeoffs);

    if (landings > 0)
        printf("Average Landing Wait Time: %.2f minutes\n", (float)total_landing_wait / landings);
    else
        printf("Average Landing Wait Time: 0.00 minutes\n");

    if (takeoffs > 0)
        printf("Average Takeoff Wait Time: %.2f minutes\n", (float)total_takeoff_wait / takeoffs);
    else
        printf("Average Takeoff Wait Time: 0.00 minutes\n");

    // Show remaining queue contents
    printf("\nPlanes still waiting to Land:\n");
    while (!isEmpty(&landingQueue)) {
        Request r = dequeue(&landingQueue);
        printf("Plane #%d (Requested at %d mins)\n", r.id, r.time_stamp);
    }

    printf("\nPlanes still waiting to Takeoff:\n");
    while (!isEmpty(&takeoffQueue)) {
        Request r = dequeue(&takeoffQueue);
        printf("Plane #%d (Requested at %d mins)\n", r.id, r.time_stamp);
    }

    return 0;
}
