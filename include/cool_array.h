#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef enum {

    CA_ERROR_YAY = 0, /* no error */
    CA_ERROR_NULL, /* null passed as argument */
    CA_ERROR_INDEX, /* index out of range*/
    CA_ERROR_ALLOC_FAIL, /* out of memory / allocation fail */
    CA_ERROR_OVERFLOW, /* would overflow if more memory was allocated for array */

} Ca_Error;

/*
    intention is to check errors like this, since CA_ERROR_YAY is 0:
    Ca_Error error = ca_remove(a, 1);
    if (error)
        return error;
*/

typedef struct {

    char* data;
    size_t size, capacity, data_size;

} Cool_Array;

/* -- creation -- */

Cool_Array* ca_create(size_t data_size); /* caller should free ; returns null on allocation failures */

/* -- usage & macros -- */

Ca_Error ca_set_internal(Cool_Array* a, size_t at, const void* src); /* set element in position at to the contents of src */
Ca_Error ca_append_internal(Cool_Array* a, const void* src); /* append src to last position */
Ca_Error ca_insert_internal(Cool_Array* a, size_t at, const void* src); /* insert content of src in position at */
Ca_Error ca_remove(Cool_Array* a, size_t at); /* remove element at position at */
Ca_Error ca_get_safe(const Cool_Array* a, size_t at, void* output); /* get function with bounds checking. writes result to void* output */
Ca_Error ca_swap(Cool_Array* a, size_t pos_1, size_t pos_2); /* swap position 1 and position 2's places*/
Ca_Error ca_reverse(Cool_Array* a); /* reverse the array */
Ca_Error ca_resize(Cool_Array* a, size_t new_size); /* change the size of array. new elements will be zero initialized */
Ca_Error ca_trim(Cool_Array* a); /* shrink capacity to size */

size_t ca_size(const Cool_Array* a); /* get size */
size_t ca_capacity(const Cool_Array* a); /* get capacity */
size_t ca_last_index(const Cool_Array* a); /* get last index (aka size - 1) */

bool ca_is_empty(const Cool_Array* a); /* check if array is empty */

void ca_free(Cool_Array* a); /* free the array */
void ca_clear(Cool_Array* a); /* sets size to 0 but keeps capacity */

/*
    ca: pointer to cool_array
    type: type which is stored in array (int, double, etc)
    at: size_t position of your crap
    value (...): what to put in the array
*/
#define ca_append(ca, type, ...) ca_append_internal((ca), (type[]){__VA_ARGS__})
#define ca_insert(ca, type, at, ...) ca_insert_internal((ca), (at), ((type)[]){__VA_ARGS__})
#define ca_set(ca, type, at, ...) ca_set_internal((ca), (at), (type)[]){__VA_ARGS__})
#define ca_get(ca, type, at) (((type*)(ca)->data)[(at)])