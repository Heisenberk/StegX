#ifndef PNG_H
#define PNG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "typesteg.h"

#define SIG_PNG 0x89504E470D0A1A0A

struct png{
	uint32_t header_size;
	uint32_t data_size;
};
typedef struct png png_s;

type_e stegx_test_file_png(FILE* file);



#endif
