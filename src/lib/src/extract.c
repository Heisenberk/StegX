/*
 * This file is part of the StegX project.
 * Copyright (C) 2018  StegX Team
 * 
 * StegX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
