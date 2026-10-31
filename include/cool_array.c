#include "cool_array.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* -- internal usage stuff -- */

static Ca_Error ca_set_capacity(Cool_Array* a, size_t new_capacity) {

    if (new_capacity > SIZE_MAX / a->data_size)
        return CA_ERROR_OVERFLOW;

    char* new_data = realloc(a->data, new_capacity * a->data_size);
    if (!new_data)
        return CA_ERROR_ALLOC_FAIL;

    a->data = new_data;
    a->capacity = new_capacity;

    return CA_ERROR_YAY;

}

static Ca_Error ca_grow(Cool_Array* a) {

    if (a->capacity > SIZE_MAX / 2)
        return CA_ERROR_OVERFLOW;

    return ca_set_capacity(a, a->capacity * 2);

}

static Ca_Error ca_grow_if_needed(Cool_Array* a) {

    if (a->size < a->capacity)
        return CA_ERROR_YAY;

    return ca_grow(a);
    
}

/* ---- */

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

    Ca_Error grow_error = ca_grow_if_needed(a);
    if (grow_error)
        return grow_error;
    
    memmove(a->data + (at + 1) * a->data_size, a->data + at * a->data_size, (a->size - at) * a->data_size);
    memcpy(a->data + at * a->data_size, src, a->data_size);

    a->size++;
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

Ca_Error ca_get_safe(const Cool_Array* a, size_t at, void* output) {

    if (a == NULL || output == NULL)
        return CA_ERROR_NULL;

    if (at >= a->size)
        return CA_ERROR_INDEX;

    memcpy(output, a->data + at * a->data_size, a->data_size);
    return CA_ERROR_YAY;

}

Ca_Error ca_swap(Cool_Array* a, size_t pos_1, size_t pos_2) {

    if (a == NULL)
        return CA_ERROR_NULL;

    if (pos_1 >= a->size || pos_2 >= a->size)
        return CA_ERROR_INDEX;

    if (pos_1 == pos_2)
        return CA_ERROR_YAY;

    char* p1 = a->data + pos_1 * a->data_size;
    char* p2 = a->data + pos_2 * a->data_size;

    /* swap bytes around since theyre char pointers */
    for (size_t i = 0; i < a->data_size; i++) {

        char tmp = p1[i];

        p1[i] = p2[i];
        p2[i] = tmp;

    }

    return CA_ERROR_YAY;

}

Ca_Error ca_reverse(Cool_Array *a) {

    if (a == NULL)
        return CA_ERROR_NULL;

    if (a->size == 0)
        return CA_ERROR_YAY;

    for (size_t i = 0; i < a->size / 2; i++)
        ca_swap(a, i, a->size - 1 - i);

    return CA_ERROR_YAY;

}

Ca_Error ca_resize(Cool_Array* a, size_t new_size) {

    if (a == NULL)
        return CA_ERROR_NULL;

    if (new_size == a->size)
        return CA_ERROR_YAY;

    if (new_size > a->capacity) {

        Ca_Error cap_error = ca_set_capacity(a, new_size);
        if (cap_error)
            return cap_error;

    }

    if (new_size > a->size)
        memset(a->data + a->size * a->data_size, 0, (new_size - a->size) * a->data_size);

    a->size = new_size;
    return CA_ERROR_YAY;

}

Ca_Error ca_trim(Cool_Array* a) {

    if (a == NULL)
        return CA_ERROR_NULL;

    size_t new_capacity = (a->size != 0) ? a->size : 1;
    if (new_capacity == a->capacity)
        return CA_ERROR_YAY;

    return ca_set_capacity(a, new_capacity);

}

size_t ca_size(const Cool_Array* a) {

    return a->size;

}

size_t ca_capacity(const Cool_Array* a) {

    return a->capacity;

}

size_t ca_last_index(const Cool_Array* a) {

    return (a->size != 0) ? (a->size - 1) : 0;

}

bool ca_is_empty(const Cool_Array* a) {

    return (a->size == 0);

}

void ca_free(Cool_Array* a) {

    if (a == NULL)
        return;

    free(a->data);
    free(a);

}

void ca_clear(Cool_Array* a) {

    a->size = 0;

}