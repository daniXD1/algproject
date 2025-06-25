#include "./lib/lib.h"
#include "./utils/utils.h"
#include <stdio.h>
#include <time.h>

//IMPORTANT:
//    Configure those values to generate the data files

int min_param = 100;
int max_param = 1000000;
//double exponential_step =1.3593563908785256228; // For 30 points
double exponential_step = 1.58489319246111348520210137339150701326944213382503906831629681231665686366; // For 20 points
unsigned int batch_size = 20;
int generator_id = GEN_ARRAY_SIMPLE; // Change this to test different generators
char *logfile_format = "out/log-%s-%06d.txt";


int main(){
    srand(time(NULL));
    double r=getResolution();
    printf("Resolution: %lf ns\n", r);

    int* (*generator_function)(int) = NULL;
    switch(generator_id){
        case GEN_ARRAY_SIMPLE:
            generator_function = gen_array_simple;
            break;
        case GEN_ARRAY_RANGE:
            generator_function = gen_array_by_value_range;
            break;
        case GEN_ARRAY_DIFFERENT:
            generator_function = gen_array_by_different_elements;
            break;
        default:
            printf("Invalid generator index\n");
            return -1;
    }

    double n=(double)min_param;
    while(n < max_param){
        printf("Current parameter: %lf\n", n);
        double *times = measure_batch(insertionSort, (unsigned int)n, batch_size, generator_function);
        char *fname=calloc(100, sizeof(char));
        sprintf(fname, logfile_format, "insertionSort", (unsigned int)n);
        write_logfile(fname, times, batch_size, (unsigned int)n, generator_id);
        free(fname);
        free(times);
        n = n * exponential_step;
    }
    
    return 0;
}