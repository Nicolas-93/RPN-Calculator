#include "stack.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int Stack_init(TokenStack* new) {
    Vector_init(&new->vec, sizeof(Token), 100, NULL);

    return 0;
}

int Stack_push_token(TokenStack* stack, Token token) {

    Vector_append(&stack->vec, &token);

    return ERR_NONE;
}

Token Stack_get_head_token(const TokenStack* stack) {
    Token t = * (Token*) Vector_get_reverse(&stack->vec, 1);
    return t;
}

Token Stack_pop_head_token(TokenStack* stack) {
    Token t = * (Token*) Vector_pop(&stack->vec);
    return t;
}

int Stack_swap_head_token(TokenStack* stack) {
    assert(Vector_get_length(&stack->vec) >= 2);

    Token* entry1 = Vector_get_reverse(&stack->vec, 1);
    Token* entry2 = Vector_get_reverse(&stack->vec, 2);

    Token tmp = *entry2;
    *entry2 = *entry1;
    *entry1 = tmp;

    return ERR_NONE;
}

int Stack_clear(TokenStack* stack) {
    Vector_free(&stack->vec);

    return ERR_NONE;
}

void Stack_print(const TokenStack* stack) {

    // Comment déclarer un pointeur comme tableau avec la syntaxe des VLAs ?
    // De sorte que la tableau soit correctement typé et ainsi facilement itérable,
    // et possède sa taille réelle ? (sizeof(array))

    // Token* tokens = (Token*) stack->vec.arr;

    VECTOR_DECLARE_ARRAY(stack->vec, Token, tokens);

    for (int i = 0; i < Vector_get_length(&stack->vec); ++i) {
        Token_print_token(tokens[i]);
        putchar(' ');
    }

    putchar('\n');
}
