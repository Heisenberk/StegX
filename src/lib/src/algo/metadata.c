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
 * @file metadata.c
 * @brief Algorithme METADATA.
 * @details Contient les fonctions concernant l'algorithme METADATA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

int insert_metadata(info_s * infos)
{
    assert(infos);
    assert(infos->mode == STEGX_MODE_INSERT);
    assert(infos->algo == STEGX_ALGO_METADATA);
    int insertion;
    if ((infos->host.type == BMP_COMPRESSED) || (infos->host.type == BMP_UNCOMPRESSED)) {
        insertion = insert_metadata_bmp(infos);
    } else if (infos->host.type == PNG) {
        insertion = insert_metadata_png(infos);
    } else if ((infos->host.type == AVI_UNCOMPRESSED) || (infos->host.type == AVI_COMPRESSED)) {
        insertion = insert_metadata_avi(infos);
    } else if (infos->host.type == FLV) {
        insertion = insert_metadata_flv(infos);
    } else {
        stegx_errno = ERR_INSERT;
        insertion = 1;
    }
    return insertion;
}

int extract_metadata(info_s * infos)
{
    assert(infos);
    assert(infos->mode == STEGX_MODE_EXTRACT);
    assert(infos->algo == STEGX_ALGO_METADATA);
    int extraction;
    if ((infos->host.type == BMP_COMPRESSED) || (infos->host.type == BMP_UNCOMPRESSED)) {
        extraction = extract_metadata_bmp(infos);
    } else if (infos->host.type == PNG) {
        extraction = extract_metadata_png(infos);
    } else if ((infos->host.type == AVI_UNCOMPRESSED) || (infos->host.type == AVI_COMPRESSED)) {
        extraction = extract_metadata_avi(infos);
    } else if (infos->host.type == FLV) {
        extraction = extract_metadata_flv(infos);
    } else {
        stegx_errno = ERR_INSERT;
        extraction = 1;
    }
    return extraction;
}
