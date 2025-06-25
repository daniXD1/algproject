#include "lib.h"

double* measure_batch(void (*f)(int *, unsigned int), unsigned int parameter, unsigned int batch_size, int * (*generator_function)(int)){
    double *results = calloc(batch_size+1, sizeof(double));
    
    for (unsigned int i = 0; i < batch_size; i++) {
        int* arr = ((int* (*)(int))generator_function)(parameter);
        results[i] = measure_function_run(f, arr, arr_len(arr));
        /*for(unsigned int j = 0; j < arr_len(arr)-1; j++) {
            if(arr[j] > arr[j+1]) {
                puts("Error: Array not sorted");
                exit(EXIT_FAILURE);
            }
        }*/
        free(arr);
    }

    return results;
}