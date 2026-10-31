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

    /* this leaks the string lol */

    Test_Struct test = {

        .x = 9999,
        .y = 0.1111,
        .z = '!',
        .str = "abc",

    };

    Test_Struct test_2 = {

        .x = 112,
        .y = -0.28213,
        .z = '?',
        .str = "ghghg",

    };

    Cool_Array* struct_array = ca_create(sizeof(Test_Struct));
    ca_append_internal(struct_array, &test);
    ca_append(struct_array, Test_Struct, test_2);
    ca_append(struct_array, Test_Struct, {.x = -255, .y = -1.250, .z = 'A', .str = "aaaaaaAAAAAA"});

    for (size_t i = 0; i < struct_array->size; i++)
        print_test_struct(&ca_get(struct_array, Test_Struct, i));

    ca_free(struct_array);

}