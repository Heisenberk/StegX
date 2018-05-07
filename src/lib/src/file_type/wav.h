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

#define WAV_DATA_1 0x64
#define WAV_DATA_2 0x61
#define WAV_DATA_3 0x74
#define WAV_DATA_4 0x61
#define WAV_DATA_SIZE 4
#define WAV_SUBCHUNK_LENGTH 8
#define WAV_CHUNK_SIZE_LOCALISATION 2
#define WAV_NUM_CHANNELS 22
#define WAV_NB_BLOC_ALIGN 32

/** Structure du format WAVE. */
struct wav {
    uint32_t header_size; /*!< Offset du début du segment data (octet). */
    uint32_t data_size;   /*!< Taille des données (octet). */
    uint32_t chunk_size;  /*!< Taille de chaque sample (bit). */
};

/** Type du format WAVE. */
typedef struct wav wav_s;

/**
 * @brief Test si le fichier est un fichier WAVE.
 * @param file Fichier à tester.
 * @req Le pointeur ne doit pas être null et le fichier ouvert en lecture.
 * @return -1 si une erreur survient, sinon \r{WAV_PCM}, \r{WAV_NO_PCM} ou \r{UNKNOWN}. 
 */
type_e stegx_test_file_wav(FILE * file);

#endif
