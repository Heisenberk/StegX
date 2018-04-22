
#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct bmp{
	uint32_t header_size;
	uint32_t data_size;
	uint32_t pixel_length;
	uint32_t pixel_number;
};
typedef struct bmp bmp_s;

#endif
