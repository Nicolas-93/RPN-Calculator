#include "operator_api.h"
#include "limits.h"
#include <math.h>
#include <errno.h>

typedef enum OPErr {
    OP_ERR_NONE     = 0,
    OP_ERR_OVERFLOW = -1,
} OPErr;

static const char* ERRORS[] = {
    [-OP_ERR_NONE]       = (void*) 0,
    [-OP_ERR_OVERFLOW]   = "Dépassement d'entiers (Overflow)",
};

static int LAST_RESULT = -1;

int eval(const int args[2]) {
    return LAST_RESULT;
}

int check(const int args[2]) {
    LAST_RESULT = -1;

    int a = args[0], b = args[1];
    long dres = powl(a, b);

    if (errno == ERANGE || dres >= INT_MAX) {
        errno = 0;
        return OP_ERR_OVERFLOW;
    }

    LAST_RESULT = dres;

    return OP_ERR_NONE;
}

const char* get_error(int err) {
    return ERRORS[-err];
}

int arity(void) {
    return 2;
}

char symbol(void) {
    return '^';
}
