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
 * @file wav.c
 * @brief Fichier WAVE.
 * @details Contient les informations (fonctions, types, structures) relatives
 * aux fichiers au format WAVE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "riff.h"

/** Signature d'un fichier WAVE. */
#define SIG_WAVE 0x45564157
/** Signautre d'un flux PCM. */
#define SIG_PCM 0x0001

/** Adresse (offset) de la signature du WAVE (octet). */
#define ADDRESS_WAV_WAVE 8
/** Adresse (offset) de la signature du PCM (octet). */
#define ADDRESS_WAV_PCM 20

type_e stegx_test_file_wav(FILE * file)
{
    assert(file);
    uint32_t sig_32;
    /* Lecture de la signature RIFF. */
    if (fseek(file, 0, SEEK_SET) == -1)
        return perror("Can't move to RIFF signature"), -1;
    if (fread(&sig_32, sizeof(uint32_t), 1, file) != 1)
        return perror("Can't read RIFF signature"), -1;
    if (sig_32 != SIG_RIFF)
        return UNKNOWN;

    /* Lecture de la singnature WAVE. */
    if (fseek(file, ADDRESS_WAV_WAVE, SEEK_SET) == -1)
        return perror("Can't move to WAVE signature"), -1;
    if (fread(&sig_32, sizeof(uint32_t), 1, file) != 1)
        return perror("Can't read WAVE signature"), -1;
    if (sig_32 != SIG_WAVE)
        return UNKNOWN;

    uint16_t sig_16;
    /* Lecture de la signature du PCM. */
    if (fseek(file, ADDRESS_WAV_PCM, SEEK_SET) == -1)
        return perror("Can't move to PCM signature"), -1;
    if (fread(&sig_16, sizeof(uint16_t), 1, file) != 1)
        return perror("Can't read PCM signature"), -1;

    if (sig_16 == SIG_PCM)
        return WAV_PCM;
    else
        return WAV_NO_PCM;
}
