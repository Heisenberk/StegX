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

/**
 * @brief Structure du format MP3.
 * @author Pierre Ayoub et Damien Delaunay
 */
struct mp3 {
};

/** Type du format MP3. */
typedef struct mp3 mp3_s;

/**
 * @brief Test si le fichier est un fichier WAVE.
 * @param file Fichier à tester.
 * @req Le pointeur ne doit pas être null et le fichier ouvert en lecture.
 * @return \r{MP3}, \r{UNKNOWN} ou -1 en cas d'erreur. 
 * @author Clément Caumes, Pierre Ayoub et Damien Delaunay
 */
type_e stegx_test_file_mp3(FILE * file);

#endif
