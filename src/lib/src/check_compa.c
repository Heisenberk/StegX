#include <stdio.h>
#include <stdlib.h>

#include "stegx_common.h"
#include "common.h"

type_e check_file_format(FILE * file)
{
    type_e res = UNKNOWN;
    if (!file)
        return res;
    if (res = stegx_test_file_bmp(file)) {
    } else if (res = stegx_test_file_png(file)) {
    } else if (res = stegx_test_file_wav(file)) {
    } else if (res = stegx_test_file_mp3(file)) {
    } else if (res = stegx_test_file_avi(file)) {
    } else if (res = stegx_test_file_flv(file)) {
    }
    return res;
}

int stegx_check_compatibility(info_s * infos)
{
    if (!(infos->host.host))
        return 1;
    infos->host.type = check_file_format(infos->host.host);
    return 0;
}
