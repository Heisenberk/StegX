#ifndef FLV_H
#define FLV_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "typesteg.h"

#define SIG_FLV_1 0x46
#define SIG_FLV_2 0x4C
#define SIG_FLV_3 0x56

struct flv{
	uint32_t nb_video_tag;
	uint32_t nb_metadata_tag;
	uint32_t file_size;
};
typedef struct flv flv_s;

type_e stegx_test_file_flv(FILE* file);


#endif
