/**
 * @file extract.c
 * @brief Extraction des données cachées dans un fichier hôte.
 * @details Module qui contient la fonction d'extraction de données.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

#include "algo/lsb.h"
#include "algo/eof.h"
#include "algo/metadata.h"
#include "algo/eoc.h"
#include "algo/junk_chunk.h"

int stegx_extract(info_s * infos, char *res_path)
{
    /* Vérification. */
    if (infos->mode != STEGX_MODE_EXTRACT)
        return stegx_errno = ERR_EXTRACT, 1;

    if (infos->res != stdout) {
        // Concatenation du chemin du fichier a créer et le nom du fichier caché
        char *res_name = malloc((strlen(res_path) + strlen(infos->hidden_name) + 1) * sizeof(char));
        strcpy(res_name, res_path);
        strcat(res_name, infos->hidden_name);

        infos->res = fopen(res_name, "wb");
        if (infos->res == NULL) {
            stegx_errno = ERR_EXTRACT;
            return 1;
        }
        free(res_name);
    }

    /* Les fonctions de ce tableau doivent être déclarés dans l'ordre de
     * l'énumération. */
    assert(infos->algo >= STEGX_ALGO_LSB && infos->algo < STEGX_NB_ALGO);
    static int (*extract_algo[STEGX_NB_ALGO]) (info_s *) = {
    extract_lsb, extract_eof, extract_metadata, extract_eoc, extract_junk_chunk};
    /* Extraction en appellant la fonction selon le format. */
    return (*extract_algo[infos->algo]) (infos) ? (stegx_errno = ERR_EXTRACT, 1) : 0;
}
