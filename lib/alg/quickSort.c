#include "../lib.h"


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int n){
    quickSort_rec(arr, 0, n - 1);
}

void quickSort_rec(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort_rec(arr, low, pi - 1);
        quickSort_rec(arr, pi + 1, high);
    }
}