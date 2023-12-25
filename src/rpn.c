#define _GNU_SOURCE
#include "interpretor.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plugins.h"

int main(int argc, char const *argv[]) {
    ValueStack stack;
    Plugins_load();
    Stack_init(&stack);
    Interpretor_consume_input(&stack);
    Stack_free(&stack);

    return EXIT_SUCCESS;
}
