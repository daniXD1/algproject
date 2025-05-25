#include "lib.h"

void write_dataline(FILE *file, double time) {
    fprintf(file, "%lf\n", time);
}

// I dont remember what data is for -_-
void write_dataline_ahh(FILE *file, double time, int data) {
    fprintf(file, "%lf, %d\n", time, data);
}

int write_logfile(char *s, double *times, unsigned int n){
    FILE *f=fopen(s, "w");
    if(f==NULL){
        puts("Error opening file");
        return -1;
    }

    for(int i=0; i<n; i++){
        write_dataline(f, times[i]);
    }
    return 0;
}