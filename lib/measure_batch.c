#include "lib.h"

double* measure_batch(void *f, unsigned int parameter, unsigned int batch_size, int *generator_function){
    double *results = calloc(batch_size, sizeof(double));
    
    for (unsigned int i = 0; i < batch_size; i++) {
        int* arr = ((int* (*)(int))generator_function)(parameter);
        results[i] = measure_function_run(f, arr, arr_len(arr));
        free(arr);
    }

    return results;
}