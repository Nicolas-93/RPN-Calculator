#ifndef TOKEN_H
#define TOKEN_H

#include "operations.h"

typedef enum TokenError {
    TOKEN_ERR_NONE,
    TOKEN_ERR_INVALID
} TokenError;

typedef enum TokenType {
    OPERATOR,
    NUMBER,
    STRING,
} TokenType;

typedef struct Token {
    TokenType type;
    union {
        Operator op;
        int number;
        char* str;
    } token;
} Token;

/**
 * @brief Parse a string to a new Token object
 * 
 * @param token user string
 * @param dest destination to new Token
 * @return TokenError
 */
TokenError Token_parse(char* token, Token* dest);

TokenError Token_print_token(Token token);

#endif
