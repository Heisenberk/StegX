#ifndef WAV_H
#define WAV_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "typesteg.h"

#define SIG_RIFF 0x52494646
#define SIG_WAVE 0x57415645
#define ADDRESS_WAV_WAVE 8
#define ADDRESS_WAV_PCM 20
#define SIG_PCM 0x0100

struct wav{
	uint32_t header_size;
	uint32_t data_size;
	uint32_t chunk_size;
};
typedef struct wav wav_s;

type_e stegx_test_file_wav(FILE* file);

#endif
