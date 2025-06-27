#include "../lib.h"
#define N_GROUPS 5

// Helper function to find the first occurrence of a value in a subarray
int firstOccurrencePartial(int arr[], int low, int high, int value) {
    for (int i = low; i <= high; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return high;
}

// partitionMedianPartial function using a given pivot value
int partitionMedianPartial(int arr[], int low, int high, int pivot) {
    int pos = firstOccurrencePartial(arr, low, high, pivot);
    swap(&arr[pos], &arr[high]);
    
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

// Finds the median of a small subarray (<= 5 elements)
int findMedianPartial(int arr[], int start, int size) {
    for (int i = start; i < start + size; i++) {
        int greater = 0, minor = 0, equals = 0;
        for (int j = start; j < start + size; j++) {
            if (arr[j] == arr[i]) equals++;
            else if (arr[j] > arr[i]) greater++;
            else minor++;
        }
        if (abs(greater - minor) <= equals) {
            return arr[i];
        }
    }
    return arr[start];
}

// Computes the Median of Medians (used only once)
int medianOfMediansPartial(int arr[], int low, int high) {
    int size = high - low + 1;
    if (size <= 5) {
        return findMedianPartial(arr, low, size);
    }
    
    int numGroups = (size + N_GROUPS - 1) / N_GROUPS; // Equivalent to ceil(size / N_GROUPS)
    int *medians = (int *)malloc(numGroups * sizeof(int));
    
    for (int i = 0; i < numGroups; i++) {
        int groupStart = low + i * N_GROUPS;
        int groupEnd = (groupStart + N_GROUPS - 1 < high) ? groupStart + N_GROUPS - 1 : high;
        medians[i] = findMedianPartial(arr, groupStart, groupEnd - groupStart + 1);
    }
    
    int median = (numGroups <= 5) ? 
        findMedianPartial(medians, 0, numGroups) : 
        medianOfMediansPartial(medians, 0, numGroups - 1);
    
    free(medians);
    return median;
}

// Modified QuickSort that uses MoM only once
void quickSortMedianPartial_rec(int arr[], int low, int high, bool useMom) {
    if (low < high) {
        int pivot;
        if (useMom) {
            // Compute MoM only once (first call)
            pivot = medianOfMediansPartial(arr, low, high);
        } else {
            // Fall back to a simpler pivot (e.g., last element)
            pivot = arr[high];
        }
        
        int r = partitionMedianPartial(arr, low, high, pivot);
        quickSortMedianPartial_rec(arr, low, r - 1, false); // No more MoM
        quickSortMedianPartial_rec(arr, r + 1, high, false); // No more MoM
    }
}

// Entry point for QuickSort with MoM optimization (used only once)
void quickSortMedianPartial(int *arr, unsigned int n) {
    if (n <= 1) return;
    quickSortMedianPartial_rec(arr, 0, n - 1, true); // First call uses MoM
}