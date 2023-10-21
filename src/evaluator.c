#include "evaluator.h"
#include "stack.h"
#include "token.h"
#include "utils.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

Error Eval_evaluate(ValueStack* stack, Operator op) {
    Error err = ERR_NONE;
    Value res = 0;
    VECTOR_DECLARE_ARRAY(stack->vec, Value, values);

    assert(Stack_get_length(stack) > 0);

    if (Stack_get_length(stack) < op.arity) {
        return EVAL_ERR_MISSING_NUMBER;
    }

    err = op.func(values + Stack_get_length(stack) - op.arity, &res);

    if (err < 0) {
        return err;
    }

    Vector_resize(&stack->vec, Stack_get_length(stack) - op.arity);
    Stack_push_value(stack, res);

    return ERR_NONE;
}
