#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

int insert_metadata(info_s * infos)
{
	assert(infos);
	assert(infos->mode==STEGX_MODE_INSERT);
	assert(infos->algo==STEGX_ALGO_METADATA);
	int insertion;
    if ((infos->host.type==BMP_COMPRESSED)||(infos->host.type==BMP_UNCOMPRESSED)) {
        insertion = insert_metadata_bmp(infos);
    } else if (infos->host.type==PNG) {
        insertion = insert_metadata_bmp(infos);
    } else if ((infos->host.type == WAV_NO_PCM)||(infos->host.type == WAV_PCM)) {
        insertion = insert_metadata_wav(infos);
    } else if (infos->host.type == MP3) {
        insertion = insert_metadata_mp3(infos);
    } else if ((infos->host.type == AVI_UNCOMPRESSED)||(infos->host.type == AVI_COMPRESSED)) {
        insertion = insert_metadata_avi(infos);
    } else if (infos->host.type == FLV) {
        insertion = insert_metadata_flv(infos);
    } else {
        stegx_errno = ERR_INSERT;
        insertion = 1;
    }
    return insertion;
}

int extract_metadata(info_s * infos)
{
    return 1;
}
