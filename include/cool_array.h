#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef enum {

    CA_ERROR_YAY = 0,    /* no error */
    CA_ERROR_NULL,       /* null passed as argument */
    CA_ERROR_INDEX,      /* index out of range*/
    CA_ERROR_ALLOC_FAIL, /* out of memory / allocation fail */
    CA_ERROR_OVERFLOW,   /* would overflow if more memory was allocated for array */

    CA_ERROR_COUNT_, /* enum item count */

} Ca_Error;

typedef struct {

    char* data;
    size_t size, capacity, data_size;

} Cool_Array;

/* -- misc -- */

/* get error string for each enum item. returns "CA_ERROR_UNKNOWN" for out of bounds input */
const char* ca_get_error_string(Ca_Error error);

/* -- creation -- */

/* caller should free ; returns null on allocation failures */
Cool_Array* ca_create(size_t data_size);

/* -- usage & macros -- */

/* set element in position at to the contents of src */
Ca_Error ca_set_internal(Cool_Array* a, size_t at, const void* src);

/* insert content of src in position at */
Ca_Error ca_insert_internal(Cool_Array* a, size_t at, const void* src);

/* append src to last position */
Ca_Error ca_append_internal(Cool_Array* a, const void* src);

/* remove element at position at */
Ca_Error ca_remove(Cool_Array* a, size_t at);

/* get function with bounds checking. writes result to void* output */
Ca_Error ca_get_safe(const Cool_Array* a, size_t at, void* output);

/* swap position 1 and position 2's places */
Ca_Error ca_swap(Cool_Array* a, size_t pos_1, size_t pos_2);

/* reverse the array */
Ca_Error ca_reverse(Cool_Array* a);

/* change the size of array. new elements will be zero initialized */
Ca_Error ca_resize(Cool_Array* a, size_t new_size);

/* shrink capacity to size */
Ca_Error ca_trim(Cool_Array* a);

/* get size */
size_t ca_size(const Cool_Array* a);

/* get capacity */
size_t ca_capacity(const Cool_Array* a);

/* get last index (aka size - 1) */
size_t ca_last_index(const Cool_Array* a);

/* check if array is empty */
bool ca_is_empty(const Cool_Array* a);

/* free the array */
void ca_free(Cool_Array* a);

/* sets size to 0 but keeps capacity */
void ca_clear(Cool_Array* a);

/*
    ca: pointer to cool_array
    type: type which is stored in array (int, double, etc)
    at: size_t position of your crap
    value (...): what to put in the array
*/

#define ca_append(ca, type, ...) ca_append_internal((ca), (type[]){__VA_ARGS__})
#define ca_insert(ca, type, at, ...) ca_insert_internal((ca), (at), (type[]){__VA_ARGS__})
#define ca_set(ca, type, at, ...) ca_set_internal((ca), (at), (type[]){__VA_ARGS__})
#define ca_get(ca, type, at) (((type*)(ca)->data)[(at)])