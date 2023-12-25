#define _DEFAULT_SOURCE

#include <dirent.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include "errors.h"
#include "plugins.h"
#include "utils.h"

#define RETURN_IF_DLERROR(func) \
    do { \
        char* err = dlerror(); \
        if (err) { \
            fprintf(stderr, func ": %s\n", err); \
            return ERR_PLUGIN_LOAD; \
        } \
    } while (0)

#define _Plugin_safe_load_sym(handle, sym_name, dest) \
    ({ \
        *(void**) dest = dlsym(handle, sym_name); \
        RETURN_IF_DLERROR("dlsym"); \
        !BOOL(*dest); \
    })


static Plugins PLUGINS = {0};

const Vector* Plugins_get_operators(void) {
    return &PLUGINS.operators;
}

static int Plugin_dirent_filter(const struct dirent* entry) {
    return (
        strlen(entry->d_name) >= 3 &&
        strstr(entry->d_name + strlen(entry->d_name) - 3, ".so")
    );

    return 0;
}

static Error _Plugin_load_operators(void) {
    struct dirent** found;
    int found_len = scandir("./plugins/operators", &found, Plugin_dirent_filter, alphasort);

    if (found_len < 0) {
        perror("scandir");
        return ERR_PLUGIN_LOAD;
    }

    Vector_init(&PLUGINS.operators, sizeof(Operator), 10, NULL);
    char buffer[512];

    for (int i = 0; i < found_len; i++) {
        Operator op;

        void* handle;
        snprintf(buffer, 512, "./plugins/operators/%s", found[i]->d_name);
        printf("Loading plugin %s\n", buffer);
        handle = dlopen(buffer, RTLD_NOW);
        RETURN_IF_DLERROR("dlopen");

        if (_Plugin_safe_load_sym(handle, "symbol", &op.symbol)         ||
            _Plugin_safe_load_sym(handle, "arity", &op.arity)           ||
            _Plugin_safe_load_sym(handle, "check", &op.check)           ||
            _Plugin_safe_load_sym(handle, "get_error", &op.get_error)   ||
            _Plugin_safe_load_sym(handle, "eval", &op.eval)) {
            printf("Failed to load plugin %s\n", buffer);
            return ERR_PLUGIN_LOAD;
        }

        Vector_append(&PLUGINS.operators, &op);
    }

    free(found);

    return ERR_NONE;
}

Error Plugins_load(void) {
    return _Plugin_load_operators();
}
