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


typedef struct Operator {
    OperatorType type;
    OperatorName name;
    char* symbol;
} Operator;

Operator OPERATORS[] = {
    {UNARY_OPERATOR, FACTORIAL, "!"},
    {UNARY_OPERATOR, EXPONENT, "^"},
    {BINARY_OPERATOR, ADD, "+"},
    {BINARY_OPERATOR, SUB, "-"},
    {BINARY_OPERATOR, DIV, "\\"},
    {BINARY_OPERATOR, MOD, "%"},
};

typedef int (*UnaryFunction)(int);
typedef int (*BinaryFunction)(int, int);

int OP_add(int a, int b);

int OP_div(int a, int b);

int OP_mul(int a, int b);

int OP_sub(int a, int b);

int OP_mod(int a, int b);

int OP_exp(int a);

int OP_factorial(int a);

bool is_operator(char* s, Operator* op);

#endif
