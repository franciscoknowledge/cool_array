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

    return 0;

}