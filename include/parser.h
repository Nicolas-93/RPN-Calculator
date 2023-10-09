#ifndef PARSER_H
#define PARSER_H

#include "stack.h"

typedef enum ParserError {
    PARSE_ERR_NONE,
    PARSE_ERR_UNRECOGNIZED_TOKEN,
    PARSE_ERR_NO_OPERATOR,
} ParserError;

char* PARSE_ERROR_MSG[] = {
    "",
    "Token non reconnu",
    "Opérateur ou fonction attendu",
};

/**
 * @brief Evaluates stack
 * 
 * @param stack 
 * @return int 
 */
ParserError Parser_evaluate(const TokenStack* stack);

/**
 * @brief Tokenize and evaluates user input
 * 
 * @param dest 
 * @param user 
 */
ParserError Parser_tokenize(TokenStack* dest, char* user);

#endif
