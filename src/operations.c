#include "operations.h"
#include "utils.h"
#include <string.h>
#include <math.h>
#include <limits.h>
#include <errno.h>

Operator OPERATORS[] = {
    {1, FACTORIAL, "!", OP_factorial},
    {2, EXPONENT , "^", OP_exp},
    {2, ADD      , "+", OP_add},
    {2, SUB      , "-", OP_sub},
    {2, MUL      , "*", OP_mul},
    {2, DIV      , "/", OP_div},
    {2, MOD      , "%", OP_mod},
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

Error OP_add(int* args, int* res) {
    int a = args[0], b = args[1];

    #if __has_builtin(__builtin_add_overflow)
        if (__builtin_add_overflow(a, b, res)) {
            return OP_ERR_OVERFLOW;
        }
    #else
        *res = a + b;
    #endif
    return ERR_NONE;
}

Error OP_div(int* args, int* res) {
    int a = args[0], b = args[1];
    if (b == 0) {
        return OP_ERR_DIV_ZERO;
    }
    if (a == INT_MIN && b == -1) {
        return OP_ERR_OVERFLOW;
    }
    *res = a / b;
    return ERR_NONE;
}

Error OP_mul(int* args, int* res) {
    int a = args[0], b = args[1];
    #if __has_builtin(__builtin_mul_overflow)
        if (__builtin_mul_overflow(a, b, res)) {
            return OP_ERR_OVERFLOW;
        }
    #else
        *res = a * b;
    #endif
    return ERR_NONE;
}

Error OP_sub(int* args, int* res) {
    int a = args[0], b = args[1];
    #if __has_builtin(__builtin_mul_overflow)
        if (__builtin_sub_overflow(a, b, res)) {
            return OP_ERR_OVERFLOW;
        }
    #else
        *res = a - b;
    #endif
    return ERR_NONE;
}

Error OP_mod(int* args, int* res) {
    int a = args[0], b = args[1];
    if (b == 0) {
        return OP_ERR_DIV_ZERO;
    }
    if (a == INT_MIN && b == -1) {
        return OP_ERR_OVERFLOW;
    }
    *res = a % b;
    if (*res < 0)
        *res += b;
    return ERR_NONE;
}

Error OP_exp(int* args, int* res) {
    int a = args[0], b = args[1];
    long dres = powl(a, b);
    if (errno == ERANGE || dres >= INT_MAX) {
        errno = 0;
        return OP_ERR_OVERFLOW;
    }
    *res = (int) dres;
    return ERR_NONE;
}

Error OP_factorial(int* args, int* res) {
    int a = args[0];

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

    return ERR_NONE;
}
