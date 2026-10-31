#pragma once

#include <stddef.h>
#include <stdbool.h>

/*
    it would be nice to pass the size of element via the macros to the internal functions,
    to catch differing data sizes

    ca_get has no bounds checks and can't return an error code sooo i guess that has to be investigated
*/

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

/* 
    TODO: swap, resize, reserve, pop, back, front, reverse
*/

typedef struct {

    char* data;
    size_t size, capacity, data_size;

} Cool_Array;

/* -- creation -- */

/* caller should free ; returns null on allocation failures */
Cool_Array* ca_create(size_t data_size);
void ca_free(Cool_Array* a);

/* -- mostly internal use -- */

Ca_Error ca_set_internal(Cool_Array* a, size_t at, const void* src);
Ca_Error ca_append_internal(Cool_Array* a, const void* src);
Ca_Error ca_insert_internal(Cool_Array* a, size_t at, const void* src);
Ca_Error ca_remove(Cool_Array* a, size_t at);
Ca_Error ca_get_safe(Cool_Array* a, size_t at, void* output); /* just in case i guess */

/* -- usage & macros -- */

/* checks */

size_t ca_size(Cool_Array* a);
size_t ca_capacity(Cool_Array* a);
size_t ca_last_index(Cool_Array* a);

bool ca_is_empty(Cool_Array* a);

/* some operations */

/* shrink capacity to size */
Ca_Error ca_trim(Cool_Array* a);

/* nuke all elements but keep capacity */
void ca_clear(Cool_Array* a);

/*
    ca: pointer to cool_array
    type: type which is stored in array (int, double, etc)
    at: size_t position of your crap
    value: what to put in the array
*/

#define ca_append(ca, type, ...) ca_append_internal((ca), (type[]){__VA_ARGS__})
#define ca_insert(ca, type, at, ...) ca_insert_internal((ca), (at), ((type)[]){__VA_ARGS__})
#define ca_set(ca, type, at, ...) ca_set_internal((ca), (at), (type)[]){__VA_ARGS__})
#define ca_get(ca, type, at) (((type*)(ca)->data)[(at)])