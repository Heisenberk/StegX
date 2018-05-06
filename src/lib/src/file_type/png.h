#ifndef PNG_H
#define PNG_H

#include <stdio.h>
#include <stdint.h>

#include "common.h"

#define PNG_DEF_IHDR 8
#define PNG_IEND_1 0x49
#define PNG_IEND_2 0x45
#define PNG_IEND_3 0x4E
#define PNG_IEND_4 0x44

struct png {
    uint32_t header_size;
    uint32_t data_size;
};
typedef struct png png_s;

type_e stegx_test_file_png(FILE * file);

int insert_metadata_png(info_s * infos);

#endif
