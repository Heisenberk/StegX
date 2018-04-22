#ifndef PNG_H
#define PNG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct png{
	uint32_t header_size;
	uint32_t data_size;
};
typedef struct png png_s;



#endif
