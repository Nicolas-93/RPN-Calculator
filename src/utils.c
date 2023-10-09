#include "utils.h"
#include "ctype.h"
#include "stdbool.h"

bool is_integer(char* s) {
    for (; *s; ++s) {
        if (!isdigit(*s))
            return false;
    }
    return true;
}

