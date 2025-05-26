#include "../lib.h"
#include <math.h>

int right(int i){
    return 2*i + 1;
}

int left(int i){
    return 2*i;
}

void heapify(int *arr, int n, int i) {
    int m;
    int l = left(i);
    int r = right(i);

    if (l < n && arr[l] > arr[i]) {
        m = l;
    } else {
        m = i;
    }

    if (r < n && arr[r] > arr[m]) {
        m = r;
    }

    if (m != i) {
        int temp = arr[i];
        arr[i] = arr[m];
        arr[m] = temp;

        heapify(arr, n, m);
    }
}

void buildHeap(int *arr, int n) {
    int i;

    for (i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

void heapSort(int *arr, unsigned int n) {
    int i;
    
    buildHeap(arr, n);

    for (i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}