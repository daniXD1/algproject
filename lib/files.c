#include "lib.h"

void write_dataline(FILE *file, double time) {
    fprintf(file, "%lf\n", time);
}

// I dont remember what data is for -_-
void write_dataline_ahh(FILE *file, double time, int data) {
    fprintf(file, "%lf, %d\n", time, data);
}

int write_logfile(char *name, double *times, unsigned int n, unsigned int parameter, unsigned short generator_function){
    if(generator_function > 5){
        puts("Invalid generator function");
        return -1;
    }

    FILE *f=fopen(name, "w");
    if(f==NULL){
        puts("Error opening file");
        return -1;
    }

    fprintf(f, "Batch size: %u\n", n);
    fprintf(f, "Parameter: %u\n", parameter);

    switch(generator_function){
        case GEN_ARRAY_SIMPLE:
            fprintf(f, "Generator: Simple\n");
            break;
        case GEN_ARRAY_RANGE:
            fprintf(f, "Generator: Range\n");
            break;
        case GEN_ARRAY_DIFFERENT:
            fprintf(f, "Generator: Different\n");
            break;
        case GEN_ARRAY_SORTED:
            fprintf(f, "Generator: Sorted\n");
            break;
        case GEN_ARRAY_REVERSE_SORTED:
            fprintf(f, "Generator: Reverse\n");
            break;
        default:
            printf("Invalid generator index\n");
            return -1;
    }
    for(int i=0; i<n; i++){
        write_dataline(f, times[i]);
    }
    fclose(f);
    return 0;
}

int write_logfile_raw(char *name, double *times, unsigned int n){
    FILE *f=fopen(name, "w");
    if(f==NULL){
        puts("Error opening file");
        return -1;
    }
    
    for(int i=0; i<n; i++){
        write_dataline(f, times[i]);
    }
    fclose(f);
    return 0;
}