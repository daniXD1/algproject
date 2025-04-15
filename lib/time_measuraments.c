#include "lib.h"
#include <time.h>

double duration(timespec start, timespec end) {
    return end.tv_sec - start.tv_sec 
           + ((end.tv_nsec - start.tv_nsec ) / (double) 1000000000.0);
}

double measure_function_run(void *f, int *arr, int len){
    timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    ((void (*)(int *, unsigned int))f)(arr, len);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = duration(start, end);

    return elapsed;
}

double getResolution() {
    timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do {
        clock_gettime(CLOCK_MONOTONIC, &end);
    } while (duration(start, end) == 0.0);
    return duration(start, end);
}