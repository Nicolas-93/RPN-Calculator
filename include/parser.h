#ifndef PARSER_H
#define PARSER_H

#include "stack.h"

typedef enum ParserError {
    PARSE_ERR_NONE = 0,
    PARSE_ERR_UNRECOGNIZED_TOKEN    = -1,
    PARSE_ERR_NO_OPERATOR           = -2,
    PARSE_ERR_MISSING_NUMBER        = -3,
    PARSE_ERR_OPERATION             = -4,
    PARSE_ERR_TOKEN                 = -5,
} ParserError;

extern char* PARSE_ERROR_MSG[];

/**
 * @brief Evaluates stack
 * 
 * @param stack 
 * @return int 
 */
ParserError Parser_evaluate(TokenStack* stack, OperationError* operr);

/**
 * @brief Tokenize and evaluates user input
 * 
 * @param dest TokenStack object
 * @param user User's string
 * @param operr 
 */
ParserError Parser_tokenize(TokenStack* dest, char* user, OperationError* operr, TokenError* tokerr);

char* Parser_get_error(ParserError err);

#endif
