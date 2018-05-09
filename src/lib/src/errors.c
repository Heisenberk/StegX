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
        /* ERR_HIDDEN_NULL */ "fichier à cacher null",
        /* ERR_PASSWD */ "mot de passe invalide",
        /* ERR_RES_EXTRACT */ "le resultat en extraction doit etre un dossier",
        /* ERR_RES_INSERT */ "le resultat est invalide pour l'insertion",
        /* ERR_READ */ "erreur de lecture",
        /* ERR_CHECK_COMPAT */
        "erreur dans le module verification de la compatibilite des fichiers",
        /* ERR_SUGG_ALGOS */ "erreur dans le sous-module proposition des algos de steganographie",
        /* ERR_CHOICE_ALGO */ "erreur l'algorithme choisi par l'utilisateur n'est proposé par StegX",
        /* ERR_INSERT */ "erreur dans le sous-module insertion",
        /* ERR_EXTRACT */ "erreur dans le sous-module extraction",
        /* ERR_DETECT_ALGOS */ "erreur dans le sous-module detection de l'algorithme de steganographie",
        /* ERR_LENGTH_HIDDEN */ "erreur taille du fichier a cacher trop importante",
        /* ERR_NEED_PASSWD */ "l'application a besoin d'un mot de passe pour extraire les données",
        /* ERR_OTHER */ "erreur inconnu"
    };

    /* Vérification de la valeur de "err". */
    err = (unsigned int)err <= ERR_OTHER ? err : ERR_OTHER;
    fprintf(stderr, "Erreur %d : %s.\n", err, err_desc[err]);
}
