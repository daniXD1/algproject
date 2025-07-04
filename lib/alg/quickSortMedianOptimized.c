#include "../lib.h"
#include <math.h>
#define N_GROUPS 5

int pow_manual(int base, int exp){
    int r=base;
    for(int i=1; i<exp; i++)r*=base;
    return r;
}

int firstOccurrenceOptimized(int arr[], int low, int high, int value) {
    int i = low;
    while(i <= high){
        if(arr[i] == value){
            return i;
        }
        
        i++;
    }

    return high;
}

int partitionMediansOptimized(int arr[], int low, int high) {
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


int findMedianOptimized(int arr[], int start, int size) {
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

int medianOfMediansOptimized(int arr[], int low, int high) {
    int size = high - low + 1;
    
    if (size <= 5) {
        return findMedianOptimized(arr, low, size);
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
        
        medians[i] = findMedianOptimized(arr, groupStart, groupEnd - groupStart + 1);
    }

    if (numGroups > N_GROUPS) {
        return medianOfMediansOptimized(medians, 0, numGroups);
    }
    
    return findMedianOptimized(medians, 0, numGroups);
}

void randomPivotOptimized(int arr[], int low, int high){
    int random = rand() % (high - low);
    int pivot = low + random;
    
    swap(&arr[pivot], &arr[high]);
}

void quickSortMedianOptimized_rec(int arr[], int low, int high, int levelOfMedian, int maxMedianLevel) {
    if (low < high) {
        int pi;
        
        if(levelOfMedian > maxMedianLevel) {
            randomPivotOptimized(arr, low, high);
        } else {
            pi = medianOfMediansOptimized(arr, low, high);

            int pos = firstOccurrenceOptimized(arr, low, high, pi);
            swap(&arr[pos], &arr[high]);
        }

        int r = partitionMediansOptimized(arr, low, high);
        
        quickSortMedianOptimized_rec(arr, low, r - 1, levelOfMedian + 1, maxMedianLevel);
        quickSortMedianOptimized_rec(arr, r + 1, high, levelOfMedian + 1, maxMedianLevel);
    }
}

int getMaxMedianLevel(unsigned int  n) {
    int i;
    for (i = 0; pow_manual(2,i) < n; i++){

    }

    if (i - 1 < 10){
        return 1;
    }
    
    return i - 9;
}

void quickSortMedianOptimized(int *arr, unsigned int n){
    int maxMedianLevel = getMaxMedianLevel(n);
    
    quickSortMedianOptimized_rec(arr, 0, n - 1, 0, maxMedianLevel);
}