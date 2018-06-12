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
 * @file insert.c
 * @brief Insertion des données cachées dans une copie de l'hôte.
 * @details Module qui contient la fonction d'insertion et la fonction
 * d'écriture de la signature.
 */

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

int write_signature(info_s * infos)
{
    assert(infos->host.host && infos->hidden && infos->res && infos->hidden_name
           && infos->mode != STEGX_MODE_EXTRACT);

    /* Ecriture de l'algorithme utilisé et de la méthode de protection utilisée. */
    if (fwrite(&(infos->method), sizeof(uint8_t), 1, infos->res) != 1)
        return perror("Sig: Can't write method"), 1;
    if (fwrite(&(infos->algo), sizeof(uint8_t), 1, infos->res) != 1)
        return perror("Sig: Can't write algo"), 1;

    /* Ecriture de la taille du fichier à cacher. */
    if (fwrite(&(infos->hidden_length), sizeof(uint32_t), 1, infos->res) != 1)
        return perror("Sig: Can't write length hidden file"), 1;

    /* Ecriture de la taille du nom du fichier à cacher. */
    uint16_t length_hidden_name = strlen(infos->hidden_name);
    if (length_hidden_name > LENGTH_HIDDEN_NAME_MAX)
        length_hidden_name = LENGTH_HIDDEN_NAME_MAX;
    if (fwrite(&length_hidden_name, sizeof(uint8_t), 1, infos->res) != 1)
        return perror("Sig: Can't write length hidden file"), 1;

    /* Copie du nom du fichier a cacher car on fait un XOR après. */
    char cpy_hidden_name[LENGTH_HIDDEN_NAME_MAX + 1] = { 0 };
    strncpy(cpy_hidden_name, infos->hidden_name, length_hidden_name + 1);

    /* Ecriture du XOR du nom du fichier a cacher avec le mot de passe
     * (length_hidden_name octets). */
    for (int i = 0, j = 0; cpy_hidden_name[i]; i++) {
        cpy_hidden_name[i] = cpy_hidden_name[i] ^ infos->passwd[j];
        j = infos->passwd[j + 1] ? j + 1 : 0;   /* Boucle sur le mot de passe. */
    }
    if (fwrite(cpy_hidden_name, sizeof(char), length_hidden_name, infos->res) != length_hidden_name)
        return perror("Sig: Can't write hidden file name"), 1;

    /* Ecriture du mot de passe s'il s'agit d'un mot de passe par défaut 
       choisi aléatoirement par l'application (64 octets). */
    if (infos->method == STEGX_WITHOUT_PASSWD) {
        if (fwrite(infos->passwd, sizeof(char), LENGTH_DEFAULT_PASSWD, infos->res) !=
            LENGTH_DEFAULT_PASSWD)
            return perror("Sig: Can't write default password"), 1;
    }
    return 0;
}

int stegx_insert(info_s * infos)
{
    /* Vérification. */
    if (infos->mode != STEGX_MODE_INSERT)
        return stegx_errno = ERR_INSERT, 1;
    /* Les fonctions de ce tableau doivent être déclarés dans l'ordre de
     * l'énumération. */
    assert(infos->algo >= STEGX_ALGO_LSB && infos->algo < STEGX_NB_ALGO);
    static int (*insert_algo[STEGX_NB_ALGO]) (info_s *) = {
    insert_lsb, insert_eof, insert_metadata, insert_eoc, insert_junk_chunk};
    /* Insertion en appellant la fonction selon le format. */
    return (*insert_algo[infos->algo]) (infos) ? (stegx_errno = ERR_INSERT, 1) : 0;
}
