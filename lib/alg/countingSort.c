#include "../lib.h"

void countingSort(int arr[], int n) {
    int max = arr[0];
    int i;

    for (i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int count[max + 1];
    memset(count, 0, sizeof(count));

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