#ifndef CHECKCOMPA_H
#define CHECKCOMPA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libsteg.h"

type_e check_file_format(FILE* file);

int stegx_check_compatibility(info_s* infos);

#endif

