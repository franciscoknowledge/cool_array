#pragma once

#include <stddef.h>

typedef struct {

    char* data;
    size_t size, capacity, data_size;

} Coolest_Array;

/* ---- creation ---- */

/* caller should free ; returns null on allocation failures */
Coolest_Array* ca_create(size_t data_size);

/* ---- internal ---- */

void _ca_grow_if_needed(Coolest_Array* a);
void _ca_set_internal(Coolest_Array* a, size_t at, void* src);
void _ca_append_internal(Coolest_Array* a, void* src);
void _ca_insert_internal(Coolest_Array* a, size_t at, void* src);

/* ---- usage ---- */

void ca_remove(Coolest_Array* a, size_t at);
void ca_free(Coolest_Array* a);

/*
    ca: pointer to cool_array
    type: type which is stored in array (int, double, etc)
    at: size_t position of your crap
    value: what to put in the array
*/

/* haha how did we not have a get function before?
#define ca_append(ca, type, value) _ca_append_internal((ca), &(type){value})
#define ca_get(ca, type, at) (((type*)(ca)->data)[at])
#define ca_set(ca, type, at, value) _ca_set_internal((ca), (at), &(type){value})
#define ca_insert(ca, type, at, value) _ca_insert_internal((ca), (at), &(type){value})
*/

#define ca_append(ca, type, ...) _ca_append_internal((ca), (type[]){__VA_ARGS__})
#define ca_insert(ca, type, at, ...) _ca_insert_internal((ca), (at), ((type)[]){__VA_ARGS__})
#define ca_set(ca, type, at, ...) _ca_set_internal((ca), (at), ((type)[]){__VA_ARGS__})
#define ca_get(ca, type, at) (((type*)(ca)->data)[(at)])