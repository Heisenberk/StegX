/**
 * @file endian.h
 * @brief Module qui fait des conversions entre endianness.
 */

#ifndef ENDIAN_H
#define ENDIAN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/** 
 * @brief Convertit un nombre en little endian vers le big endian. 
 * @param nb nombre a convertir.
 * @return renvoie un nombre compris entre 0x00 et 0xFFFFFFFF.
 * @author Clément Caumes
 */
uint32_t stegx_htobe32(uint32_t nb);

/** 
 * @brief Convertit un nombre en big endian dans l'endian de la machine. 
 * @param nb nombre a convertir.
 * @return renvoie un nombre compris entre 0x00 et 0xFFFFFFFF.
 * @author Clément Caumes
 */
uint32_t stegx_be32toh(uint32_t nb);

#endif
