#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stegx_common.h"
#include "common.h"
#include "stegx_errors.h"

/**
 * @brief Retourne le type du fichier. 
 * @param *file fichier à tester.
 * @return type_e représentant les différents types pris en charge par 
 * l'application. 
 */
type_e check_file_format(FILE * file)
{
    assert(file);
    // teste pour chaque format le type du fichier en entrée
    type_e test_bmp = stegx_test_file_bmp(file);
    if (test_bmp != UNKNOWN)
        return test_bmp;

    type_e test_png = stegx_test_file_png(file);
    if (test_png != UNKNOWN)
        return test_png;

    type_e test_wav = stegx_test_file_wav(file);
    if (test_wav != UNKNOWN)
        return test_wav;

    type_e test_mp3 = stegx_test_file_mp3(file);
    if (test_mp3 != UNKNOWN)
        return test_mp3;

    type_e test_avi = stegx_test_file_avi(file);
    if (test_avi != UNKNOWN)
        return test_avi;

    type_e test_flv = stegx_test_file_flv(file);
    if (test_flv != UNKNOWN)
        return test_flv;
    return UNKNOWN;
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
	
    if (infos->host.host == NULL) {
        stegx_errno = ERR_CHECK_COMPAT;
        return 1;
    }
    // remplit le champ host.host de infos
    type_e host_type = check_file_format(infos->host.host);
    infos->host.type = host_type;
    return 0;
}
