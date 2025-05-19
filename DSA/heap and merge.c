#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int roll_no;
    float marks;
};

int heapSwaps = 0;

// Swap function
void swap(struct Student *a, struct Student *b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
    heapSwaps++;
}

// -------- HEAP SORT --------
void heapify(struct Student arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l].roll_no > arr[largest].roll_no)
        largest = l;
    if (r < n && arr[r].roll_no > arr[largest].roll_no)
        largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(struct Student arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// -------- MERGE SORT --------
void merge(struct Student arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    struct Student L[50], R[50];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;

    while (i < n1 && j < n2) {
        if (L[i].roll_no <= R[j].roll_no)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(struct Student arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// -------- DISPLAY --------
void display(struct Student arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("Roll No: %d, Name: %s, Marks: %.2f\n", arr[i].roll_no, arr[i].name, arr[i].marks);
}

// -------- MAIN --------
int main() {
    int n;
    struct Student arr[50], heapArr[50], mergeArr[50];

    printf("Enter number of students: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter name, roll no, marks: ");
        scanf("%s %d %f", arr[i].name, &arr[i].roll_no, &arr[i].marks);
    }

    // Copy for heap and merge sort
    for (int i = 0; i < n; i++) {
        heapArr[i] = arr[i];
        mergeArr[i] = arr[i];
    }

    // Heap Sort
    heapSort(heapArr, n);
    printf("\nHeap Sort (by Roll No):\n");
    display(heapArr, n);
    printf("Total swaps in Heap Sort: %d\n", heapSwaps);

    // Merge Sort
    mergeSort(mergeArr, 0, n - 1);
    printf("\nMerge Sort (by Roll No):\n");
    display(mergeArr, n);

    return 0;
}
