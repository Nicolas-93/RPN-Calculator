#ifndef INTERPRETOR_H
#define INTERPRETOR_H

#include "stack.h"

typedef struct Action {
    char* short_name;
    char* name;
    void (*action)(void);
} Action;

void print_stack_head(void);
void print_stack(void);
void clear_stack(void);
void reverse_stack_head(void);
void quit(void);

/**
 * @brief Read user input, and parse it
 * 
 * @param dest 
 */
void Interpretor_consume_input(ValueStack* dest);

#endif
