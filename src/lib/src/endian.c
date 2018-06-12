/*
 * This file is part of the StegX project.
 * Copyright (C) 2018  StegX Team
 * 
 * StegX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
