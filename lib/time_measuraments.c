#include "lib.h"

double measure_function_run(void *f, unsigned int *arr, unsigned int len){
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    ((void (*)(unsigned int *, unsigned int))f)(arr, len);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_nsec - start.tv_nsec);

    return elapsed;
}

