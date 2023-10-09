#ifndef STACK_H
#define STACK_H

#include <sys/queue.h>
#include "token.h"

typedef struct TokenStackEntry {
    Token token;
    STAILQ_ENTRY(TokenStackEntry) entries;
} TokenStackEntry;

typedef struct TokenStack {
    struct TokenStackEntry *stqh_first;
    struct TokenStackEntry **stqh_last;
    int size;
} TokenStack;

/**
 * @brief Initialize a stack
 * 
 * @param new TokenStack object
 * @return int 
 */
int Stack_init(TokenStack* new)

/**
 * @brief Push a token into the stack
 * 
 * @param stack TokenStack object
 * @param token Token to insert
 * @return int 
 */
int Stack_push_token(TokenStack* stack, Token token);

/**
 * @brief Return the stack's token, without removing it
 * 
 * @param stack TokenStack object
 * @return Token 
 */
Token Stack_get_head_token(const TokenStack* stack);

/**
 * @brief Pop out the stack's token
 * 
 * @param stack TokenStack object
 * @return Token 
 */
Token Stack_pop_head_token(TokenStack* stack);

/**
 * @brief Swaps the top's token of the stack
 * 
 * @param stack Adresss of TokenStack object
 * @return int 
 */
int Stack_swap_head_token(TokenStack* stack);

/**
 * @brief Clear stack
 * 
 * @param stack Adresss of TokenStack object
 * @return int 
 */
int Stack_clear(TokenStack* stack);

/**
 * @brief Print stack_content
 * 
 * @param stack TokenStack object
 * @return int 
 */
int Stack_print(const TokenStack* stack);

#endif
