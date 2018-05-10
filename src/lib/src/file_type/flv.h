#ifndef FLV_H
#define FLV_H

#include <stdio.h>
#include <stdint.h>

#include "common.h"

/** valeur d'un tag de type video  */
#define VIDEO_TAG 9

/** valeur d'un tag de type audio  */
#define AUDIO_TAG 8

/** valeur d'un tag de type metadata en entier non signé */
#define METATAG 18

/** valeur d'un tag de type script data en entier non signé  */
#define SCRIPT_DATA_TAG 24

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
