#include "../lib.h"
#define N_GROUPS 5

int firstOccurrenceSelect(int arr[], int low, int high, int value) {
    int i = low;
    while(i <= high){
        if(arr[i] == value){
            return i;
        }
        
        i++;
    }

    return high;
}

int partitionSelect(int arr[], int low, int high, int pivot) {
    int pos = firstOccurrenceSelect(arr, low, high, pivot);
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


int findMedianSelect(int arr[], int start, int size) {
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

    return arr[start];
}

int Select(int arr[], int low, int high, int position){
    int size = high - low + 1;

    if (size <= 5) {
        return findMedianSelect(arr, low, size);
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
        
        medians[i] = findMedianSelect(arr, groupStart, groupEnd - groupStart + 1);
    }

    int pivot = Select(medians, 0, numGroups - 1, numGroups / 2);
    free(medians);

    int r = partitionSelect(arr, low, high, pivot);

    if (r == position) {
        return arr[r];
    } else if (r > position) {
        return Select(arr, low, r - 1, position);
    } else {
        return Select(arr, r + 1, high, position);
    }
}

void quickSortSelect_rec(int arr[], int low, int high) {
    if (low < high) {
        int pi = Select(arr, low, high, low + (high-low)/2);
        int r = partitionSelect(arr, low, high, pi);
        quickSortSelect_rec(arr, low, r - 1);
        quickSortSelect_rec(arr, r + 1, high);
    }
}

void quickSortSelect(int *arr, unsigned int n){
    quickSortSelect_rec(arr, 0, n - 1);
}