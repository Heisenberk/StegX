#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdint.h>

#include "common.h"

#define BMP_DEF_PIC 10
#define BMP_DEF_LENGTH 2
#define BMP_DEF_PIX_LENGTH 28
#define BMP_DEF_NB_PIXEL 18

struct bmp {
    uint32_t header_size;
    uint32_t data_size;
    uint32_t pixel_length;
    uint32_t pixel_number;
};
typedef struct bmp bmp_s;

type_e stegx_test_file_bmp(FILE * file);

int insert_metadata_bmp(info_s * infos);

#endif
