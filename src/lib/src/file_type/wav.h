#ifndef WAV_H
#define WAV_H

#include <stdio.h>
#include <stdint.h>

#include "common_priv.h"

struct wav{
	uint32_t header_size;
	uint32_t data_size;
	uint32_t chunk_size;
};
typedef struct wav wav_s;

type_e stegx_test_file_wav(FILE* file);

#endif
