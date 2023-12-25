#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdint.h>

typedef enum VectorError {
    VECTOR_ERR_NONE = 0,
    VECTOR_ERR_ALLOC = -1,
} VectorError;

typedef struct Vector {
    size_t len;
    size_t capacity;
    size_t element_size;
    int (*cmp)(const void*, const void*);
    uint8_t* arr;
} Vector;

#define VECTOR_REALLOC_BLOCK 10

// https://stackoverflow.com/questions/28524896/casting-pointer-to-memory-buffer-to-pointer-to-vla
// int (*arrPointer)[ARRSIZE] = (int(*)[ARRSIZE]) pointer;
#define VECTOR_DECLARE_VLA(self, typename, array_name) \
    typename (*array_name)[self.len] = ((typename(*)[self.len]) (typename*) self.arr)

#define VECTOR_DECLARE_ARRAY(self, typename, array_name) \
    typename* array_name = (typename*) (self).arr

// #define Vector_pop_t(self, elem_type) ((elem_type) Vector_pop(self))

/**
 * @brief Create a new vector object
 * 
 * @param self Vector to initialize
 * @param element_size Size of one element
 * @param initial_capacity Preallocation size
 * @param cmp Comparison function used to sort array if needed,
 * if sorting is not used, set to NULL
 * @return VectorError
 * if error while allocation : VECTOR_ERR_ALLOC
 */
VectorError Vector_init(
    Vector* self,
    size_t element_size,
    size_t initial_capacity,
    int (*cmp)(const void*, const void*)
);

/**
 * @brief Add to element end of the vector
 * 
 * @param self Vector object
 * @param elem Element to add
 * @return VectorError 
 */
VectorError Vector_append(Vector* self, void* elem);

/**
 * @brief Get element's address at index i if positive,
 * len - i, if negative
 * @param self Vector object
 * @param i index
 * @return void* 
 */
void* Vector_get(const Vector* self, int64_t i);

/**
 * @brief Vector pop last element
 * 
 * @param self Vector object
 */
void* Vector_pop(Vector* self);

/**
 * @brief Resize vector
 * old_size <= new_size : Nothing
 * old_size > new_size : Removes elements to fit
 * 
 * @param self 
 * @param new_size new size
 */
void Vector_resize(Vector* self, size_t new_size);

/**
 * @brief Reduce memory usage by reducing capacity
 * to vector's length
 * 
 * @param self 
 */
VectorError Vector_shrink_to_fit(Vector* self);

/**
 * @brief Free Vector object
 * 
 * @param self 
 */
void Vector_free(Vector* self);

/**
 * @brief Clear Vector object
 * 
 * @param self 
 */
void Vector_clear(Vector* self);

/**
 * @brief Get Vector's length
 * 
 * @param self 
 * @return size_t 
 */
size_t Vector_get_length(const Vector* self);

/**
 * @brief Sort's vector
 * 
 * @param self 
 */
void Vector_sort(Vector* self);

/**
 * @brief Search value in vector
 * 
 * @param self 
 * @param searched_value 
 * @return void* 
 */
void* Vector_search(Vector* self, void* searched_value);

#endif
