#ifndef PNG_H
#define PNG_H

#include <stdio.h>
#include <stdint.h>

#include "common.h"

struct png {
    uint32_t header_size;
    uint32_t data_size;
};
typedef struct png png_s;

type_e stegx_test_file_png(FILE * file);

#endif
