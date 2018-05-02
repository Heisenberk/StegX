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

struct wav {
    uint32_t header_size;
    uint32_t data_size;
    uint32_t chunk_size;
};
typedef struct wav wav_s;

type_e stegx_test_file_wav(FILE * file);

#endif
