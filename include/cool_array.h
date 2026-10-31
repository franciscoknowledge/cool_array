#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct {

    char* data;
    size_t size, capacity, data_size;

} Cool_Array;

/* -- creation -- */

/* caller should free ; returns null on allocation failures */
Cool_Array* ca_create(size_t data_size);

/* -- mostly internal use -- */

void ca_set_internal(Cool_Array* a, size_t at, void* src);
void ca_append_internal(Cool_Array* a, void* src);
void ca_insert_internal(Cool_Array* a, size_t at, void* src);

/* -- usage & macros -- */

void ca_remove(Cool_Array* a, size_t at);
void ca_free(Cool_Array* a);

/*
    ca: pointer to cool_array
    type: type which is stored in array (int, double, etc)
    at: size_t position of your crap
    value: what to put in the array
*/

#define ca_append(ca, type, ...) ca_append_internal((ca), (type[]){__VA_ARGS__})
#define ca_insert(ca, type, at, ...) ca_insert_internal((ca), (at), ((type)[]){__VA_ARGS__})
#define ca_set(ca, type, at, ...) ca_set_internal((ca), (at), ((type)[]){__VA_ARGS__})
#define ca_get(ca, type, at) (((type*)(ca)->data)[(at)])