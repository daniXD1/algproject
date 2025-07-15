#include "./lib/lib.h"
#include <stdio.h>
#include <time.h>

int min_param = 100;
int max_param = 1000000;
// Default range for different elements generation

double exponential_step = 1.09749876549305610989775307413179551147080372752868932886445899804013989385;
// Default step for 100 points on simple generation 

unsigned int batch_size = 10;
int generator_id = GEN_ARRAY_DIFFERENT; // Change this to test different generators
char *logfile_format = "./log-%s-%07d.txt";


int main(){
    srand(time(NULL));
    double r=getResolution();
    printf("Resolution: %lf ms\n", r);

    int* (*generator_function)(int) = NULL;
    switch(generator_id){
        case GEN_ARRAY_SIMPLE:
            generator_function = gen_array_simple;
            break;
        case GEN_ARRAY_DIFFERENT:
            generator_function = gen_array_by_different_elements;
            exponential_step = 1.047128548050899533464502031528140079056791471503929212005652529901257764102372;
            // Exponential step for 100 points on different elements generation
            max_param = static_array_len;
            break;
        case GEN_ARRAY_SORTED:
            generator_function = gen_array_sorted;
            break;
        case GEN_ARRAY_REVERSE_SORTED:
            generator_function = gen_array_reverse_sorted;
            break;
        default:
            printf("Invalid generator index\n");
            return -1;
    }


    double n=(double)min_param;
    while(n < max_param){
        printf("Current parameter: %lf\n", n);
        double *times=measure_batch(quickSortSelect, (unsigned int)n, batch_size, generator_function);
        char *fname=calloc(100, sizeof(char));
        sprintf(fname, logfile_format, "quickSortSelect_different", (unsigned int)n);
        write_logfile(fname, times, batch_size, (unsigned int)n, generator_id);
        free(fname);
        free(times);
        n = n * exponential_step;
    }
    return 0;
}
