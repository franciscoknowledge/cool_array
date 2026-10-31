#pragma once

#include <stddef.h>

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

typedef struct {

    char* data;
    size_t size, capacity, data_size;

} Cool_Array;

/* -- creation -- */

/* caller should free ; returns null on allocation failures */
Cool_Array* ca_create(size_t data_size);

/* -- mostly internal use -- */

Ca_Error ca_set_internal(Cool_Array* a, size_t at, const void* src);
Ca_Error ca_append_internal(Cool_Array* a, const void* src);
Ca_Error ca_insert_internal(Cool_Array* a, size_t at, const void* src);

/* -- usage & macros -- */

Ca_Error ca_remove(Cool_Array* a, size_t at);

/* -- to free -- */

void ca_free(Cool_Array* a);

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