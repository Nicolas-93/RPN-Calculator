#ifndef STACK_H
#define STACK_H

#include "vector.h"

typedef struct ValueStack {
    Vector vec;
} ValueStack;

typedef int Value;

/**
 * @brief Initialize a stack
 * 
 * @param new ValueStack object
 * @return int 
 */
int Stack_init(ValueStack* self);

/**
 * @brief Push a value into the stack
 * 
 * @param stack ValueStack object
 * @param value Token to insert
 * @return int 
 */
int Stack_push_value(ValueStack* self, Value value);

/**
 * @brief Return the stack's head value, without removing it
 * 
 * @param stack ValueStack object
 * @return Token 
 */
Value Stack_get_head_value(const ValueStack* self);

/**
 * @brief Pop out the stack's number
 * 
 * @param stack ValueStack object
 * @return Token 
 */
Value Stack_pop_head_value(ValueStack* self);

/**
 * @brief Swaps the top's values of the stack
 * 
 * @param stack Adresss of ValueStack object
 * @return int 
 */
int Stack_swap_head_value(ValueStack* self);

/**
 * @brief Clear stack
 * 
 * @param stack Adresss of ValueStack object
 */
void Stack_clear(ValueStack* self);

/**
 * @brief Frees stack
 * 
 * @param stack Adresss of ValueStack object
 * @return int 
 */
int Stack_free(ValueStack* self);

/**
 * @brief Print stack_content
 * 
 * @param stack ValueStack object
 */
void Stack_print(const ValueStack* stack);

/**
 * @brief Get stack's length
 * 
 * @param self 
 * @return size_t 
 */
size_t Stack_get_length(const ValueStack* self);

#endif
