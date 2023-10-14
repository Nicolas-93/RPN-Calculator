#include "vector.h"
#include <string.h>
#include <assert.h>

VectorError _Vector_realloc(Vector* self, size_t new_capacity);

VectorError Vector_init(
    Vector* self,
    size_t element_size,
    size_t initial_capacity,
    int (*cmp)(const void*, const void*)
) {
    *self = (Vector) {
        .capacity = initial_capacity,
        .element_size = element_size,
        .len = 0,
        .cmp = cmp,
    };

    self->arr = malloc(element_size * initial_capacity);

    if (self->arr == NULL)
        return VECTOR_ERR_ALLOC;

    return VECTOR_ERR_NONE;
}

VectorError _Vector_realloc(Vector* self, size_t new_capacity) {
    uint8_t* new_arr = realloc(self->arr, new_capacity * self->element_size);

    if (new_arr == NULL)
        return VECTOR_ERR_ALLOC;

    self->arr = new_arr;
    self->capacity = new_capacity;

    return VECTOR_ERR_NONE;
}

VectorError Vector_append(Vector* self, void* elem) {
    if (self->len >= self->capacity) {
        VectorError err = _Vector_realloc(self, self->capacity + VECTOR_REALLOC_BLOCK);

        if (err < 0)
            return err;
    }

    memcpy(self->arr + self->len * self->element_size, (uint8_t*) elem, self->element_size);
    self->len++;

    return VECTOR_ERR_NONE;
}

void* Vector_get(const Vector* self, int64_t i) {

    if (i < 0)
        i = self->len + i;

    if (i >= self->len)
        return NULL;

    return self->arr + i * self->element_size;
}

void* Vector_pop(Vector* self) {
    if (self->len == 0)
        return NULL;

    uint8_t* popped = self->arr + (--(self->len)) * self->element_size;

    return popped;
}

void Vector_resize(Vector* self, size_t new_size) {
    assert(new_size >= 0);
    self->len = new_size;
}

VectorError Vector_shrink_to_fit(Vector* self) {
    return _Vector_realloc(self, self->len);
}

void Vector_free(Vector* self) {
    free(self->arr);
    *self = (Vector) {0};
}

void Vector_clear(Vector* self) {
    self->len = 0;
}

size_t Vector_get_length(const Vector* self) {
    return self->len;
}

void Vector_sort(Vector* self) {
    assert(self->cmp);

    qsort(
        self->arr,
        self->len,
        self->element_size,
        self->cmp
    );
}

void* Vector_search(Vector* self, void* searched_value) {
    assert(self->cmp);

    return bsearch(
        searched_value,
        self->arr,
        self->len,
        self->element_size,
        self->cmp
    );
}
