#include "../lib.h"

int getMax(int *arr, int n){
    int i = 0;
    int max = arr[0];
    
    for (i = 1; i < n; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}

void countingSort(int *arr, unsigned int n) {
    int i;

    int range = getMax(arr, n);

    int *occurr = (int *)malloc((range + 1) * sizeof(int));
    int *sorted = (int *)malloc(n * sizeof(int));

    for(i = 0; i <= range; i++) {
        occurr[i] = 0;
    }

    for(i = 0; i < n; i++) {
        occurr[arr[i]]++;
    }

    for(i = 1; i <= range; i++) {
        occurr[i] += occurr[i-1];
    }

    for(i = n - 1; i >= 0; i--) {
        sorted[occurr[arr[i]] - 1] = arr[i];
        occurr[arr[i]]--;
    }

    for(i = 0; i < n; i++) {
        arr[i] = sorted[i];
    }
}