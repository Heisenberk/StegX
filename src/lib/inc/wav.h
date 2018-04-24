#ifndef WAV_H
#define WAV_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libsteg.h"

#define SIG_WAV_RIFF 0x46464952
#define SIG_WAV_WAVE 0x45564157
#define ADDRESS_WAV_WAVE 8

struct wav{
	uint32_t header_size;
	uint32_t data_size;
	uint32_t chunk_size;
};
typedef struct wav wav_s;

type_e stegx_test_file_wav(FILE* file);

#endif
