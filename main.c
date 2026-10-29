#include <stdio.h>
#include "include/coolest_array.h"

int main(void) {

    Coolest_Array* int_array = ca_create(sizeof(int));
    Coolest_Array* double_array = ca_create(sizeof(double));

    ca_append(int_array, int, 250);
    ca_append(int_array, int, 600);
    ca_append(int_array, int, 1997);
    ca_append(int_array, int, 1983);

    ca_append(double_array, double, 0.99239);

    ca_insert(int_array, int, 0, 999);
    ca_insert(int_array, int, 0, 0);
    ca_insert(int_array, int, 0, -120);
    
    for (size_t i = 0; i < int_array->size; i++) {

        printf("%d\n", ca_get(int_array, int, i));

    }

    printf("------------\n");

    for (size_t i = 0; i < double_array->size; i++) {

        printf("%f\n", ca_get(double_array, double, i));

    }

}