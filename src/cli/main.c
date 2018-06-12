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

#include <stdio.h>
#include <stdlib.h>

#include "stegx.h"
#include "commandes/cli.h"

int main(int argc, char *argv[])
{
    // Initialisation de la structure publique correspondant aux choix de l'utilisateur
    stegx_choices_s *com = init_stegx_info();
    fill_info(com, argc, argv);

    // Initialisation de la structure privée à partir de la structure publique
    info_s *infos = stegx_init(com);
    if (infos == NULL) {
        err_print(stegx_errno);
        return EXIT_FAILURE;
    }
    // Vérification de la compatibilité des fichiers en entrée
    int compatibility = stegx_check_compatibility(infos);
    if (compatibility == 1) {
        err_print(stegx_errno);
        return EXIT_FAILURE;
    }
    // Si l'utilisateur a choisi de faire une insertion
    if (com->mode == STEGX_MODE_INSERT) {
        // Proposition des algorithmes de stéganographie
        int suggest = stegx_suggest_algo(infos);
        if (suggest == 1) {
            err_print(stegx_errno);
            return EXIT_FAILURE;
        }
        // Choix de l'algorithme en fonction de la proposition
        int choosen = stegx_choose_algo(infos, com->insert_info->algo);
        if (choosen == 1) {
            err_print(stegx_errno);
            return EXIT_FAILURE;
        }
        // Insertion
        int insert = stegx_insert(infos);
        if (insert == 1) {
            err_print(stegx_errno);
            return EXIT_FAILURE;
        }
    }
    // Si l'utilisateur a choisi de faire une extraction
    else if (com->mode == STEGX_MODE_EXTRACT) {

        // Détection de l'algorithme de stéganographie
        int detect = stegx_detect_algo(infos);
        if (detect == 1) {
            err_print(stegx_errno);
            return EXIT_FAILURE;
        }
        // Extraction
        int extract = stegx_extract(infos, com->res_path);
        if (extract == 1) {
            err_print(stegx_errno);
            return EXIT_FAILURE;
        }
    }
    stegx_clear(infos);
    dest_stegx_info(com);

    return EXIT_SUCCESS;
}
