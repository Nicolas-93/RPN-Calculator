#include "parser.h"
#include "interpretor.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

TokenStack STACK;
bool QUIT = false;

void print_stack_head(void)     {
    if (Stack_get_length(&STACK) <= 0) {
        printf("stack empty\n");
        return;
    }
    printf("%d\n", Stack_get_head_token(&STACK).token.number);
}
void print_stack(void)          { Stack_print(&STACK); }
void clear_stack(void)          { Stack_clear(&STACK); }
void reverse_stack_head(void)   { Stack_swap_head_token(&STACK); }
void quit(void)                 { QUIT = true; }

Action FUNCTS[] = {
    {"a", "all"    , print_stack},
    {"p", "print"  , print_stack_head},
    {"c", "clear"  , clear_stack},
    {"r", "reverse", reverse_stack_head},
    {"q", "quit"   , quit},
};

int command(char* input) {

    for (int i = 0; i < STATIC_LEN(FUNCTS); ++i) {
        if (!strcmp(FUNCTS[i].short_name, input) || !strcmp(FUNCTS[i].name, input)) {
            FUNCTS[i].action();
            return true;
        }
    }

    return false;
}

void interpretor(void) {
    char* line = NULL;
    Stack_init(&STACK);
    ParserError err = PARSE_ERR_NONE;
    OperationError operr = OP_ERR_NONE;

    while (!QUIT && (line = readline(">>> "))) {
        add_history(line);
        if (command(line)) {
            continue;
        }
        
        if ((err = Parser_tokenize(&STACK, line, &operr)) < 0) {
            char* msg = err == PARSE_ERR_OPERATION ? OP_get_error(operr) : Parser_get_error(err);
            printf("\x1b[31m%s\x1b[0m\n", msg);
        }
        free(line);
    }
    free(line);
}
