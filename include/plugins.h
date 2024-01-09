#ifndef PLUGINS_H
#define PLUGINS_H

#include "errors.h"
#include "vector.h"
#include "operator.h"

typedef struct Plugins {
    Vector operators;
} Plugins;

Error Plugins_load(char* exec);

void Plugins_get(void);

const Vector* Plugins_get_operators(void);

#endif
