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

/** Hexadecimal "D". */
#define HEXA_D 0x64
/** Hexadecimal "A". */
#define HEXA_A 0x61
/** Hexadecimal "T". */
#define HEXA_T 0x74
/** Taille Signature DATA dans le format WAV. */
#define WAV_DATA_SIZE 4
/** Taille du SubChunk dans le format WAV. */
#define WAV_SUBCHUNK_LENGTH 8
/** Position du curseur pour lire le nombre de canaux dans le format WAV. */
#define WAV_NUM_CHANNELS 22
/** Position du curseur pour lire le bloc align dans le format WAV. */
#define WAV_NB_BLOC_ALIGN 32

/** Structure du format WAVE. */
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
