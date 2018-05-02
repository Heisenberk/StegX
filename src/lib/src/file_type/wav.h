#ifndef WAV_H
#define WAV_H

#include <stdio.h>
#include <stdint.h>

#include "common.h"

struct wav {
    uint32_t header_size; /*!< Offset du début de data (octet). */
    uint32_t data_size;   /*!< Taille des données (octet). */
    uint32_t chunk_size;  /*!< Taille de chaque sample (bit). */
};
typedef struct wav wav_s;

type_e stegx_test_file_wav(FILE * file);

#endif
