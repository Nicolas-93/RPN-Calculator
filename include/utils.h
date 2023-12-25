#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>

#define STATIC_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

#define BOOL(x) (!!x)

bool is_integer(char* s, bool minus);

#define C_RED "\x1b[31m"
#define C_END "\x1b[0m"

#endif
