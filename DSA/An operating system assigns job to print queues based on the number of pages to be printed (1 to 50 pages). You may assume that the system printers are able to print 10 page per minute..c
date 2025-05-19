#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define JOBS 100
#define MAX_PAGES 50
#define PAGES_PER_MINUTE 10
#define MAX_PRINTERS 3

typedef struct {
    int id;
    int pages;
    int arrival_time;
} Job;

typedef struct {
    Job job;
    int start_time;
    int end_time;
    int printer_id;
} PrintedJob;

// Priority Queue using Min-Heap
Job jobQueue[JOBS];
int jobCount = 0;

// Insert job into priority queue
void insertJob(Job j) {
    jobQueue[jobCount] = j;
    int i = jobCount;
    while (i > 0 && jobQueue[(i - 1) / 2].pages > jobQueue[i].pages) {
        Job temp = jobQueue[i];
        jobQueue[i] = jobQueue[(i - 1) / 2];
        jobQueue[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
    jobCount++;
}

// Remove job with smallest page count
Job removeMin() {
    Job min = jobQueue[0];
    jobQueue[0] = jobQueue[--jobCount];
    int i = 0;
    while (2 * i + 1 < jobCount) {
        int child = 2 * i + 1;
        if (child + 1 < jobCount && jobQueue[child + 1].pages < jobQueue[child].pages)
            child++;
        if (jobQueue[i].pages <= jobQueue[child].pages)
            break;
        Job temp = jobQueue[i];
        jobQueue[i] = jobQueue[child];
        jobQueue[child] = temp;
        i = child;
    }
    return min;
}

void simulate(int printers, Job jobs[JOBS]) {
    PrintedJob result[JOBS];
    int resultCount = 0;
    int time = 0;
    int printerAvailable[MAX_PRINTERS] = {0};

    jobCount = 0; // clear priority queue
    for (int i = 0; i < JOBS; i++) {
        insertJob(jobs[i]);
    }

    while (resultCount < JOBS) {
        for (int p = 0; p < printers; p++) {
            if (printerAvailable[p] <= time && jobCount > 0) {
                Job j = removeMin();
                int duration = (j.pages + PAGES_PER_MINUTE - 1) / PAGES_PER_MINUTE;
                printerAvailable[p] = time + duration;

                result[resultCount].job = j;
                result[resultCount].start_time = time;
                result[resultCount].end_time = printerAvailable[p];
                result[resultCount].printer_id = p + 1;
                resultCount++;
            }
        }
        time++;
    }

    printf("\n=== Simulation with %d Printer(s) ===\n", printers);
    printf("JobID\tPages\tArrival\tStart\tEnd\tPrinter\n");
    for (int i = 0; i < JOBS; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
            result[i].job.id,
            result[i].job.pages,
            result[i].job.arrival_time,
            result[i].start_time,
            result[i].end_time,
            result[i].printer_id
        );
    }

    int maxTime = 0;
    for (int i = 0; i < printers; i++) {
        if (printerAvailable[i] > maxTime)
            maxTime = printerAvailable[i];
    }

    printf("Total Time to complete all jobs with %d printer(s): %d minutes\n", printers, maxTime);
}

int main() {
    Job jobs[JOBS];

    srand(time(NULL));

    // Generate 100 print jobs
    for (int i = 0; i < JOBS; i++) {
        jobs[i].id = i + 1;
        jobs[i].pages = (rand() % MAX_PAGES) + 1;  // 1 to 50 pages
        jobs[i].arrival_time = i; // one per minute
    }

    // Simulate for 1, 2, and 3 printers
    simulate(1, jobs);
    simulate(2, jobs);
    simulate(3, jobs);

    return 0;
}
