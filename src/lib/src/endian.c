/**
 * @file endian.c
 * @brief Module qui fait des conversions entre endianness.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "endian.h"

uint32_t stegx_be32toh(uint32_t nb)
{
    // Inversion entre les octets
    return (((nb) >> 24) | (((nb) & 0x00FF0000) >> 8) | (((nb) & 0x0000FF00) << 8) | ((nb) << 24));
}

uint32_t stegx_htobe32(uint32_t nb)
{
    // Il suffit d'appeler stegx_be32toh car on veut son inverse
    return stegx_be32toh(nb);

}
