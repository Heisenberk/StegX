#ifndef AVI_H
#define AVI_H

#include <stdio.h>

#include "common.h"

struct avi {

};
typedef struct avi avi_s;

type_e stegx_test_file_avi(FILE * file);

int insert_metadata_avi(info_s * infos);

#endif
