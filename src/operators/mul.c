#include "operator_api.h"

typedef enum OPErr {
    OP_ERR_NONE     = 0,
    OP_ERR_OVERFLOW = -1,
} OPErr;

static const char* ERRORS[] = {
    [-OP_ERR_NONE]       = (void*) 0,
    [-OP_ERR_OVERFLOW]   = "Dépassement d'entiers (Overflow)",
};

int eval(const int args[2]) {
    int a = args[0], b = args[1];

    return a * b;
}

int check(const int args[2]) {
    int a = args[0], b = args[1];
    int res;

    #if __has_builtin(__builtin_mul_overflow)
        if (__builtin_mul_overflow(a, b, &res)) {
            return OP_ERR_OVERFLOW;
        }
    #endif

    return OP_ERR_OVERFLOW;
}

const char* get_error(int err) {
    return ERRORS[-err];
}

int arity(void) {
    return 2;
}

char symbol(void) {
    return '*';
}
