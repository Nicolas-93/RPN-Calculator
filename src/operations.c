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

bool is_operator(char* s, Operator* op) {
    for (int i = 0; i < STATIC_LEN(OPERATORS); ++i) {
        if (strcmp(s, OPERATORS[i].symbol) == 0) {
            *op = OPERATORS[i];
            return true;
        }
    }
    return false;
}

int OP_add(int a, int b) {
    return a + b;
}

int OP_div(int a, int b) {
    return a / b;
}

int OP_mul(int a, int b) {
    return a * b;
}

int OP_sub(int a, int b) {
    return a - b;
}

int OP_mod(int a, int b) {
    return a % b;
}

int OP_exp(int a, int b) {
    return pow(a, b);
}

int OP_factorial(int a) {
    int res = 1;
    for (; a; --a) {
        res *= a;
    }
    return res;
}
