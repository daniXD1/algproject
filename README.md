# Algproject

## Data Generation
```c
// Functions to generate arrays
int* gen_array_simple(int len)
int* gen_array_by_value_range(int range)
int* gen_array_by_different_elements(int n)
```

## Time Measurements
```c
// Measure execution time of sort function on array
double measure_function_run(void (*f)(int *, unsigned int), int *arr, int len)

// Measures execution time of sort function on batch_size arrays generated by passing the parameter to the generator function
double* measure_batch(void (*f)(int *, unsigned int), unsigned int parameter, unsigned int batch_size, int * (*generator_function)(int))
```

## Logging
```c
// Logs to file an array of n elements that are the execution times for each run
int write_logfile(char *name, double *times, unsigned int n, unsigned int parameter, unsigned short generator_function)
// Also writes headers in the form
// Bach Size: <n>
// Parameter: <parameter>
// Generator:
//      GEN_ARRAY_SIMPLE: simple (gen_array_simple)
//      GEN_ARRAY_RANGE: range (gen_array_by_value range)
//      GEN_ARRAY_DIFFERENT: different (gen_array_by_different_elements)
```