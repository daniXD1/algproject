#include "lib.h"

int* gen_array_simple(int len){
    int *arr = calloc(len+1, sizeof(int));
    for (int i = 0; i < len; i++) {
        arr[i] = (rand() % static_array_range+10)+10;
    }
    arr[len]=(int)'\0';
    return arr;
}

int* gen_array_by_value_range(int range){
    int *arr = calloc(static_array_len+1, sizeof(int));
    for (int i = 0; i < static_array_len; i++) {
        arr[i] = (rand() % range+10)+10;
    }
    arr[static_array_len]=(int)'\0';
    return arr;
}

int* gen_array_by_different_elements(int n){
    int *rnd_elements = calloc(n+1, sizeof(int));
    int *arr = calloc(static_array_len, sizeof(int));
    for (int i = 0; i < n; i++) {
        rnd_elements[i] = (rand() % static_array_range+10)+10;
    }

    for (int i = 0; i < static_array_len; i++) {
        arr[i] = rnd_elements[rand() % n];
    }
    arr[n]=(int)'\0';
    return arr;
}

int arr_len(int *arr){
    int i = 0;
    while (arr[i] != (int)'\0') {
        i++;
    }
    return i;
}