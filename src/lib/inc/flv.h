#ifndef FLV_H
#define FLV_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libsteg.h"

struct flv{
	uint32_t nb_video_tag;
	uint32_t nb_metadata_tag;
	uint32_t file_size;
};
typedef struct flv flv_s;

type_e stegx_test_file_flv(FILE* file);


#endif
