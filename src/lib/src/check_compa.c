/**
 * @file check_compa.c
 * @brief Module de vérification de la compatibilité.
 * @details Vérification de la compatibilité des fichiers en entrée, détection
 * du type du fichier hôte.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stegx_common.h"
#include "stegx_errors.h"
#include "common.h"

/** Nombre de fonctions de test d'un type de fichier. */
#define STEGX_TEST_FILE_NB 6

/**
 * @brief Retourne le type du fichier. 
 * @param *file fichier à tester.
 * @return type_e représentant les différents types pris en charge par 
 * l'application. 
 */
type_e check_file_format(FILE * file)
{
    assert(file);
    type_e(*test_file[STEGX_TEST_FILE_NB]) (FILE *) = {
    stegx_test_file_bmp, stegx_test_file_png, stegx_test_file_wav,
            stegx_test_file_mp3, stegx_test_file_avi, stegx_test_file_flv};
    type_e res = UNKNOWN;
    for (int i = 0; i < STEGX_TEST_FILE_NB && res == UNKNOWN; i++)
        res = (*test_file[i]) (file);
    return res;
}

int stegx_check_compatibility(info_s * infos)
{
    if (!(infos->host.host) || !(infos->host.type = check_file_format(infos->host.host)))
        return stegx_errno = ERR_CHECK_COMPAT, 1;
    return 0;
}
