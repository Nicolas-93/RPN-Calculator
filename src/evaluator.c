#include "evaluator.h"
#include "stack.h"
#include "token.h"
#include "utils.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

Error Eval_evaluate(ValueStack* stack, Operator op) {
    Error err;

    assert(Stack_get_length(stack) > 0);

    if (Stack_get_length(stack) < op.arity) {
        return EVAL_ERR_MISSING_NUMBER;
    }

    err = ERR_NONE;
    Value res = 0;

    Value v2 = Stack_pop_head_value(stack);

    if (op.arity == UNARY_OPERATOR) {
        err = op.func.unary(v2, &res);

        if (err < 0) {
            Stack_push_value(stack, v2);
        }
    }
    else if (op.arity == BINARY_OPERATOR) {
        Value v3 = Stack_pop_head_value(stack);

        err = op.func.binary(v3, v2, &res);

        if (err < 0) {
            Stack_push_value(stack, v3);
            Stack_push_value(stack, v2);
        }
    }

    if (err < 0) {
        return err;
    }

    Stack_push_value(stack, res);

    return ERR_NONE;
}
