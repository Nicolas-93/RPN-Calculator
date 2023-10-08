#ifndef OPERATIONS_H
#define OPERATIONS_H

typedef enum OperatorType {
    UNARY_OPERATOR = 1,
    BINARY_OPERATOR,
} OperatorType;


typedef enum BinaryOperator {
    UNKNOWN_OP,
    ADD,
    SUB,
    DIV,
    MOD,
} BinaryOperator;

char BINARY_OPERATOR_CHAR[] = {
    '\0',
    '+',
    '-',
    '/',
    '%',
};

typedef enum UnaryOperator {
    UNKNOWN_OP,
    FACTORIAL,
    EXPONENT,
} UnaryOperator;

char UNARY_OPERATOR_CHAR[] = {
    '\0',
    '!',
    '^',
};

typedef struct Operator {
    OperatorType type;
    union {
        UnaryOperator unary;
        BinaryOperator binary;
    };
} Operator;

typedef int (*UnaryFunction)(int);

typedef int (*BinaryFunction)(int, int);

int OP_add(int a, int b);

int OP_div(int a, int b);

int OP_mul(int a, int b);

int OP_sub(int a, int b);

int OP_mod(int a, int b);

int OP_exp(int a);

int OP_factorial(int a);

#endif
