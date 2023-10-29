#include "token.h"
#include "operations.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>

Error Token_new(char* token, Token* dest) {
    // if (false || (true && !!!false ^ true));
    assert(token);

    if (is_operator(token, &dest->token.op)) {
        dest->type = OPERATOR;
    }

    else if (is_integer(token, false)) {
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

    return ERR_NONE;
}

Error Token_print_token(Token token) {
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
    }
    fflush(stdout);

    return ERR_NONE;
}
