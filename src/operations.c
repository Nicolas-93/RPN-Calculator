#include "operations.h"
#include "utils.h"
#include <string.h>
#include <math.h>
#include <limits.h>
#include <errno.h>

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
    "Dépassement d'entiers (Overflow)"
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
    #if __has_builtin(__builtin_add_overflow)
        if (__builtin_add_overflow(a, b, res)) {
            return OP_ERR_OVERFLOW;
        }
    #else
        *res = a + b;
    #endif
    return OP_ERR_NONE;
}

OperationError OP_div(int a, int b, int* res) {
    if (b == 0) {
        return OP_ERR_DIV_ZERO;
    }
    if (a == INT_MIN && b == -1) {
        return OP_ERR_OVERFLOW;
    }
    *res = a / b;
    return OP_ERR_NONE;
}

OperationError OP_mul(int a, int b, int* res) {
    #if __has_builtin(__builtin_mul_overflow)
        if (__builtin_mul_overflow(a, b, res)) {
            return OP_ERR_OVERFLOW;
        }
    #else
        *res = a * b;
    #endif
    return OP_ERR_NONE;
}

OperationError OP_sub(int a, int b, int* res) {
    #if __has_builtin(__builtin_mul_overflow)
        if (__builtin_sub_overflow(a, b, res)) {
            return OP_ERR_OVERFLOW;
        }
    #else
        *res = a - b;
    #endif
    return OP_ERR_NONE;
}

OperationError OP_mod(int a, int b, int* res) {
    if (b == 0) {
        return OP_ERR_DIV_ZERO;
    }
    if (a == INT_MIN && b == -1) {
        return OP_ERR_OVERFLOW;
    }
    *res = a % b;
    return OP_ERR_NONE;
}

OperationError OP_exp(int a, int b, int* res) {
    long dres = powl(a, b);
    if (errno == ERANGE || dres >= INT_MAX) {
        errno = 0;
        return OP_ERR_OVERFLOW;
    }
    *res = (int) dres;
    return OP_ERR_NONE;
}

OperationError OP_factorial(int a, int* res) {
    if (a < 0) {
        return OP_ERR_FACT_NEGATIVE;
    }

    *res = 1;

    for (; a; --a) {
        #if __has_builtin(__builtin_mul_overflow)
            if (__builtin_mul_overflow(*res, a, res)) {
                return OP_ERR_OVERFLOW;
            }
        #else
            *res *= a;
        #endif
    }

    return OP_ERR_NONE;
}
