#ifndef ALGPROGLIB_H
#define ALGPROGLIB_H

typedef struct timespec timespec;

double measure_function_run(void *f, int *arr, unsigned int len);

double getResolution();
double duration(timespec start, timespec end);

double* measure_batch(void *f, int arr_len, unsigned int batch_size);

void countingSort(int arr[], unsigned int n);
void mergeSort(int arr[], unsigned int n);
void quickSort(int arr[], unsigned int n);
void quickSort3Way(int arr[], unsigned int n);
void insertionSort(int arr[], unsigned int n);
void heapSort(int arr[], unsigned int n);

#endif
