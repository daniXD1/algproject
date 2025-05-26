#include "../lib.h"

//#include <string.h>           <--- per il merge compatto

void merge(int *arr, int left, int mid, int right) {
    int half1 = mid - left + 1;
    int half2 = right - mid;

    int L[half1], R[half2];

    int i;
    int j;

    for (i = 0; i < half1; i++) {
        L[i] = arr[left + i];
    }

    for (j = 0; j < half2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    i = 0;
    j = 0;
    int k = left;

    while (i < half1 && j < half2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < half1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < half2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


/*              merge compatto
void merge(int *arr, int left, int mid, int right) {
    int half1 = mid - left + 1;
    int half2 = right - mid;

    int L[half1], R[half2];

    memcpy(L, arr + left, half1*sizeof(int));
    memcpy(R, arr + mid + 1, half2*sizeof(int));

    int i = 0, j = 0, k = left;

    while (i < half1 && j < half2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }

    while (i < half1) {
        arr[k++] = L[i++];
    }

    while (j < half2) {
        arr[k++] = R[j++];
    }
}*/


void mergeSort_rec(int *arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort_rec(arr, left, mid);
        mergeSort_rec(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void mergeSort(int *arr, unsigned int n) {
    mergeSort_rec(arr, 0, n - 1);
}