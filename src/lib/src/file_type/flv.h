#ifndef FLV_H
#define FLV_H

#include <stdio.h>
#include <stdint.h>

#include "common.h"

/** Structure du format FLV. */
struct flv {
    uint32_t nb_video_tag;
    uint32_t nb_metadata_tag;
    uint32_t file_size;
};

/** Type du format FLV. */
typedef struct flv flv_s;

/**
 * @brief Test si le fichier est un fichier FLV.
 * @param file Fichier à tester.
 * @req Le pointeur ne doit pas être null et le fichier ouvert en lecture.
 * @return \r{FLV} ou \r{UNKNOWN}. 
 */
type_e stegx_test_file_flv(FILE * file);

int insert_metadata_flv(info_s * infos);

int extract_metadata_avi(info_s * infos);

#endif
