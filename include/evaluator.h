#ifndef PARSER_H
#define PARSER_H

#include "stack.h"
#include "operations.h"
#include "error.h"

/**
 * @brief Evaluates stack
 * 
 * @param stack Values stack
 * @param operator Operator to apply 
 * @return int 
 */
Error Eval_evaluate(ValueStack* stack, Operator op);

#endif
