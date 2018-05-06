#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stegx_common.h"
#include "stegx_errors.h"
#include "common.h"

/**
 * @brief Retourne le type du fichier. 
 * @param *file fichier à tester.
 * @return type_e représentant les différents types pris en charge par 
 * l'application. 
 */
type_e check_file_format(FILE * file)
{
    assert(file);
    type_e res = UNKNOWN;
    if (res = stegx_test_file_bmp(file)) {
    } else if (res = stegx_test_file_png(file)) {
    } else if (res = stegx_test_file_wav(file)) {
    } else if (res = stegx_test_file_mp3(file)) {
    } else if (res = stegx_test_file_avi(file)) {
    } else if (res = stegx_test_file_flv(file)) {
    }
    return res;
}

/**
 * @brief Fonction principale du module Vérification de la compatibilité 
 * des fichiers.
 * @details Remplit la structure info_s avec son champ host.type correspondant
 * au type du fichier hôte. 
 * @param *infos Structure qui contient les informations pour réaliser 
 * correctement la dissimulation/extraction.
 * @return 0 si la vérification s'est bien déroulée, sinon 1. 
 */
int stegx_check_compatibility(info_s * infos)
{
    if (!(infos->host.host))
        return stegx_errno = ERR_CHECK_COMPAT, 1;
    infos->host.type = check_file_format(infos->host.host);
    return 0;
}
