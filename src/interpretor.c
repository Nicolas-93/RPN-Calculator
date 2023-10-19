#include "token.h"
#include "interpretor.h"
#include "couroutine.h"
#include "stack.h"
#include "utils.h"
#include "evaluator.h"

#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

ValueStack* STACK;
bool QUIT = false;


void print_stack_head(void)     {
    if (Stack_get_length(STACK) <= 0) {
        printf("stack empty\n");
        return;
    }
    printf("%d\n", Stack_get_head_value(STACK));
}
void print_stack(void)          { Stack_print(STACK); }
void clear_stack(void)          { Stack_clear(STACK); }
void reverse_stack_head(void)   { if (Stack_get_length(STACK) >= 2) Stack_swap_head_value(STACK); }
void quit(void)                 { QUIT = true; }

Action FUNCTS[] = {
    {"a", "all"    , print_stack},
    {"p", "print"  , print_stack_head},
    {"c", "clear"  , clear_stack},
    {"r", "reverse", reverse_stack_head},
    {"q", "quit"   , quit},
};

Error Interpretor_command(char* input) {

    for (int i = 0; i < STATIC_LEN(FUNCTS); ++i) {
        if (!strcmp(FUNCTS[i].short_name, input) || !strcmp(FUNCTS[i].name, input)) {
            FUNCTS[i].action();
            return ERR_NONE;
        }
    }

    return CMD_UNRECOGNIZED;
}

int Interpretor_read_tokens(Token* token, Error* tokerr) {
    static char* token_str;
    static char* strtok_save_pointer;
    static char* line;

    crBegin

    while (!QUIT && (line = readline(">>> "))) {
        add_history(line);
        FOREACH_TOKEN_SAFE(token_str, line, &strtok_save_pointer) {
            *tokerr = Token_new(token_str, token);
            crYield(1);
        }
        free(line);
    }

    crFinish

    return 0;
}

void Interpretor_consume_input(ValueStack* dest) {
    Error err = 0;
    Token token;
    STACK = dest;

    while (Interpretor_read_tokens(&token, &err)) {

        if (err >= 0) {
            if (token.type == STRING) {
                err = Interpretor_command(token.token.str);
            }
            else if (token.type == NUMBER) {
                Stack_push_value(dest, token.token.number);
            }
            else if (token.type == OPERATOR) {
                err = Eval_evaluate(dest, token.token.op);
            }

        }
        if (err) PRINT_ERR(get_error(err));

    }

    STACK = NULL;
}
