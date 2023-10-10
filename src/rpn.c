#include "parser.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    TokenStack stack;
    Stack_init(&stack);
    
    char* str = strdup("2 3 + 6 4 - * 7 +");
    Parser_tokenize(&stack, str);

    printf("\n%d\n", Stack_get_head_token(&stack).token.number);

    Stack_clear(&stack);
    free(str);

    return 0;
}
