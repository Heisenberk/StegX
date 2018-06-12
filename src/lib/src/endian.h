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
