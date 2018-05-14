#include <endian.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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
    int extraction;
    if (infos->mode != STEGX_MODE_EXTRACT) {
        stegx_errno = ERR_EXTRACT;
        return 1;
    }
    // ATTENTION si stdout faux --> a rajouter dans stegx_init et ici

    // Concatenation du chemin du fichier a créer et le nom du fichier caché
    char *res_name = malloc((strlen(res_path) + strlen(infos->hidden_name) + 1) * sizeof(char));
    int i, j;
    for (i = 0; i < (int)strlen(res_path); i++) {
        res_name[i] = res_path[i];
    }
    i = 0;
    for (j = strlen(res_path); j < (int)(strlen(res_path) + strlen(infos->hidden_name)); j++) {
        res_name[j] = infos->hidden_name[i];
        i++;
    }
    res_name[strlen(res_path) + strlen(infos->hidden_name)] = '\0';
    infos->res = fopen(res_name, "w");
    if (infos->res == NULL) {
        stegx_errno = ERR_EXTRACT;
        return 1;
    }
    free(res_name);

    if (infos->algo == STEGX_ALGO_EOF) {
        extraction = extract_eof(infos);
    } else if (infos->algo == STEGX_ALGO_LSB) {
        extraction = extract_lsb(infos);
    } else if (infos->algo == STEGX_ALGO_METADATA) {
        extraction = extract_metadata(infos);
    } else if (infos->algo == STEGX_ALGO_EOC) {
        extraction = extract_eoc(infos);
    } else if (infos->algo == STEGX_ALGO_JUNK_CHUNK) {
        extraction = extract_junk_chunk(infos);
    } else {
        stegx_errno = ERR_EXTRACT;
        extraction = 1;
    }
    return extraction;
}
