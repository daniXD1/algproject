#include "lib.h"

double* measure_batch(void (*f)(int *, unsigned int), unsigned int parameter, unsigned int batch_size, int * (*generator_function)(int)){
    double *results = calloc(batch_size+1, sizeof(double));
    
    for (unsigned int i = 0; i < batch_size; i++) {
        int* arr = ((int* (*)(int))generator_function)(parameter);
        results[i] = measure_function_run(f, arr, arr_len(arr));

        free(arr);
    }

    return results;
}

double* measure_batch_gen_included(void (*f)(int *, unsigned int), unsigned int parameter, unsigned int batch_size, int * (*generator_function)(int), int system_resolution){
    double *results = calloc(batch_size+1, sizeof(double));

    for (unsigned int i = 0; i < batch_size; i++) {
        timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        while(true){
            int* arr = ((int* (*)(int))generator_function)(parameter);
            ((void (*)(int *, unsigned int))f)(arr, arr_len(arr));
            clock_gettime(CLOCK_MONOTONIC, &end);
            if(duration(start, end) >= system_resolution) break;
            free(arr);
        }
        
        results[i] = duration(start, end);
    }
    
    return results;
}