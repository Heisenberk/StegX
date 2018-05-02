/**
 * @file common.h
 * @brief Définitions communes à la partie privée de la bibliothèque.
 * @details Ce fichier peut-être inclus par les différents modules de la
 * bibliothèque.
 */

#ifndef COMMON_PRIV_H
#define COMMON_PRIV_H

#include <stdio.h>
#include <stdint.h>

#include "stegx_common.h"

/*
 * Types
 * =============================================================================
 */

enum type { BMP_COMPRESSED, BMP_UNCOMPRESSED, PNG, WAV_PCM, WAV_NO_PCM,
    MP3, AVI_COMPRESSED, AVI_UNCOMPRESSED, FLV, UNKNOWN
};
typedef enum type type_e;

/*
 * Structures
 * =============================================================================
 */

#include "file_type/bmp.h"
#include "file_type/png.h"
#include "file_type/wav.h"
#include "file_type/mp3.h"
#include "file_type/avi.h"
#include "file_type/flv.h"

struct host_info {
    FILE *host;
    type_e type;
    union {
        struct bmp bmp;
        struct png png;
        struct wav wav;
        struct mp3 mp3;
        struct avi avi;
        struct flv flv;
    } file_info;
};
typedef struct host_info host_info_s;

struct info {
    mode_e mode;                // Requis : INSERT / EXTRACT
    algo_e algo;
    method_e method;
    host_info_s host;           // Requis
    FILE *res;                  // Requis
    FILE *hidden;               // Requis si mode == INSERT
    char *hidden_name;          // Requis (calculé à partir de hidden_path)
    uint32_t hidden_length;     // taille en octets du fichier a a
    char *passwd;               //optionnel    
};

#endif                          /* ifndef COMMON_PRIV_H */
