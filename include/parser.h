#ifndef PARSER_H
#define PARSER_H

#include "stack.h"

typedef enum ParserError {
    PARSE_ERR_NONE = 0,
    PARSE_ERR_UNRECOGNIZED_TOKEN = -1,
    PARSE_ERR_NO_OPERATOR = -2,
    PARSE_ERR_MISSING_NUMBER = -3,
} ParserError;

extern char* PARSE_ERROR_MSG[];

/**
 * @brief Evaluates stack
 * 
 * @param stack 
 * @return int 
 */
ParserError Parser_evaluate(TokenStack* stack);

/**
 * @brief Tokenize and evaluates user input
 * 
 * @param dest 
 * @param user 
 */
ParserError Parser_tokenize(TokenStack* dest, char* user);

#endif
