#include "cool_array.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

Cool_Array* ca_create(size_t data_size) {

    if (data_size == 0)
        return NULL;

    Cool_Array* new = malloc(sizeof(Cool_Array));

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

void ca_grow(Cool_Array* a) {

    char* new_data = realloc(a->data, a->capacity * a->data_size * 2);
    if (!new_data)
        return;

    a->data = new_data;
    a->capacity *= 2;

}

void ca_grow_if_needed(Cool_Array* a) {

    if (a->size + 1 > a->capacity) 
        ca_grow(a);
    
}

void ca_set_internal(Cool_Array* a, size_t at, void* src) {

    if (at >= a->size)
        return;

    memcpy(a->data + at * a->data_size, src, a->data_size);

}

void ca_append_internal(Cool_Array* a, void* src) {

    ca_grow_if_needed(a);

    memcpy(a->data + a->size * a->data_size, src, a->data_size);
    a->size++;

}

void ca_insert_internal(Cool_Array* a, size_t at, void* src) {

    if (at > a->size)
        return;

    if (at == a->size) {

        ca_append_internal(a, src);
        return;

    }

    ca_grow_if_needed(a);

    memmove(a->data + (at + 1) * a->data_size, a->data + at * a->data_size, (a->size - at) * a->data_size);

    a->size++;
    ca_set_internal(a, at, src);

}

void ca_remove(Cool_Array* a, size_t at) {

    if (at >= a->size)
        return;

    memmove(a->data + at * a->data_size, a->data + (at + 1) * a->data_size, (a->size - at - 1) * a->data_size);
    a->size -= 1;

}

void ca_free(Cool_Array* a) {

    if (a == NULL)
        return;

    free(a->data);
    free(a);

}