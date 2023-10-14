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

char* Parser_get_error(ParserError err) {
    return PARSE_ERROR_MSG[-err];
}

ParserError Parser_evaluate(TokenStack* stack, OperationError* operr) {

    assert(Stack_get_length(stack) > 0);

    Token t1 = Stack_pop_head_token(stack);

    if (t1.type == NUMBER) {
        return PARSE_ERR_NO_OPERATOR;
    }

    else if (t1.type == STRING) {
        return PARSE_ERR_UNRECOGNIZED_TOKEN;
    }

    if (t1.type == OPERATOR) {

        Operator op = t1.token.op;

        if (Stack_get_length(stack) < op.type) {
            // Stack_clear(stack);
            return PARSE_ERR_MISSING_NUMBER;
        }

        *operr = OP_ERR_NONE;
        int res = 0;

        Token t2 = Stack_pop_head_token(stack);

        if (op.type == UNARY_OPERATOR) {
            *operr = op.func.unary(t2.token.number, &res);
        }

        else if (op.type == BINARY_OPERATOR) {
            Token t3 = Stack_pop_head_token(stack);

            *operr = op.func.binary(
                t3.token.number,
                t2.token.number,
                &res
            );
        }

        if (*operr < 0) {
            return PARSE_ERR_OPERATION;
        }

        Stack_push_token(
            stack,
            (Token) {
                .type = NUMBER,
                .token.number = res,
            }
        );
    }

    else {
        assert(false && "Can be everything but not a Token...");
    }

    return PARSE_ERR_NONE;
}

ParserError Parser_tokenize(TokenStack* dest, char* user, OperationError* operr) {
    char* token_str;
    char* strtok_save_pointer;
    ParserError err = PARSE_ERR_NONE;

    FOREACH_TOKEN_SAFE(token_str, user, &strtok_save_pointer) {

        Token token;
        Token_parse(token_str, &token);
        Stack_push_token(dest, token);
        Stack_print(dest);

        if (token.type == OPERATOR || token.type == STRING) {
            if ((err = Parser_evaluate(dest, operr)) < 0) {
                return err;
            }
        }

    }

    return PARSE_ERR_NONE;
}
