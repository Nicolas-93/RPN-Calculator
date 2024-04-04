#include "operator_api.h"
#include <limits.h>

typedef enum OPErr {
    OP_ERR_NONE     = 0,
    OP_ERR_OVERFLOW = -1,
    OP_ERR_DIV_ZERO = -2,
} OPErr;

static const char* ERRORS[] = {
    [-OP_ERR_NONE]       = (void*) 0,
    [-OP_ERR_OVERFLOW]   = "Integer overflow",
    [-OP_ERR_DIV_ZERO]   = "Divide by 0",
};

int eval(const int args[2]) {
    int a = args[0], b = args[1];

    return a / b;
}

int check(const int args[2]) {
    int a = args[0], b = args[1];

    if (b == 0) {
        return OP_ERR_DIV_ZERO;
    }
    if (a == INT_MIN && b == -1) {
        return OP_ERR_OVERFLOW;
    }

    return OP_ERR_NONE;
}

const char* get_error(int err) {
    return ERRORS[-err];
}

int arity(void) {
    return 2;
}

char symbol(void) {
    return '/';
}
