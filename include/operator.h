#ifndef OPERATOR_H
#define OPERATOR_H

#include "utils.h"
#include "errors.h"
#include <stdint.h>


typedef struct Operator {
    const char      (*symbol)(void);
    const int       (*arity)(void);
    int             (*check)(const int args[]);
    const char*     (*get_error)(int err);
    int             (*eval)(const int args[]);
} Operator;

bool Operator_is_op(Operator** op, char c);

#endif
