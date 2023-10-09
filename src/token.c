#include "token.h"
#include "operations.h"
#include "utils.h"
#include <stdlib.h>

TokenError Token_parse(char* token, Token* dest) {
    // if (false || (true && !!!false ^ true));
    if (!token) {
        return -1;
    }

    if (is_operator(token, &dest->token.op)) {
        dest->type = OPERATOR;
    }

    else if (is_integer(token)) {
        dest->type = NUMBER;
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
    }
    printf("<WTF>");
    return TOKEN_ERR_INVALID;
}
