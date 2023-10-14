#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "utils.h"

typedef enum OperatorType {
    UNARY_OPERATOR = 1,
    BINARY_OPERATOR,
} OperatorType;

typedef enum BinaryOperator {
    ADD = 1,
    SUB,
    DIV,
    MOD,
    FACTORIAL,
    EXPONENT,
} OperatorName;

typedef enum OperationError {
    OP_ERR_NONE = 0,
    OP_ERR_DIV_ZERO = -1,
    OP_ERR_FACT_NEGATIVE = -2,
} OperationError;

extern char* OP_ERR_MSG[];

typedef OperationError (*UnaryFunction)(int, int*);
typedef OperationError (*BinaryFunction)(int, int, int*);

typedef struct Operator {
    OperatorType type;
    OperatorName name;
    char* symbol;
    union {
        // UnaryFunction unary;
        // BinaryFunction binary;
        OperationError (*unary)(int a, int* res);
        OperationError (*binary)(int a, int b, int* res);
    } func;
    
} Operator;

char* OP_get_error(OperationError err);

OperationError OP_add(int a, int b, int* res);

OperationError OP_div(int a, int b, int* res);

OperationError OP_mul(int a, int b, int* res);

OperationError OP_sub(int a, int b, int* res);

OperationError OP_mod(int a, int b, int* res);

OperationError OP_exp(int a, int b, int* res);

OperationError OP_factorial(int a, int* res);

bool is_operator(char* s, Operator* op);

extern Operator OPERATORS[];

#endif
