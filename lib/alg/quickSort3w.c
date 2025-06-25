#include "../lib.h"

void swap3w(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void partition3Way(int* arr, int low, int high, int* lt, int* gt) {
    int pivot = arr[high];
    int j = low;

    while (j < *gt) {
        if (arr[j] < pivot) {
            (*lt)++;
            swap3w(&arr[*lt], &arr[j]);
            j++;
        } else if (arr[j] > pivot) {
            (*gt)--;
            swap3w(&arr[*gt], &arr[j]);
        } else {
            j++;
        }
    }

    swap3w(&arr[*gt], &arr[high]);
    (*gt)++;
}

void quickSort3Way_rec(int* arr, int low, int high) {
    if (low < high) {
        int lt = low - 1;
        int gt = high;
        
        partition3Way(arr, low, high, &lt, &gt);
        
        quickSort3Way_rec(arr, low, lt);
        quickSort3Way_rec(arr, gt, high);
    }
}

void quickSort3Way(int *arr, unsigned int n){
    quickSort3Way_rec(arr, 0, n - 1);
}