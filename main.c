#include <stdio.h>
#include "include/cool_array.h"

void print_int_array_hehe(Cool_Array* a) {

    int dest;
    Ca_Error err;

    for (size_t i = 0; i <= ca_last_index(a); i++) {

        err = ca_get_safe(a, i, (void*) &dest);
        if (!err)
            printf("[%zu] = %d\n", i, dest);
        else
            printf("access error code %d of pos %zu\n", err, i);

    }

    printf("size: %zu\n", ca_size(a));
    printf("cap: %zu\n", ca_capacity(a));
    printf("last i: %zu\n", ca_last_index(a));

}

int main(void) {

    Cool_Array* int_array = ca_create(sizeof(int));
    ca_append(int_array, int, 100);
    ca_append(int_array, int, 200);
    ca_append(int_array, int, 300);
    ca_append(int_array, int, 400);
    
    print_int_array_hehe(int_array);

    for (size_t i = 0; i <= 10; i++)
        ca_append(int_array, int, i);

    printf("create: \n");
    print_int_array_hehe(int_array);

    printf("swap 3,4\n");
    ca_swap(int_array, 3, 4);
    print_int_array_hehe(int_array);
    ca_reverse(int_array);
    print_int_array_hehe(int_array);

    ca_insert(int_array, int, int_array->size + 1, 99);
    ca_insert(int_array, int, int_array->size + 2, 255);
    ca_insert(int_array, int, int_array->size + 3, 14141);
    printf("invalid writes past: \n");
    print_int_array_hehe(int_array);

    ca_insert(int_array, int, -2, 6262);
    ca_insert(int_array, int, -1, 6262);
    printf("invalid writes neg: \n");
    print_int_array_hehe(int_array);

    ca_insert(int_array, int, 2, 200);
    ca_insert(int_array, int, 5, 300);
    ca_insert(int_array, int, 9, 400);
    printf("insert in middle\n");
    print_int_array_hehe(int_array);

    printf("insert in start\n");
    ca_insert(int_array, int, 0, 900);
    ca_insert(int_array, int, 0, 1000);
    print_int_array_hehe(int_array);

    printf("removes\n");
    ca_remove(int_array, 99);
    ca_remove(int_array, 200);
    ca_remove(int_array, -1);
    ca_remove(int_array, -2);
    ca_remove(int_array, 0);
    ca_remove(int_array, 8);
    ca_remove(int_array, ca_last_index(int_array));
    print_int_array_hehe(int_array);

    printf("trim\n");
    ca_trim(int_array);
    print_int_array_hehe(int_array);

    printf("resize to 30\n");
    ca_resize(int_array, 30);
    print_int_array_hehe(int_array);

    printf("resize to 5\n");
    ca_resize(int_array, 5);
    print_int_array_hehe(int_array);

    printf("REVERSE HELL YEAH\n");
    ca_reverse(int_array);
    print_int_array_hehe(int_array);
    
    ca_clear(int_array);
    printf("clear it\n");
    print_int_array_hehe(int_array);

    printf("trim\n");
    ca_trim(int_array);
    print_int_array_hehe(int_array);

    printf("refill:\n");
    for (size_t i = 0; i < 10; i++)
        ca_append(int_array, int, i * 100 + i * 10);

    print_int_array_hehe(int_array);

    printf("int_array: %p\n", (void*)int_array);
    printf("thats enough. be free!\n");

    ca_free(int_array);
    int_array = NULL;

    printf("finally: %p\n", (void*)int_array);

    return 0;

}