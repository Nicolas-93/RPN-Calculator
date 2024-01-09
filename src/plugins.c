#define _DEFAULT_SOURCE

#include <dirent.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include "errors.h"
#include "plugins.h"
#include "utils.h"
#include <unistd.h>

static Plugins PLUGINS = {0};

/**
 * @brief Print dlerror if any
 * 
 * @param func Called function name
 * @return Error 
 */
static Error print_dlerr(char* func) {
    char* err = dlerror();
    if (err) {
        fprintf(stderr, "%s: %s\n", func, err);
        return ERR_PLUGIN_LOAD;
    }
    return ERR_NONE;
}

/**
 * @brief Load plugin
 * 
 * @param handle dlsym handle
 * @param sym_name function to load from handle
 * @param dest Address to store function's pointer
 * @param mandatory If true, macro's value is false
 * if the function couldn't be load
 * 
 */
#define _Plugin_load_sym(handle, sym_name, dest, mandatory) \
    (*(void**) dest = dlsym(handle, sym_name), mandatory && !BOOL(*dest) )

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

/**
 * @brief Change directory to exec's directory
 * 
 * @param cmd_exec 
 */
static void change_dir(char* cmd_exec) {
    char* c = NULL;
    if ((c = strrchr(cmd_exec, '/'))) {
        *c = '\0';
    }
    else {
        return;
    }
    chdir(cmd_exec);
}

/**
 * @brief Load operators
 * 
 * @param exec argv[0]
 * @return Error 
 */
static Error _Plugin_load_operators(char* exec) {
    struct dirent** found;
    change_dir(exec);
    int found_len = scandir("./plugins/operators", &found, Plugin_dirent_filter, alphasort);

    if (found_len < 0) {
        perror("scandir");
        return ERR_PLUGIN_LOAD;
    }

    Vector_init(&PLUGINS.operators, sizeof(Operator), 10, NULL);
    char buffer[512];

    for (int i = 0; i < found_len; i++) {
        Operator op = {0};

        void* handle = NULL;
        snprintf(buffer, 512, "./plugins/operators/%s", found[i]->d_name);
        printf("Loading plugin %s\n", buffer);
        handle = dlopen(buffer, RTLD_NOW);
        
        if (print_dlerr("dlopen") == ERR_PLUGIN_LOAD) {
            continue;
        }

        if (_Plugin_load_sym(handle, "symbol",      &op.symbol,     true)   ||
            _Plugin_load_sym(handle, "arity",       &op.arity,      true)   ||
            _Plugin_load_sym(handle, "check",       &op.check,      true)   ||
            _Plugin_load_sym(handle, "get_error",   &op.get_error,  false)  ||
            _Plugin_load_sym(handle, "eval",        &op.eval,       true)) {
            fprintf(stderr, "Failed to load plugin %s\n", buffer);
            print_dlerr("dlsym");
            continue;
        }

        Vector_append(&PLUGINS.operators, &op);
    }

    free(found);

    return ERR_NONE;
}

Error Plugins_load(char* exec) {
    return _Plugin_load_operators(exec);
}
