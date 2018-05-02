/** 
 * @file errors.c
 * @brief Module de gestion des erreurs.
 * @details Contient les fonctions de gestion des erreurs ainsi que les
 * descriptions des codes d'erreurs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "stegx_errors.h"

void err_print(enum err_code err)
{
    static const char *err_desc[] = {
        /* ERR_NONE */ "aucune erreur",
        /* ERR_HOST_NULL */ "fichier host null",
        /* ERR_HIDDEN_NULL */ "fichier a cacher null",
        /* ERR_PASSWD */ "mot de passe invalide",
        /* ERR_RES_EXTRACT */ "le resultat en extraction doit etre un dossier",
        /* ERR_READ */ "erreur de lecture",
        /* ERR_OTHER */ "erreur inconnu"
 
    };
    /* Vérifcation de la valeur de "err". */
    err = (unsigned int)err <= ERR_OTHER ? err : ERR_OTHER;
    fprintf(stderr, "Erreur %d : %s.\n", err, err_desc[err]);
}
