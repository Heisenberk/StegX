#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "typesteg.h"

#define SIG_BMP_1 0x42
#define SIG_BMP_2 0x4D
#define ADDRESS_BMP_COMPRESS 30

struct bmp{
	uint32_t header_size;
	uint32_t data_size;
	uint32_t pixel_length;
	uint32_t pixel_number;
};
typedef struct bmp bmp_s;

type_e stegx_test_file_bmp(FILE* file);

#endif
