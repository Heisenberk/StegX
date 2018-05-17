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
 * @brief Structure du formatWAVE.
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
 * @return \r{WAV_PCM}, \r{WAV_NO_PCM} ou \r{UNKNOWN}. 
 */
type_e stegx_test_file_wav(FILE * file);

int insert_metadata_wav(info_s * infos);

int extract_metadata_wav(info_s * infos);

#endif
