#include "../lib.h"
#define N_GROUPS 5

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
    int greater, minor, equals;

    for (i = start; i < start + size; i++) {
        greater = 0;
        minor = 0;
        equals = 0;
        
        for (j = start; j < start + size; j++){
            if(arr[j] == arr[i]) {
                equals++;
            } else if (arr[j] > arr[i]) {
                greater++;
            } else {
                minor++;
            }
        }

        if (greater - minor <= equals) {
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
    
    int numGroups = ceil(size / N_GROUPS);
    int *medians = (int *)malloc(numGroups * sizeof(int));
    int i;
    
    for (i = 0; i < numGroups; i++) {
        int groupStart = low + i * N_GROUPS;
        int groupEnd = groupStart + N_GROUPS - 1;
        
        if (groupEnd > high) {
            groupEnd = high;
        }
        
        medians[i] = findMedian(arr, groupStart, groupEnd - groupStart + 1);
    }

    if (numGroups > N_GROUPS) {
        return medianOfMedians(medians, 0, numGroups);
    }
    
    return findMedian(medians, 0, numGroups);
}

void quickSortMedian_rec(int arr[], int low, int high) {
    if (low < high) {
        int pi = medianOfMedians(arr, low, high);
        int r = partition(arr, low, high, pi);
        quickSortMedian_rec(arr, low, r - 1);
        quickSortMedian_rec(arr, r + 1, high);
    }
}

void quickSortMedian(int *arr, unsigned int n){
    quickSortMedian_rec(arr, 0, n - 1);
}