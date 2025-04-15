#include <stdio.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 3-way partition QuickSort function
void quickSort3Way(int arr[], int low, int high) {
    if (low < high) {
        int lt = low;       // Index for elements less than pivot
        int gt = high;      // Index for elements greater than pivot
        int pivot = arr[low]; // Choosing the first element as the pivot
        int i = low;

        while (i <= gt) {
            if (arr[i] < pivot) {
                swap(&arr[i], &arr[lt]);
                lt++;
                i++;
            } else if (arr[i] > pivot) {
                swap(&arr[i], &arr[gt]);
                gt--;
            } else {
                i++;
            }
        }

        // Recursively sort the partitions
        quickSort3Way(arr, low, lt - 1);
        quickSort3Way(arr, gt + 1, high);
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Main function to test 3-way QuickSort
int main() {
    int arr[] = {4, 9, 4, 4, 8, 7, 4, 6, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: \n");
    printArray(arr, n);

    quickSort3Way(arr, 0, n - 1);

    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;
}