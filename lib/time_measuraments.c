#define _POSIX_C_SOURCE 199309L
#include "lib.h"
#include <time.h>

double measure_function_run(void *f, int *arr, unsigned int len){
    timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    ((void (*)(int *, unsigned int))f)(arr, len);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_nsec - start.tv_nsec);

    return elapsed;
}

double duration(timespec start, timespec end) {
    return end.tv_sec - start.tv_sec 
           + ((end.tv_nsec - start.tv_nsec ) / (double) 1000000000.0);
}
double getResolution() {
    timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do {
        clock_gettime(CLOCK_MONOTONIC, &end);
    } while (duration(start, end) == 0.0);
    return duration(start, end);
}