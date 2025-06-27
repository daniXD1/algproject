#include "../lib.h"

int partitionRand(int *arr, int low, int high) {
    int random = rand() % (high - low);
    int pivot = low + random;
    
    swap(&arr[pivot], &arr[high]);

    int i = low - 1;
    int j;

    for (j = low; j < high; j++) {
        if (arr[j] < arr[high]) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    
    return i + 1;
}

void quickSortRand_rec(int *arr, int low, int high) {
    if (low < high) {
        int pi = partitionRand(arr, low, high);

        quickSortRand_rec(arr, low, pi - 1);
        quickSortRand_rec(arr, pi + 1, high);
    }
}

void quickSortRand(int *arr, unsigned int n){
    quickSortRand_rec(arr, 0, n - 1);
}