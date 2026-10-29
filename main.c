#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* HOLY SHIT THIS CODE IS RADIOACTIVE */
/* TODO: errors NEED to be handled properly on allocations & etc etc */

typedef struct {

    char* data;
    size_t size, capacity, data_size;

} Coolest_Array;

/* caller should free ; returns null on allocation failures */
Coolest_Array* ca_create(size_t data_size) {

    Coolest_Array* new = malloc(sizeof(Coolest_Array));

    /* allocation failure */
    if (!new)
        return NULL;

    new->data_size = data_size;

    new->size = 0;
    new->capacity = 1;

    new->data = malloc(data_size);

    /* allocation failure */
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

    /*
    for (size_t i = a->size; i > at; i--) {

        memmove(a->data + i * a->data_size, a->data + (i - 1) * a->data_size, a->data_size);

    }
    */

    memmove(a->data + (at + 1) * a->data_size, a->data + at * a->data_size, (a->size - at) * a->data_size);

    a->size++;
    _ca_set_internal(a, at, src);

}

void ca_remove(Coolest_Array* a, size_t at) {

    if (at >= a->size)
        return;

    /* does the removed element need to be freed here? */
    /* ^^ not if the element doesnt own its own heap memory */

    /* ditch
    for (size_t i = at; i + 1 < a->size; i++) {

        memmove(a->data + i * a->data_size, a->data + (i + 1) * a->data_size, a->data_size);

    }
    */

    /* its possible to just move everything all at once */
    memmove(a->data + at * a->data_size, a->data + (at + 1) * a->data_size, (a->size - at - 1) * a->data_size);

    a->size -= 1;

}

void ca_free(Coolest_Array* a) {

    if (a == NULL)
        return;

    free(a->data);
    free(a);

}

#define ca_append(ca, type, value) _ca_append_internal((ca), &(type){value})
#define ca_get(ca, type, at) (((type*)(ca)->data)[at])
#define ca_set(ca, type, at, value) _ca_set_internal((ca), (at), &(type){value})
#define ca_insert(ca, type, at, value) _ca_insert_internal((ca), (at), &(type){value})

int main(void) {

    Coolest_Array* int_array = ca_create(sizeof(int));
    Coolest_Array* double_array = ca_create(sizeof(double));

    ca_append(int_array, int, 250);
    ca_append(int_array, int, 600);
    ca_append(int_array, int, 1997);
    ca_append(int_array, int, 1983);

    ca_append(double_array, double, 0.99239);

    ca_insert(int_array, int, 0, 999);
    ca_insert(int_array, int, 0, 0);
    ca_insert(int_array, int, 0, -120);
    //ca_set(int_array, int, 2, 67676767);

    for (size_t i = 0; i < int_array->size; i++) {

        printf("%d\n", ca_get(int_array, int, i));

    }

    printf("------------\n");

    for (size_t i = 0; i < double_array->size; i++) {

        printf("%f\n", ca_get(double_array, double, i));

    }

}