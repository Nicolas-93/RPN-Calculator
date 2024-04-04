#include "errors.h"

char* ERR_MSG[] = {
    [-ERR_NONE]                     = "",
    [-ERR_ALLOC]                    = "Memory error",
    [-CMD_UNRECOGNIZED]             = "Command not recognized",
    [-EVAL_ERR_MISSING_NUMBER]      = "Missing numbers to perform operation",
    [-TOKEN_ERR_TOO_BIG_NUMBER]     = "Number too big", 
    [-ERR_PLUGIN_LOAD]              = "Error while plugin loading",
    [-OP_ERROR]                     = "Unknown error from operator",
};


char* get_error(Error err) {
    return ERR_MSG[-err];
}
