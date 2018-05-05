#ifndef MP3_H
#define MP3_H

#include <stdio.h>

#include "common.h"

struct mp3 {

};
typedef struct mp3 mp3_s;

type_e stegx_test_file_mp3(FILE * file);

int insert_metadata_mp3(info_s * infos);

#endif
