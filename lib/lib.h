#ifndef ALGPROGLIB_H
#define ALGPROGLIB_H

#define _POSIX_C_SOURCE 199309L

#define static_array_len 100000
#define static_array_range 1000000
//#define static_array_range __INT_MAX__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>


typedef struct timespec timespec;

double getResolution();

double measure_function_run(void (*f)(int *, unsigned int), int *arr, int len);
double* measure_batch(void (*f)(int *, unsigned int), unsigned int parameter, unsigned int batch_size, int * (*generator_function)(int));
double* measure_batch_gen_included(void (*f)(int *, unsigned int), unsigned int parameter, unsigned int batch_size, int * (*generator_function)(int), int system_resolution);

double duration(timespec start, timespec end);

int* gen_array_simple(int len);
#define GEN_ARRAY_SIMPLE 0

int* gen_array_by_different_elements(int n);
#define GEN_ARRAY_DIFFERENT 1

int* gen_array_sorted(int len);
#define GEN_ARRAY_SORTED 2

int* gen_array_reverse_sorted(int len);
#define GEN_ARRAY_REVERSE_SORTED 3

int arr_len(int *arr);

void write_dataline(FILE *file, double time);
int write_logfile(char *name, double *times, unsigned int n, unsigned int parameter, unsigned short generator_function);

void countingSort(int *arr, unsigned int n);
void mergeSort(int *arr, unsigned int n);
void quickSort(int *arr, unsigned int n);
void quickSortMedian(int *arr, unsigned int n);
void quickSortSelect(int *arr, unsigned int n);
void quickSortMedianOptimized(int *arr, unsigned int n);
void quickSort3Way(int *arr, unsigned int n);
void insertionSort(int *arr, unsigned int n);
void heapSort(int *arr, unsigned int n);

void quickSortMedianPartial(int *arr, unsigned int n);

void swap(int* a, int* b);

#endif
