#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "utils.h"
#include "errors.h"
#include <stdint.h>

typedef enum BinaryOperator {
    ADD = 1,
    SUB,
    MUL,
    DIV,
    MOD,
    FACTORIAL,
    EXPONENT,
} OperatorName;

extern char* OP_ERR_MSG[];

typedef Error (*NAryFunction)(int* args, int* res);

typedef struct Operator {
    uint32_t arity;
    OperatorName name;
    char* symbol;
    NAryFunction func;
} Operator;

Error OP_add(int* args, int* res);

Error OP_div(int* args, int* res);

Error OP_mul(int* args, int* res);

Error OP_sub(int* args, int* res);

Error OP_mod(int* args, int* res);

Error OP_exp(int* args, int* res);

Error OP_factorial(int* args, int* res);

bool is_operator(char* s, Operator* op);

extern Operator OPERATORS[];

#endif
