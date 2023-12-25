#ifndef ERRORS_H
#define ERRORS_H

#include "utils.h"

extern char* ERR_MSG[];

typedef enum Error {
    ERR_NONE                    =  0,
    ERR_ALLOC                   = -1,
    CMD_UNRECOGNIZED            = -2,
    EVAL_ERR_MISSING_NUMBER     = -3,
    TOKEN_ERR_TOO_BIG_NUMBER    = -4,
    ERR_PLUGIN_LOAD             = -5,
    OP_ERROR                    = -6,
} Error;

char* get_error(Error err);

#define PRINT_ERR(err) do { printf(C_RED"%s"C_END "\n", err); } while(0)

#endif
