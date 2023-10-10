#include "stack.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int Stack_init(TokenStack* new) {
    *new = (TokenStack) {
        .size = 0,
    };
    STAILQ_INIT(new);

    return 0;
}

int Stack_push_token(TokenStack* stack, Token token) {
    TokenStackEntry* entry = malloc(sizeof(TokenStackEntry));

    if (!entry)
        return ERR_ALLOC;

    entry->token = token;

    STAILQ_INSERT_HEAD(stack, entry, entries);
    stack->size++;

    return ERR_NONE;
}

Token Stack_get_head_token(const TokenStack* stack) {
    return STAILQ_FIRST(stack)->token;
}

Token Stack_pop_head_token(TokenStack* stack) {
    TokenStackEntry* entry = STAILQ_FIRST(stack);
    Token token = entry->token;
    STAILQ_REMOVE_HEAD(stack, entries);
    free(entry);
    stack->size--;
    return token;
}

int Stack_swap_head_token(TokenStack* stack) {
    assert(stack->size >= 2);

    TokenStackEntry* entry1 = STAILQ_FIRST(stack);
    TokenStackEntry* entry2 = STAILQ_NEXT(STAILQ_FIRST(stack), entries);

    Token tmp = entry2->token;
    entry2->token = entry1->token;
    entry1->token = tmp;

    return ERR_NONE;
}

int Stack_clear(TokenStack* stack) {
    TokenStackEntry* entry = STAILQ_FIRST(stack);
    TokenStackEntry* next = NULL;
    
    while (entry) {
        next = STAILQ_NEXT(entry, entries);
        STAILQ_REMOVE(stack, entry, TokenStackEntry, entries);
        stack->size--;
        free(entry);
        entry = next;
    }

    return 0;
}

void Stack_print_aux(const TokenStackEntry* entry) {
    if (!entry) {
        return;
    }
    Stack_print_aux(STAILQ_NEXT(entry, entries));
    Token_print_token(entry->token);
    printf(" ");
}

void Stack_print(const TokenStack* stack) {
    Stack_print_aux(STAILQ_FIRST(stack));
    printf("\n");
}
