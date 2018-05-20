/** 
 * @file mp3.h
 * @brief Fichier MP3.
 * @details Contient les informations (fonctions, types, structures) relatives
 * aux fichiers au format MP3.
 */

#ifndef MP3_H
#define MP3_H

#include <stdio.h>
#include <stdint.h>

#include "common.h"

/** Signature du MP3 MPEG 1 Layer III (sans CRC, contenant ou pas de l'ID3v1 à la fin). */
#define SIG_MP3_MPEG1_LAYER3 0xFAFF
/** Signature du MP3 MPEG 2 Layer III (sans CRC, contenant ou pas de l'ID3v1 à la fin). */
#define SIG_MP3_MPEG2_LAYER3 0xF2FF
/** Signature du MP3 avec tag ID3v2. */
#define SIG_MP3_ID3V2 0x00334449

/** Masque à appliquer à un entier de 32 bits pour reconnaître la
 * signature d'un MP3 MPEG 1/2 Layer III. */
#define MASK_MP3_MPEGX_LAYER3 0x0000FEFF
/** Masque à appliquer à un entier de 32 bits pour reconnaître la
 * signature d'un MP3 avec tag ID3v2. */
#define MASK_MP3_ID3V2 0x00FFFFFF

/**
 * @brief Structure du format MP3.
 */
struct mp3 {
};

/** Type du format MP3. */
typedef struct mp3 mp3_s;

/**
 * @brief Test si le fichier est un fichier WAVE.
 * @param file Fichier à tester.
 * @req Le pointeur ne doit pas être null et le fichier ouvert en lecture.
 * @return \r{MP3}, \r{UNKNOWN} ou -1 en cas d'erreur. 
 */
type_e stegx_test_file_mp3(FILE * file);

#endif
