#ifndef PLUGINS_H
#define PLUGINS_H

int eval(const int args[]);

int check(const int args[]);

__attribute__ ((const)) const char* get_error(int err);

__attribute__ ((const)) const int arity(void);

__attribute__ ((const)) const char symbol(void);

#endif
