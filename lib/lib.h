#ifndef ALGPROGLIB_H
#define ALGPROGLIB_H

#include <time.h>

double measure_function_run(void *f, unsigned int *arr, unsigned int len);

double getResolution();
double duration(struct timespec start, struct timespec end);

#endif
