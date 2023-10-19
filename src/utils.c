#include "utils.h"
#include <ctype.h>
#include <stdbool.h>

bool is_integer(char* s, bool minus) {
    if (!s) return false;
    if (minus && *s == '-') ++s;

    for (; *s; ++s) {
        if (!isdigit(*s))
            return false;
    }
    return true;
}
