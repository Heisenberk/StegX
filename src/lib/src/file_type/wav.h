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
 * @file wav.h
 * @brief Fichier WAVE.
 * @details Contient les informations (fonctions, types, structures) relatives
 * aux fichiers au format WAVE.
 */

#ifndef WAV_H
#define WAV_H

#include <stdio.h>
#include <stdint.h>

#include "common.h"

/** Signature du subchunk data. */
#define WAV_DATA_SIGN 0x61746164
/** Signature du subchunk fmt. */
#define WAV_FMT_SIGN 0x20746d66
/** Offset entre le champ situé après la taille du subchunk fmt et le nombre de bit
 * par sample. */
#define WAV_FMT_BPS_OFF 14
/** Adresse du premier subchunk (octet). */
#define WAV_SUBCHK1_ADDR 12

/**
 * @brief Structure du format WAVE.
 * @internal Ne pas changer les deux premiers membres (ordre et type).
 * @author Pierre Ayoub et Damien Delaunay
 */
struct wav {
    uint32_t header_size;       /*!< Offset du début du segment data (octet). */
    uint32_t data_size;         /*!< Taille des données (octet). */
    uint32_t chunk_size;        /*!< Taille de chaque sample (bit). */
};

/** Type du format WAVE. */
typedef struct wav wav_s;

/**
 * @brief Test si le fichier est un fichier WAVE.
 * @param file Fichier à tester.
 * @req Le pointeur ne doit pas être null et le fichier ouvert en lecture.
 * @return \r{WAV_PCM}, \r{WAV_NO_PCM}, \r{UNKNOWN} ou -1 en cas d'erreur. 
 * @author Clément Caumes, Pierre Ayoub et Damien Delaunay
 */
type_e stegx_test_file_wav(FILE * file);

#endif
