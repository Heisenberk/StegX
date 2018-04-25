#ifndef MP3_H
#define MP3_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "typesteg.h"

#define SIG_MP3_ID3V1 0xFBFF
#define SIG_MP3_ID3V1_1 0xFF
#define SIG_MP3_ID3V1_2 0xFB
#define SIG_MP3_ID3V2_1 0x49
#define SIG_MP3_ID3V2_2 0x44
#define SIG_MP3_ID3V2_3 0x33

struct mp3{
	
};
typedef struct mp3 mp3_s;

type_e stegx_test_file_mp3(FILE* file);

#endif
