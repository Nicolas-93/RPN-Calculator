#include "errors.h"

char* ERR_MSG[] = {
    [-ERR_NONE]                     = "",
    [-ERR_ALLOC]                    = "Erreur d'allocation",
    [-CMD_UNRECOGNIZED]             = "Commande non implémentée",
    [-EVAL_ERR_MISSING_NUMBER]      = "Manque de nombres pour réaliser l'opération",
    [-TOKEN_ERR_TOO_BIG_NUMBER]     = "Le nombre saisi est trop grand",
    [-ERR_PLUGIN_LOAD]              = "Erreur lors du chargement d'un plugin",
    [-OP_ERROR]                     = "Erreur inconnue de l'opérateur",
};


char* get_error(Error err) {
    return ERR_MSG[-err];
}
