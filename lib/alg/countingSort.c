#include "../lib.h"

void countingSort(int *arr, unsigned int n, unsigned int range) {
    //cambiare la firma della funzione per passare range e elemento minimo (o anche solo range)
    
    int i;

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