/** 
 * @file mp3.h
 * @brief Fichier MP3.
 * @details Contient les informations (fonctions, types, structures) relatives
 * aux fichiers au format MP3.
 */

#ifndef MP3_H
#define MP3_H

#include <stdio.h>

#include "common.h"

/** Structure du format MP3. */
struct mp3 {
};

/** Type du format MP3. */
typedef struct mp3 mp3_s;

/**
 * @brief Test si le fichier est un fichier WAVE.
 * @param file Fichier à tester.
 * @req Le pointeur ne doit pas être null et le fichier ouvert en lecture.
 * @return -1 si une erreur survient, sinon \r{MP3} ou \r{UNKNOWN}. 
 */
type_e stegx_test_file_mp3(FILE * file);

#endif
