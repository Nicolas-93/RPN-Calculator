#include "token.h"
#include "operations.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>

char* TOKEN_ERR_MSG[] = {
    "",
    "Token invalide",
    "Le nombre saisi est trop grand",
};

char* Token_get_error(TokenError err) {
    return TOKEN_ERR_MSG[-err];
}

TokenError Token_parse(char* token, Token* dest) {
    // if (false || (true && !!!false ^ true));
    assert(token);

    if (is_operator(token, &dest->token.op)) {
        dest->type = OPERATOR;
    }

    else if (is_integer(token, true)) {
        dest->type = NUMBER;
        long long int n = strtoll(token, NULL, 10);
        if (errno == ERANGE || n > INT_MAX || n < INT_MIN) {
            return TOKEN_ERR_TOO_BIG_NUMBER;
        }

        dest->token.number = atoi(token);
    }

    else {
        dest->type = STRING;
        dest->token.str = token;
    }

    return TOKEN_ERR_NONE;
}

TokenError Token_print_token(Token token) {
    switch (token.type) {
    case NUMBER:
        printf("%d", token.token.number);
        break;
    
    case STRING:
        printf("%s", token.token.str);
        break;
    
    case OPERATOR:
        printf("%s", token.token.op.symbol);
        break;
    default:
        printf("<WTF>");
        fflush(stdout);
        return TOKEN_ERR_INVALID;
    }
    fflush(stdout);

    return TOKEN_ERR_NONE;
}
