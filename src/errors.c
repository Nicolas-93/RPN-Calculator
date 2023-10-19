#include "errors.h"

char* ERR_MSG[] = {
    "",

    "Erreur d'allocation",
    "Commande non implémentée",
    "Manque de nombres pour réaliser l'opération",
    "Le nombre saisi est trop grand",

    "Division par 0",
    "Factorielle négative",
    "Dépassement d'entiers (Overflow)",
};


char* get_error(Error err) {
    return ERR_MSG[-err];
}
