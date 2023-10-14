#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define STATIC_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

typedef enum Error {
    ERR_NONE,
    ERR_ALLOC,
} Error;

bool is_integer(char* s, bool minus);

#endif
