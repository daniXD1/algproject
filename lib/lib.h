#ifndef ALGPROGLIB_H
#define ALGPROGLIB_H

#define static_array_len 10000
#define static_array_range 1000000

#include <stdio.h>
#include <stdlib.h>

typedef struct timespec timespec;

double getResolution();

double measure_function_run(void *f, int *arr, int len);
double* measure_batch(void *f, unsigned int parameter, unsigned int batch_size, int *generator_function);

int* gen_array_simple(int len);
int* gen_array_by_value_range(int range);
int* gen_array_by_different_elements(int n);
int arr_len(int *arr);

void write_dataline(FILE *file, double time, int data);

void countingSort(int arr[], unsigned int n);
void mergeSort(int arr[], unsigned int n);
void quickSort(int arr[], unsigned int n);
void quickSort3Way(int arr[], unsigned int n);
void insertionSort(int arr[], unsigned int n);
void heapSort(int arr[], unsigned int n);

#endif
