#include "operator_api.h"
#include <limits.h>

typedef enum OPErr {
    OP_ERR_NONE     = 0,
    OP_ERR_OVERFLOW = -1,
    OP_ERR_FACT_NEGATIVE = -2,
} OPErr;

static const char* ERRORS[] = {
    [-OP_ERR_NONE]              = (void*) 0,
    [-OP_ERR_OVERFLOW]          = "Integer overflow",
    [-OP_ERR_FACT_NEGATIVE]     = "Negative factorial",
};

static int LAST_RESULT = -1;

int eval(const int args[1]) {
    return LAST_RESULT;
}

int check(const int args[1]) {
    int a = args[0];
    int res = 1;
    LAST_RESULT = -1;

    if (a < 0) {
        return OP_ERR_FACT_NEGATIVE;
    }

    for (; a; --a) {
        #if __has_builtin(__builtin_mul_overflow)
            if (__builtin_mul_overflow(res, a, &res)) {
                return OP_ERR_OVERFLOW;
            }
        #else
            res *= a;
        #endif
    }

    LAST_RESULT = res;

    return OP_ERR_NONE;
}

const char* get_error(int err) {
    return ERRORS[-err];
}

int arity(void) {
    return 1;
}

char symbol(void) {
    return '!';
}
