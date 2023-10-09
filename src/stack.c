#include "stack.h"
#include <stdlib.h>
#include <assert.h>

int Stack_push_token(TokenStack* stack, Token token) {
    TokenStackEntry* entry = malloc(sizeof(TokenStackEntry));

    if (!entry)
        return ERR_ALLOC;

    STAILQ_INSERT_HEAD(stack, entry, entries);
}

Token Stack_get_head_token(const TokenStack* stack) {
    return STAILQ_FIRST(stack)->token;
}

Token Stack_pop_head_token(TokenStack* stack) {
    TokenStackEntry* entry = STAILQ_FIRST(stack);
    Token token = entry->token;
    free(entry);
    return token;
}

int Stack_swap_head_token(TokenStack* stack) {
    assert(stack->size >= 2);

    TokenStackEntry* entry1 = STAILQ_FIRST(stack);
    TokenStackEntry* entry2 = STAILQ_NEXT(STAILQ_FIRST(stack), entries);

    Token tmp = entry2->token;
    entry2->token = entry1->token;
    entry1->token = tmp;
}

int Stack_clear(TokenStack* stack) {
    TokenStackEntry* entry = STAILQ_FIRST(stack);
    TokenStackEntry* next = NULL;
    
    while (entry) {
        next = STAILQ_NEXT(entry, entries);
        STAILQ_REMOVE(stack, entry, TokenStackEntry, entries);
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
}

int Stack_print(const TokenStack* stack) {
    Stack_print_aux(STAILQ_FIRST(stack));
}
