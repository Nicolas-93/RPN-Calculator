#ifndef PLUGINS_H
#define PLUGINS_H

#include "errors.h"
#include "vector.h"
#include "operator.h"

typedef struct Plugins {
    Vector operators;
} Plugins;

/**
 * @brief Load all plugins
 * 
 * @param exec argv[0]
 * @return Error 
 */
Error Plugins_load(char* exec);

/**
 * @brief Get loaded operators
 * 
 * @return const Vector* 
 */
const Vector* Plugins_get_operators(void);

#endif
