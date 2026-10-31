#include <stdio.h>
#include "include/cool_array.h"

typedef struct {

    int x;
    double y;
    char z;
    char* str;

} Test_Struct;

void print_test_struct(Test_Struct* ts) {

    printf("- test struct: -\n");
    printf("x = %d\ny = %f\nz = %c\nstr = %s\n", ts->x, ts->y, ts->z, ts->str);
    printf("--------------\n");

}

int main(void) {

    Cool_Array* int_array = ca_create(sizeof(int));
    for (size_t i = 1; i <= 12000; i++)
        ca_append(int_array, int, (int)i);        

    for (size_t i = 0; i < (int_array->size - 1); i++)
        printf("[%zu] = %d\n", i, ca_get(int_array, int, i));

}