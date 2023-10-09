#include "operations.h"
#include "utils.h"
#include <string.h>

bool is_operator(char* s, Operator* op) {
    for (int i = 0; i < STATIC_LEN(OPERATORS); ++i) {
        if (strcmp(s, OPERATORS[i].symbol)) {
            *op = OPERATORS[i];
            return true;
        }
    }
    return false;
}
