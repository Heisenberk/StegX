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
 * @file avi.c
 * @brief Fichier AVI.
 * @details Contient les informations (fonctions, types, structures) relatives
 * aux fichiers au format AVI.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "riff.h"

/** Signature d'un fichier AVI. */
#define SIG_AVI 0x20495641

/** Déplacement absolu à faire pour lire la signature AVI. */
#define ADDRESS_SIG_AVI 8

type_e stegx_test_file_avi(FILE * file)
{
    assert(file);
    if (fseek(file, 0, SEEK_SET) == -1)
        return perror("Can't move to RIFF signature"), -1;
    // lecture de la signature RIFF
    uint32_t sig_read;
    if (fread(&sig_read, sizeof(uint32_t), 1, file) != 1)
        return perror("Can't read RIFF signature"), -1;
    if (sig_read != SIG_RIFF) {
        return UNKNOWN;
    }
    if (fseek(file, ADDRESS_SIG_AVI, SEEK_SET) == -1)
        return perror("Can't move to AVI signature"), -1;
    // lecture de la signature AVI
    if (fread(&sig_read, sizeof(uint32_t), 1, file) != 1)
        return perror("Can't read AVI signature"), -1;
    if (sig_read != SIG_AVI) {
        return UNKNOWN;
    }
    return AVI_UNCOMPRESSED;
}

int insert_metadata_avi(info_s * infos)
{
    (void)infos;                /* Unused. */
    return 1;
}

int extract_metadata_avi(info_s * infos)
{
    (void)infos;                /* Unused. */
    return 1;
}
