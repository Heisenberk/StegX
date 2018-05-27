/** 
 * @file mp3.h
 * @brief Fichier MP3.
 * @details Contient les informations (fonctions, types, structures) relatives
 * aux fichiers au format MP3.
 */

#ifndef MP3_H
#define MP3_H

#include <stdio.h>
#include <stdint.h>

#include "common.h"

/**
 * @brief Structure du format MP3.
 */
struct mp3 {
    long int fr_frst_adr; /*!< Adresse du header de la première frame MPEG 1/2 Layer III. */
    long int fr_nb;       /*!< Nombre de frame MPEG 1/2 Layer III. */
    long int eof;         /*!< Adresse de la fin du fichier officiel (sans signature et données cachées). */
};

/** Type du format MP3. */
typedef struct mp3 mp3_s;

int mp3_mpeg_hdr_test(uint32_t hdr);
int mp3_mpeg_fr_seek(uint32_t hdr, FILE * f);
long int mp3_mpeg_fr_find_first(FILE * f);
int mp3_id3v1_hdr_test(uint32_t hdr);
int mp3_id3v1_tag_seek(FILE * f);

/**
 * @brief Test si le fichier est un fichier MP3.
 * @param file Fichier à tester.
 * @req Le fichier doit être ouvert en lecture.
 * @return \r{MP3}, \r{UNKNOWN} ou -1 en cas d'erreur. 
 */
type_e stegx_test_file_mp3(FILE * file);

#endif
