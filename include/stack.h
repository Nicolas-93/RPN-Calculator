#ifndef STACK_H
#define STACK_H

#include <sys/queue.h>
#include "token.h"

typedef struct TokenStackEntry {
    Token token;
    STAILQ_ENTRY(TokenStackEntry) entries;
};

typedef STAILQ_HEAD(TokenStack, TokenStackEntry) TokenStack;

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
Token Stack_get_head_token(TokenStack stack);

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
int Stack_print(TokenStack stack);

#endif
