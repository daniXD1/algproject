#include "../lib.h"

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int firstOccurrence(int arr[], int low, int high, int value) {
    int i = low;
    while(i <= high){
        if(arr[i] == value){
            return i;
        }
        
        i++;
    }

    return high;
}

int partition(int arr[], int low, int high, int pivot) {
    int pos = firstOccurrence(arr, low, high, pivot);
    swap(&arr[pos], &arr[high]);
    
    int i = low - 1;
    int j;

    for (j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return i + 1;
}


int findMedian(int arr[], int start, int size) {
    int i, j;
    int greater, minor;

    for (i = start; i < start + size; i++) {
        greater = 0;
        minor = 0;
        
        for (j = start; j < start + size; j++){
            if (j != i) {
                if(arr[j] == arr[i]) {
                    greater++;
                    minor++;
                } else if (arr[j] > arr[i]) {
                    greater++;
                } else {
                    minor++;
                }
            }
        }

        if (greater >= floor((size-1)/2) && minor >= floor((size-1)/2)) {
            return arr[i];
        }
    }

    return start;
}

int medianOfMedians(int arr[], int low, int high) {
    int size = high - low + 1;
    
    if (size <= 5) {
        return findMedian(arr, low, size);
    }
    
    int numGroups = (size + 4) / 5;
    int *medians = (int *)malloc(numGroups * sizeof(int));
    int i;
    
    for (i = 0; i < numGroups; i++) {
        int groupStart = low + i * 5;
        int groupEnd = (groupStart + 4 < high) ? groupStart + 4 : high;
        
        medians[i] = findMedian(arr, groupStart, groupEnd - groupStart + 1);
    }

    if (numGroups > 5) {
        return medianOfMedians(medians, 0, numGroups);
    }
    
    return findMedian(medians, 0, numGroups);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = medianOfMedians(arr, low, high);
        int r = partition(arr, low, high, pi);
        quickSort(arr, low, r - 1);
        quickSort(arr, r + 1, high);
    }
}

void quickSort(int *arr, unsigned int n){
    quickSort_rec(arr, 0, n - 1);
}