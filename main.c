#include <stdio.h>
#include "include/coolest_array.h"

typedef struct {

    int x;
    double y;
    char z;

} Test_Struct;

int main(void) {

    Test_Struct test = {

        .x = 9999,
        .y = 0.1111,
        .z = '!'

    };

    Coolest_Array* struct_array = ca_create(sizeof(Test_Struct));
    _ca_append_internal(struct_array, &test);

}