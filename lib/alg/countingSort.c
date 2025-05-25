#include "../lib.h"

void countingSort(int *arr, unsigned int n) {
    int max = arr[0];
    int i;

    for (i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    unsigned int *count=calloc(max+1, sizeof(int));

    for (i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    int index = 0;
    
    for (i = 0; i <= max; i++) {
        while (count[i] > 0) {
            arr[index++] = i;
            count[i]--;
        }
    }
}