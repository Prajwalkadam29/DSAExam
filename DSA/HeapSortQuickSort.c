#include <stdio.h>
#include <string.h>

typedef struct {
    char student_name[50];
    int student_roll_no;
    int total_marks;
} Student;

int swapCountHeap = 0, swapCountQuick = 0;

void swap(Student *a, Student *b, int *swapCount) {
    Student temp = *a;
    *a = *b;
    *b = temp;
    (*swapCount)++;
}

// Heapify function for Heap Sort
void heapify(Student arr[], int n, int i, int *swapCount) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left].student_roll_no > arr[largest].student_roll_no)
        largest = left;
    if (right < n && arr[right].student_roll_no > arr[largest].student_roll_no)
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest], swapCount);
        heapify(arr, n, largest, swapCount);
    }
}

void heapSort(Student arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i, &swapCountHeap);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i], &swapCountHeap);
        heapify(arr, i, 0, &swapCountHeap);
    }
}

// Partition for Quick Sort
int partition(Student arr[], int low, int high, int *swapCount) {
    int pivot = arr[high].student_roll_no;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].student_roll_no < pivot) {
            i++;
            swap(&arr[i], &arr[j], swapCount);
        }
    }
    swap(&arr[i+1], &arr[high], swapCount);
    return i + 1;
}

void quickSort(Student arr[], int low, int high, int *swapCount) {
    if (low < high) {
        int pi = partition(arr, low, high, swapCount);
        quickSort(arr, low, pi - 1, swapCount);
        quickSort(arr, pi + 1, high, swapCount);
    }
}

void printStudents(Student arr[], int n) {
    printf("Name\tRoll No\tTotal Marks\n");
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\n", arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
}

int main() {
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);

    Student arr1[n], arr2[n];
    for (int i = 0; i < n; i++) {
        printf("Enter name, roll no, total marks of student %d:\n", i+1);
        scanf("%s %d %d", arr1[i].student_name, &arr1[i].student_roll_no, &arr1[i].total_marks);
        arr2[i] = arr1[i];  // copy for quicksort
    }

    heapSort(arr1, n);
    printf("\nSorted by Heap Sort:\n");
    printStudents(arr1, n);
    printf("Heap Sort swaps: %d\n", swapCountHeap);

    quickSort(arr2, 0, n - 1, &swapCountQuick);
    printf("\nSorted by Quick Sort:\n");
    printStudents(arr2, n);
    printf("Quick Sort swaps: %d\n", swapCountQuick);

    return 0;
}