#include "parser.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

char* PARSE_ERROR_MSG[] = {
    "",
    "Token non reconnu",
    "Opérateur ou fonction attendu",
    "Manque de nombres pour réaliser l'opération",
};

ParserError Parser_evaluate(TokenStack* stack) {
    Token t1 = Stack_pop_head_token(stack);

    if (t1.type == OPERATOR) {
        int res = 0;

        if (Vector_get_length(&stack->vec) < 2) {
            return PARSE_ERR_MISSING_NUMBER;
        }

        Token t2 = Stack_pop_head_token(stack);

        if (t1.token.op.type == UNARY_OPERATOR) {
            res = t1.token.op.func.unary(t2.token.number);
        }

        else if (t1.token.op.type == BINARY_OPERATOR) {
            assert(Vector_get_length(&stack->vec) >= 1);
            Token t3 = Stack_pop_head_token(stack);

            res = t1.token.op.func.binary(
                t3.token.number,
                t2.token.number
            );
        }

        else {
            assert(false && "Can't be here");
        }

        Stack_push_token(
            stack,
            (Token) {
                .type = NUMBER,
                .token.number = res,
            }
        );
    }

    else if (t1.type == STRING) {
        return PARSE_ERR_UNRECOGNIZED_TOKEN;
    }

    else if (t1.type == NUMBER) {
        return PARSE_ERR_NO_OPERATOR;
    }

    return PARSE_ERR_NONE;
}

ParserError Parser_tokenize(TokenStack* dest, char* user) {
    char* token_str;
    char* strtok_save_pointer;
    ParserError err = PARSE_ERR_NONE;

    FOREACH_TOKEN_SAFE(token_str, user, &strtok_save_pointer) {

        Token token;
        Token_parse(token_str, &token);
        Stack_push_token(dest, token);
        Stack_print(dest);

        if (token.type == OPERATOR || token.type == STRING) {
            if ((err = Parser_evaluate(dest)) < 0) {
                return err;
            }
        }

    }

    return PARSE_ERR_NONE;
}
