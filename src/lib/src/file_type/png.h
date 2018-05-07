#ifndef PNG_H
#define PNG_H

#include <stdio.h>
#include <stdint.h>

#include "common.h"

/** Adresse (offset) de la definition du chunk IHDR (octet). */
#define PNG_DEF_IHDR 8
/** Hexadecimal "i". */
#define HEXA_i 0x49
/** Hexadecimal "e". */
#define HEXA_e 0x45
/** Hexadecimal "n". */
#define HEXA_n 0x4E
/** Hexadecimal "d". */
#define HEXA_d 0x44

/** Structure du format FLV. */
struct png {
    uint32_t header_size;
    uint32_t data_size;
};

/** Type du format PNG. */
typedef struct png png_s;

/**
 * @brief Test si le fichier est un fichier PNG.
 * @param file Fichier à tester.
 * @req Le pointeur ne doit pas être null et le fichier ouvert en lecture.
 * @return \r{PNG} ou \r{UNKNOWN}. 
 */
type_e stegx_test_file_png(FILE * file);

#endif
