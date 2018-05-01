#ifndef WAV_H
#define WAV_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "typesteg.h"

#define SIG_RIFF_1 0x52
#define SIG_RIFF_2 0x49
#define SIG_RIFF_3_4 0x46
#define SIG_WAVE_1 0x57
#define SIG_WAVE_2 0x41
#define SIG_WAVE_3 0x56
#define SIG_WAVE_4 0x45
#define ADDRESS_WAV_WAVE 8
#define ADDRESS_WAV_PCM 20
#define PCM_1 0x01
#define PCM_2 0x00

struct wav{
	uint32_t header_size;
	uint32_t data_size;
	uint32_t chunk_size;
};
typedef struct wav wav_s;

type_e stegx_test_file_wav(FILE* file);

#endif
