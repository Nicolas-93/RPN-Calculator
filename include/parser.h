#ifndef PARSER_H
#define PARSER_H

#include "stack.h"

typedef enum ParserError {
    PARSE_ERR_NONE,
    PARSE_ERR_UNRECOGNIZED_TOKEN,
};

char* PARSE_ERROR_MSG[] = {
    "None",
    "Token non reconnu",
};

/**
 * @brief Evaluates stack
 * 
 * @param stack 
 * @return int 
 */
int Parser_evaluate(TokenStack stack);

#endif
