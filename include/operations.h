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

typedef int (*UnaryFunction)(int);
typedef int (*BinaryFunction)(int, int);

typedef struct Operator {
    OperatorType type;
    OperatorName name;
    char* symbol;
    union {
        // UnaryFunction unary;
        // BinaryFunction binary;
        int (*unary)(int a);
        int (*binary)(int a, int b);
    } func;
    
} Operator;


int OP_add(int a, int b);

int OP_div(int a, int b);

int OP_mul(int a, int b);

int OP_sub(int a, int b);

int OP_mod(int a, int b);

int OP_exp(int a, int b);

int OP_factorial(int a);

bool is_operator(char* s, Operator* op);

Operator OPERATORS[] = {
    {UNARY_OPERATOR, FACTORIAL, "!", OP_factorial},
    {BINARY_OPERATOR, EXPONENT, "^", OP_exp},
    {BINARY_OPERATOR, ADD, "+", OP_add},
    {BINARY_OPERATOR, SUB, "-", OP_sub},
    {BINARY_OPERATOR, DIV, "/", OP_div},
    {BINARY_OPERATOR, MOD, "%", OP_mod},
};

#endif
