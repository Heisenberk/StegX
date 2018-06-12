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
 * @file png.h
 * @brief Fichier PNG.
 * @details Contient les informations (fonctions, types, structures) relatives
 * aux fichiers au format PNG.
 */

#ifndef PNG_H
#define PNG_H

#include <stdio.h>
#include <stdint.h>

#include "common.h"

/** Adresse (offset) de la definition du chunk IHDR (octet). */
#define PNG_DEF_IHDR 8
/** Signature IEND. */
#define SIG_IEND 0x444E4549
/** Signature IDAT */
#define SIG_IDAT 0x54414449
/** Signature tEXt */
#define SIG_tEXt 0x74584574
/** Signature tEXt STEGX PNG */
#define SIG_STEGX_PNG 0x53544547
/** Longueur en octets chunk IEND */
#define LENGTH_CHUNK_IEND 12
/** Longueur en octets signature IEND. */
#define LENGTH_IEND 4
/** Longueur en octets bloc CRC. */
#define LENGTH_CRC 4
/** Longueur jusqu'au premier chunk PNG. */
#define LENGTH_SIG_PNG 8

/**
 * @brief Structure du format PNG.
 * @internal Ne pas changer les deux premiers membres (ordre et type).
 * @author Clément Caumes et Yassin Doudouh
 */
struct png {
    uint32_t header_size;       /*!< Taille du Header en octets. */
    uint32_t data_size;         /*!< Taille du chunk Data en octets. */
};

/** Type du format PNG. */
typedef struct png png_s;

/**
 * @brief Test si le fichier est un fichier PNG.
 * @param file Fichier à tester.
 * @req Le pointeur ne doit pas être null et le fichier ouvert en lecture.
 * @return \r{PNG}, \r{UNKNOWN}, -1 en cas d'erreur. 
 * @author Clément Caumes et Yassin Doudouh
 */
type_e stegx_test_file_png(FILE * file);

/** 
 * @brief Va inserer les donnees cachees en utilisant l'algorithme Metadata 
 * dans le format PNG. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si les données ont bien été inserées ; sinon 1 en cas d'erreur.
 * @author Clément Caumes et Yassin Doudouh
 */
int insert_metadata_png(info_s * infos);

/** 
 * @brief Va extraire les donnees cachees en utilisant l'algorithme Metadata
 * dans le formar PNG. 
 * @param infos Structure représentant les informations concernant l'extraction.
 * @return 0 si les données ont bien été extraites ; sinon 1 en cas d'erreur.
 * @author Clément Caumes et Yassin Doudouh
 */
int extract_metadata_png(info_s * infos);

#endif
