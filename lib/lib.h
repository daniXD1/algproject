#ifndef ALGPROGLIB_H
#define ALGPROGLIB_H

#include <time.h>

double measure_function_run(void *f, unsigned int *arr, unsigned int len);

double getResolution();
double duration(struct timespec start, struct timespec end);

void countingSort(unsigned int arr[], unsigned int n);
void mergeSort(unsigned int arr[], unsigned int n);
void quickSort(unsigned int arr[], unsigned int n);
void quickSort3Way(unsigned int arr[], unsigned int n);
void insertionSort(unsigned int arr[], unsigned int n);
void heapSort(unsigned int arr[], unsigned int n);

#endif
