#include "include/coolest_array.h"
#include <string.h>
#include <stdlib.h>

Coolest_Array* ca_create(size_t data_size) {

    Coolest_Array* new = malloc(sizeof(Coolest_Array));

    if (!new)
        return NULL;

    new->data_size = data_size;

    new->size = 0;
    new->capacity = 1;

    new->data = malloc(data_size);

    if (!new->data){

        free(new);
        return NULL;

    }

    return new;

}

void ca_grow(Coolest_Array* a) {

    char* new_data = realloc(a->data, a->capacity * a->data_size * 2);
    if (!new_data)
        return;

    a->data = new_data;
    a->capacity *= 2;

}

void _ca_grow_if_needed(Coolest_Array* a) {

    if (a->size + 1 > a->capacity) 
        ca_grow(a);
    
}

void _ca_set_internal(Coolest_Array* a, size_t at, void* src) {

    if (at >= a->size)
        return;

    memcpy(a->data + at * a->data_size, src, a->data_size);

}

void _ca_append_internal(Coolest_Array* a, void* src) {

    _ca_grow_if_needed(a);

    memcpy(a->data + a->size * a->data_size, src, a->data_size);
    a->size++;

}

void _ca_insert_internal(Coolest_Array* a, size_t at, void* src) {

    if (at > a->size)
        return;

    if (at == a->size) {

        _ca_append_internal(a, src);
        return;

    }

    _ca_grow_if_needed(a);

    memmove(a->data + (at + 1) * a->data_size, a->data + at * a->data_size, (a->size - at) * a->data_size);

    a->size++;
    _ca_set_internal(a, at, src);

}

void ca_remove(Coolest_Array* a, size_t at) {

    if (at >= a->size)
        return;

    memmove(a->data + at * a->data_size, a->data + (at + 1) * a->data_size, (a->size - at - 1) * a->data_size);
    a->size -= 1;

}

void ca_free(Coolest_Array* a) {

    if (a == NULL)
        return;

    free(a->data);
    free(a);

}