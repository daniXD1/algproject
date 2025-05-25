#include "../lib.h"

void swap3w(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort3Way_rec(int *arr, int low, int high) {
    if (low < high) {
        int lt = low;
        int gt = high;
        int pivot = arr[low];
        int i = low;

        while (i <= gt) {
            if (arr[i] < pivot) {
                swap3w(&arr[i], &arr[lt]);
                lt++;
                i++;
            } else if (arr[i] > pivot) {
                swap3w(&arr[i], &arr[gt]);
                gt--;
            } else {
                i++;
            }
        }

        quickSort3Way_rec(arr, low, lt - 1);
        quickSort3Way_rec(arr, gt + 1, high);
    }
}

void quickSort3Way(int *arr, unsigned int n){
    quickSort3Way_rec(arr, 0, n - 1);
}