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
 */
struct png {
    uint32_t header_size;
    uint32_t data_size;
};

/** Type du format PNG. */
typedef struct png png_s;

/**
 * @brief Test si le fichier est un fichier PNG.
 * @param file Fichier à tester.
 * @req Le pointeur ne doit pas être null et le fichier ouvert en lecture.
 * @return \r{PNG} ou \r{UNKNOWN}. 
 */
type_e stegx_test_file_png(FILE * file);

int insert_metadata_png(info_s * infos);

int extract_metadata_png(info_s * infos);

#endif
