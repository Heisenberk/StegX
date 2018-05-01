#ifndef MP3_H
#define MP3_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "typesteg.h"

#define SIG_MP3_ID3V1 0xFFFB
#define SIG_MP3_ID3V2 0x494433

struct mp3{
	
};
typedef struct mp3 mp3_s;

type_e stegx_test_file_mp3(FILE* file);

#endif
