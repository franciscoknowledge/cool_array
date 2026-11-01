#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/cool_array.h"

#define ERR_ARRAY_SIZE 100

typedef struct {

    size_t current_index;
    Ca_Error errors[ERR_ARRAY_SIZE];

} Error_Storage;

/* just for debugging */
#define print(...)       \
    printf(__VA_ARGS__); \
    putchar('\n')

void print_int_array(Cool_Array* a) {

    print("-- int_array --");

    for (size_t i = 0; i < ca_size(a); i++) {

        print("[%zu] = %d", i, ca_get(a, int, i));

    }

    print("\nsize: %zu", ca_size(a));
    print("capacity: %zu", ca_capacity(a));
    print("last index: %zu", ca_last_index(a));
    print("is empty: %d", ca_is_empty(a));

    print("----");

}

/* this is all really bad yes but i just want something done fast */
/* CA_ERROR_COUNT_ is just meant to indicate a "blank state". it will print unknown */

void es_print_errors(Error_Storage* es) {

    /* print until a CA_ERROR_COUNT_ is found */

    if (es->errors[0] == CA_ERROR_COUNT_) {

        print("no errors to print");
        return;
        
    }

    print("errors:");

    for (size_t i = 0; i < ERR_ARRAY_SIZE; i++) {

        if (es->errors[i] >= CA_ERROR_COUNT_)
            return;

        putchar('>');
        print("%s", ca_get_error_string(es->errors[i]));

    }

}

void es_add_error(Error_Storage* es, Ca_Error err) {

    es->errors[es->current_index] = err;
    es->current_index++;

}

void es_reset(Error_Storage* es) {

    es->current_index = 0;

    for (size_t i = 0; i < ERR_ARRAY_SIZE; i++)
        es->errors[i] = CA_ERROR_COUNT_;

}

int main(void) {

    int ints[5] = {100, 200, 300, 400, 500};
    int ints_again[5] = {9000, 9200, 9300, 9400, 9500};

    int get_output = 0;

    size_t temp_size;
    size_t temp_capacity;

    Cool_Array* int_array = ca_create(sizeof(int));
    Cool_Array* empty_array = ca_create(sizeof(char));
    Cool_Array* tiny_array = ca_create(0);

    /* just so i dont need to use the pointer every time */
    Error_Storage* errors = malloc(sizeof(Error_Storage));

    print("is the error printing stuff working ? ");

    es_reset(errors);
    es_print_errors(errors); /* nothing should print here */

    print("created arrays");
    print("is the tiny_array NULL?: %d", (tiny_array == NULL));

    /* append test */

    print("\nappend test:");
        
        es_add_error(errors, ca_append_internal(int_array, &ints[0]));
        es_add_error(errors, ca_append_internal(int_array, &ints[1]));
        es_add_error(errors, ca_append_internal(int_array, NULL));
        es_add_error(errors, ca_append_internal(NULL, &ints[0]));

        /* try to trigger overflow error in the capacity > SIZE_MAX / 2 check with ca_grow*/

        temp_size = int_array->size;
        temp_capacity = int_array->capacity;

        int_array->capacity = SIZE_MAX / 2 + 1;
        int_array->size = int_array->capacity;

        /* should be an overflow */
        es_add_error(errors, ca_append_internal(int_array, &ints[0]));

        int_array->capacity = temp_capacity;
        int_array->size = temp_size;

        es_print_errors(errors);

    print_int_array(int_array);

    /* set test */

    es_reset(errors);
    print("\nset test:");

        es_add_error(errors, ca_set_internal(int_array, 0, &ints_again[0]));
        es_add_error(errors, ca_set_internal(int_array, 1, &ints_again[4]));
        es_add_error(errors, ca_set_internal(int_array, 2, &ints[4]));
        es_add_error(errors, ca_set_internal(int_array, 10, &ints[3]));
        es_add_error(errors, ca_set_internal(int_array, 0, NULL));
        es_add_error(errors, ca_set_internal(NULL, 0, &ints[2]));

        es_print_errors(errors);

    print_int_array(int_array);

    /* insert test */

    es_reset(errors);
    print("\ninsert test:");

        es_add_error(errors, ca_insert_internal(int_array, 0, &ints_again[0]));
        es_add_error(errors, ca_insert_internal(int_array, 3, &ints[3]));
        es_add_error(errors, ca_insert_internal(int_array, 99, &ints_again[4]));
        es_add_error(errors, ca_insert_internal(int_array, 0, NULL));
        es_add_error(errors, ca_insert_internal(NULL, 0, &ints_again[0]));

        es_print_errors(errors);

    print_int_array(int_array);

    /* remove test */

    es_reset(errors);
    print("\nremove test:");

        es_add_error(errors, ca_remove(int_array, 0));
        es_add_error(errors, ca_remove(int_array, int_array->size - 1));
        es_add_error(errors, ca_remove(int_array, 999));
        es_add_error(errors, ca_remove(NULL, int_array->size - 1));

        es_print_errors(errors);

    print_int_array(int_array);

    /* safe get test */

    es_reset(errors);
    print("\nsafe get test:");

        es_add_error(errors, ca_get_safe(int_array, 0, &get_output));
        es_add_error(errors, ca_get_safe(int_array, 2, &get_output));
        es_add_error(errors, ca_get_safe(int_array, 999, &get_output));
        es_add_error(errors, ca_get_safe(NULL, 0, &get_output));
        es_add_error(errors, ca_get_safe(int_array, 0, NULL));

        es_print_errors(errors);
    
    print_int_array(int_array);

    /* swap test */

    es_reset(errors);
    print("\nswap test:");

        es_add_error(errors, ca_swap(int_array, 0, 1));
        es_add_error(errors, ca_swap(int_array, 4, 2));
        es_add_error(errors, ca_swap(int_array, 0, 9999));
        es_add_error(errors, ca_swap(NULL, 0, 1));

        es_print_errors(errors);

    print_int_array(int_array);

    /* reverse test */

    es_reset(errors);
    print("\nreverse test:");

        es_add_error(errors, ca_reverse(int_array));
        es_add_error(errors, ca_reverse(NULL));

        es_print_errors(errors);

    print_int_array(int_array);

    /* resize test */

    es_reset(errors);
    print("\nresize test:");

        print("set to 20:");
        es_add_error(errors, ca_resize(int_array, 20));
        print_int_array(int_array);

        print("set to 5:");
        es_add_error(errors, ca_resize(int_array, 5));
        es_add_error(errors, ca_resize(NULL, 100));

        print("try to overflow");
        es_add_error(errors, ca_resize(int_array, SIZE_MAX));

        print("try to create allocate failure");
        es_add_error(errors, ca_resize(int_array, SIZE_MAX / sizeof(int)));

        es_print_errors(errors);

    print_int_array(int_array);

    /* trim test */

    es_reset(errors);
    print("\ntrim test:");

        es_add_error(errors, ca_trim(int_array));
        es_add_error(errors, ca_trim(NULL));

        es_print_errors(errors);

    print_int_array(int_array);

    /* getter tests */

    es_reset(errors);
    print("\ngetter tests:");

        print("ca_size of int_array: %zu", ca_size(int_array));
        print("ca_size of NULL: %zu", ca_size(NULL));

        print("ca_capacity of int_array: %zu", ca_capacity(int_array));
        print("ca_capacity of NULL: %zu", ca_capacity(NULL));

        print("ca_is_empty with int_array: %d ", ca_is_empty(int_array));
        print("ca_is_empty with empty array: %d ", ca_is_empty(empty_array));
        print("ca_is_empty with NULL: %d ", ca_is_empty(NULL));
        
    print_int_array(int_array);

    /* clear test */

    es_reset(errors);
    print("\nclear test:");

        ca_clear(int_array);

    print_int_array(int_array);

    ca_free(int_array);
    ca_free(empty_array);
    free(errors);

}