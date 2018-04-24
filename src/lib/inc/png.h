#ifndef PNG_H
#define PNG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "typesteg.h"

#define SIG_PNG_1 0x89
#define SIG_PNG_2 0x50
#define SIG_PNG_3 0x4E
#define SIG_PNG_4 0x47
#define SIG_PNG_5 0x0D
#define SIG_PNG_6 0x0A
#define SIG_PNG_7 0x1A
#define SIG_PNG_8 0x0A

struct png{
	uint32_t header_size;
	uint32_t data_size;
};
typedef struct png png_s;

type_e stegx_test_file_png(FILE* file);



#endif
