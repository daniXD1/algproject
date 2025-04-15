#include "lib.h"
#include <stdlib.h>

int* gen_array(int len){
    int *arr = calloc(len, sizeof(int));
    for (int i = 0; i < len; i++) {
        arr[i] = (rand() % 999990)+10;
    }
    return arr;
}

double* measure_batch(void *f, int arr_len, unsigned int batch_size){
    double *results = calloc(batch_size, sizeof(double));
    
    for (unsigned int i = 0; i < batch_size; i++) {
        int* arr = gen_array(arr_len);
        results[i] = measure_function_run(f, arr, arr_len);
        free(arr);
    }

    return results;
}