#ifndef TOKEN_H
#define TOKEN_H
#define _GNU_SOURCE

#include "operations.h"
#include <string.h>

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

#define SEPARATORS " \n"
#define FOREACH_TOKEN_SAFE(token, line, saveptr) \
    for(token = strtok_r((line), SEPARATORS, (saveptr)); \
        token;                                           \
        token = strtok_r((NULL), SEPARATORS, (saveptr)))

/**
 * @brief Parse a string to a new Token object
 * 
 * @param token user string
 * @param dest destination to new Token
 * @return TokenError
 */
TokenError Token_parse(char* token, Token* dest);

/**
 * @brief Print token to stdout
 * 
 * @param token Token object
 * @return TokenError 
 */
TokenError Token_print_token(Token token);

#endif
