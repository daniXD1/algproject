#include "lib.h"

void write_dataline(FILE *file, double time, int data) {
    fprintf(file, "%lf, %d\n", time, data);
}