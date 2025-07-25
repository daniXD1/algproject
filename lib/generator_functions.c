#include "lib.h"

int* gen_array_simple(int len){
    int *arr = calloc(len+1, sizeof(int));
    for (int i = 0; i < len; i++) {
        arr[i] = (rand() % static_array_range);
    }
    arr[len]=(int)'\0';
    return arr;
}

int* gen_array_by_different_elements(int n){
    int *rnd_elements = calloc(n+1, sizeof(int));
    int *arr = calloc(static_array_len, sizeof(int));
    for (int i = 0; i < n; i++) {
        rnd_elements[i] = (rand() % static_array_range);
    }

    for (int i = 0; i < static_array_len; i++) {
        arr[i] = rnd_elements[rand() % n];
    }
    free(rnd_elements);
    arr[static_array_len]=(int)'\0';
    return arr;
}

int* gen_array_sorted(int len){
    int *arr = calloc(len+1, sizeof(int));
    for (int i = 0; i < len; i++) {
        arr[i] = i;
    }
    arr[len]=(int)'\0';
    return arr;
}

int* gen_array_reverse_sorted(int len){
    int *arr = calloc(len+1, sizeof(int));
    for (int i = len-1; i >= 0; i--) {
        arr[i] = len-i;
    }
    arr[len]=(int)'\0';
    return arr;
}

void debug_print_array(int *a, int len){
    puts("[");
    for(int i=0; i<len; i++) printf(" %d", a[i]);
    puts(" ]");
    return;
}

int arr_len(int *arr){
    int i = 0;
    while (arr[i] != (int)'\0') {
        i++;
    }
    return i;
}