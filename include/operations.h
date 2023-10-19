#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "utils.h"
#include "errors.h"

typedef enum OperatorArity {
    UNARY_OPERATOR = 1,
    BINARY_OPERATOR,
} OperatorArity;

typedef enum BinaryOperator {
    ADD = 1,
    SUB,
    DIV,
    MOD,
    FACTORIAL,
    EXPONENT,
} OperatorName;

extern char* OP_ERR_MSG[];

typedef Error (*UnaryFunction)(int, int*);
typedef Error (*BinaryFunction)(int, int, int*);

typedef struct Operator {
    OperatorArity arity;
    OperatorName name;
    char* symbol;
    union {
        UnaryFunction unary;
        BinaryFunction binary;
        // Error (*unary)(int a, int* res);
        // Error (*binary)(int a, int b, int* res);
    } func;
    
} Operator;

Error OP_add(int a, int b, int* res);

Error OP_div(int a, int b, int* res);

Error OP_mul(int a, int b, int* res);

Error OP_sub(int a, int b, int* res);

Error OP_mod(int a, int b, int* res);

Error OP_exp(int a, int b, int* res);

Error OP_factorial(int a, int* res);

bool is_operator(char* s, Operator* op);

extern Operator OPERATORS[];

#endif
