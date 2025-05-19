#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Passenger structure
typedef struct {
    int arrival_time;
    int service_time;
} Passenger;

// Queues
Passenger frequent[MAX], regular[MAX];
int frontF = 0, rearF = -1;
int frontR = 0, rearR = -1;

// Enqueue functions
void enqueueFrequent(int arrival, int service) {
    rearF++;
    frequent[rearF].arrival_time = arrival;
    frequent[rearF].service_time = service;
}

void enqueueRegular(int arrival, int service) {
    rearR++;
    regular[rearR].arrival_time = arrival;
    regular[rearR].service_time = service;
}

// Dequeue functions
Passenger dequeueFrequent() {
    return frequent[frontF++];
}

Passenger dequeueRegular() {
    return regular[frontR++];
}

// Check if queues are empty
int isFrequentEmpty() {
    return frontF > rearF;
}

int isRegularEmpty() {
    return frontR > rearR;
}

// Main simulation
int main() {
    int nF, nR;
    int time = 0, servedF = 0, servedR = 0;
    int waitTimeF = 0, waitTimeR = 0;

    printf("Enter number of Frequent Flyers: ");
    scanf("%d", &nF);
    for (int i = 0; i < nF; i++) {
        int at, st;
        printf("Frequent Flyer %d - Arrival Time and Service Time: ", i + 1);
        scanf("%d %d", &at, &st);
        enqueueFrequent(at, st);
    }

    printf("Enter number of Regular Customers: ");
    scanf("%d", &nR);
    for (int i = 0; i < nR; i++) {
        int at, st;
        printf("Regular Customer %d - Arrival Time and Service Time: ", i + 1);
        scanf("%d %d", &at, &st);
        enqueueRegular(at, st);
    }

    printf("\n--- Starting Simulation ---\n");

    int countF = 0;
    while (!isFrequentEmpty() || !isRegularEmpty()) {
        Passenger p;

        // Serve 2 frequent flyers for every 1 regular
        if (!isFrequentEmpty() && (countF < 2 || isRegularEmpty())) {
            if (frequent[frontF].arrival_time <= time) {
                p = dequeueFrequent();
                waitTimeF += time - p.arrival_time;
                printf("Time %d: Serving Frequent Flyer (Service Time %d)\n", time, p.service_time);
                time += p.service_time;
                servedF++;
                countF++;
                continue;
            }
        }

        if (!isRegularEmpty()) {
            if (regular[frontR].arrival_time <= time) {
                p = dequeueRegular();
                waitTimeR += time - p.arrival_time;
                printf("Time %d: Serving Regular Customer (Service Time %d)\n", time, p.service_time);
                time += p.service_time;
                servedR++;
                countF = 0; // reset frequent flyer counter
                continue;
            }
        }

        // If no one is ready to be served, increment time
        time++;
    }

    // Averages
    float avgF = servedF ? (float)waitTimeF / servedF : 0;
    float avgR = servedR ? (float)waitTimeR / servedR : 0;

    printf("\n--- Simulation Complete ---\n");
    printf("Average Waiting Time (Frequent Flyers): %.2f\n", avgF);
    printf("Average Waiting Time (Regular Customers): %.2f\n", avgR);

    return 0;
}
