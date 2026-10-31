#include "cool_array.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

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

static Ca_Error ca_grow(Cool_Array* a) {

    if (a->capacity > SIZE_MAX / 2)
        return CA_ERROR_OVERFLOW;

    size_t new_capacity = a->capacity * 2;

    if (new_capacity > (SIZE_MAX / a->data_size))
        return CA_ERROR_OVERFLOW;

    char* new_data = realloc(a->data, a->capacity * a->data_size * 2);
    if (!new_data)
        return CA_ERROR_ALLOC_FAIL;

    a->data = new_data;
    a->capacity = new_capacity;

    return CA_ERROR_YAY;

}

static Ca_Error ca_grow_if_needed(Cool_Array* a) {

    if (a->size < a->capacity)
        return CA_ERROR_YAY;

    return ca_grow(a);
    
}

Ca_Error ca_set_internal(Cool_Array* a, size_t at, const void* src) {

    if (a == NULL || src == NULL)
        return CA_ERROR_NULL;

    if (at >= a->size)
        return CA_ERROR_INDEX;

    memcpy(a->data + at * a->data_size, src, a->data_size);
    return CA_ERROR_YAY;

}

Ca_Error ca_append_internal(Cool_Array* a, const void* src) {

    if (a == NULL || src == NULL)
        return CA_ERROR_NULL;

    Ca_Error grow_error = ca_grow_if_needed(a);
    if (grow_error)
        return grow_error;

    memcpy(a->data + a->size * a->data_size, src, a->data_size);
    a->size++;

    return CA_ERROR_YAY;

}

Ca_Error ca_insert_internal(Cool_Array* a, size_t at, const void* src) {

    if (a == NULL || src == NULL)
        return CA_ERROR_NULL;

    if (at > a->size)
        return CA_ERROR_INDEX;

    /*
    if (at == a->size) {

        ca_append_internal(a, src);
        return;

    }
    */

    Ca_Error grow_error = ca_grow_if_needed(a);
    if (grow_error)
        return grow_error;
    
    memmove(a->data + (at + 1) * a->data_size, a->data + at * a->data_size, (a->size - at) * a->data_size);

    a->size++;
    /* ca_set_internal(a, at, src); */
    return CA_ERROR_YAY;

}

Ca_Error ca_remove(Cool_Array* a, size_t at) {

    if (a == NULL)
        return CA_ERROR_NULL;

    if (at >= a->size)
        return CA_ERROR_INDEX;

    memmove(a->data + at * a->data_size, a->data + (at + 1) * a->data_size, (a->size - at - 1) * a->data_size);
    a->size -= 1;

    return CA_ERROR_YAY;

}

void ca_free(Cool_Array* a) {

    if (a == NULL)
        return;

    free(a->data);
    free(a);

}