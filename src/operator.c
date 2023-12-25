#include "plugins.h"
#include "operator.h"

bool Operator_is_op(Operator** op, char c) {
    const Vector* ops = Plugins_get_operators();

    for (int i = 0; i < Vector_get_length(ops); ++i) {
        Operator* plugin_op = Vector_get(ops, i);

        if (c == plugin_op->symbol()) {
            *op = plugin_op;
            return true;
        }
    }
    return false;
}
