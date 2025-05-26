#include "../lib.h"

void insertionSort(int *arr, unsigned int n) {
    int j;

    for (j = 2; j < n; j++) {
        int i = j - 1;
        int key = arr[j];
        
        while (j > 0 && arr[i] > key) {
            arr[i + 1] = arr[i];
            i--;
        }
        
        arr[i + 1] = key;
    }
}