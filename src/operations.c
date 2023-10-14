#include "operations.h"
#include "utils.h"
#include <string.h>
#include <tgmath.h>

Operator OPERATORS[] = {
    {UNARY_OPERATOR , FACTORIAL, "!", .func.unary  = OP_factorial},
    {BINARY_OPERATOR, EXPONENT , "^", .func.binary = OP_exp},
    {BINARY_OPERATOR, ADD      , "+", .func.binary = OP_add},
    {BINARY_OPERATOR, SUB      , "-", .func.binary = OP_sub},
    {BINARY_OPERATOR, DIV      , "*", .func.binary = OP_mul},
    {BINARY_OPERATOR, DIV      , "/", .func.binary = OP_div},
    {BINARY_OPERATOR, MOD      , "%", .func.binary = OP_mod},
};

char* OP_ERR_MSG[] = {
    "",
    "Division par 0",
    "Factorielle négative",
};

bool is_operator(char* s, Operator* op) {
    for (int i = 0; i < STATIC_LEN(OPERATORS); ++i) {
        if (strcmp(s, OPERATORS[i].symbol) == 0) {
            *op = OPERATORS[i];
            return true;
        }
    }
    return false;
}

char* OP_get_error(OperationError err) {
    return OP_ERR_MSG[-err];
}

OperationError OP_add(int a, int b, int* res) {
    *res = a + b;
    return OP_ERR_NONE;
}

OperationError OP_div(int a, int b, int* res) {
    if (b == 0) {
        return OP_ERR_DIV_ZERO;
    }
    *res = a / b;
    return OP_ERR_NONE;
}

OperationError OP_mul(int a, int b, int* res) {
    *res = a * b;
    return OP_ERR_NONE;
}

OperationError OP_sub(int a, int b, int* res) {
    *res = a - b;
    return OP_ERR_NONE;
}

OperationError OP_mod(int a, int b, int* res) {
    if (b == 0) {
        return OP_ERR_DIV_ZERO;
    }
    *res = a % b;
    return OP_ERR_NONE;
}

OperationError OP_exp(int a, int b, int* res) {
    *res = pow(a, b);
    return OP_ERR_NONE;
}

OperationError OP_factorial(int a, int* res) {
    if (a < 0) {
        return OP_ERR_FACT_NEGATIVE;
    }

    *res = 1;

    for (; a; --a) {
        *res *= a;
    }

    return OP_ERR_NONE;
}
