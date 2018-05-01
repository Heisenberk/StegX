#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdint.h>

#include "common_priv.h"

struct bmp{
	uint32_t header_size;
	uint32_t data_size;
	uint32_t pixel_length;
	uint32_t pixel_number;
};
typedef struct bmp bmp_s;

type_e stegx_test_file_bmp(FILE* file);

#endif
