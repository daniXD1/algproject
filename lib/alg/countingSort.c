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

int getMin(int *arr, int n){
    int i = 0;
    int min = arr[0];
    
    for (i = 1; i < n; i++) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }

    return min;
}

void countingSort(int *arr, unsigned int n) {
    int i;

    int max = getMax(arr, n);
    int min = getMin(arr, n);
    int range=max - min;;
    //printf("Max: %d, Min: %d, Range: %d\n", max, min, range);

    int *occurr = (int *)malloc((range + 1) * sizeof(int));
    int *sorted = (int *)malloc(n * sizeof(int));

    for(i = 0; i <= range; i++) {
        occurr[i] = 0;
    }

    for(i = 0; i < n; i++) {
        occurr[arr[i]-min]++;
    }

    for(i = 1; i <= range; i++) {
        occurr[i] += occurr[i-1];
    }

    for(i = n - 1; i >= 0; i--) {
        sorted[occurr[arr[i]-min] - 1] = arr[i];
        occurr[arr[i]-min]--;
    }

    for(i = 0; i < n; i++) {
        arr[i] = sorted[i];
    }
}