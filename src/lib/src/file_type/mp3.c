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
 * @file mp3.c
 * @brief Fichier MP3.
 * @details Contient les informations (fonctions, types, structures) relatives
 * aux fichiers au format MP3.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "mp3.h"

/** Signature du MPEG 1 Layer III. */
#define SIG_MPEG1_LAYER3 0xFFFA0000
/** Signature du MPEG 2 Layer III. */
#define SIG_MPEG2_LAYER3 0xFFF20000
/** Signature de l'ID3v1. */
#define SIG_ID3V1 0x54414700
/** Signature de l'ID3v2. */
#define SIG_ID3V2 0x49443300

/** Masque à appliquer pour reconnaître la signature du MPEG 1/2 Layer III. */
#define MASK_MPEG_LAYER3 0xFFFE0000
/** Masque à appliquer pour reconnaître la signature de l'ID3. */
#define MASK_ID3 0xFFFFFF00

/** Taille d'un TAG ID3v1. */
#define TAG_ID3V1_SIZE 128
/** Taille d'un header de tag ID3v2. */
#define TAG_ID3V2_HEADER_SIZE 10

/**
 * @brief Test si le header est un header ID3v2.
 * @param hdr Header à tester.
 * @return 0 si le header est incorrect, sinon 1 si le header est valide.
 * @author Pierre Ayoub, Damien Delaunay
 */
static int mp3_id3v2_hdr_test(const uint32_t hdr)
{
    return (hdr & MASK_ID3) == SIG_ID3V2;
}

/**
 * @brief Retire la sécurité de synchronisation de la taille d'un tag ID3v2.
 * @param s Taille lu du tag.
 * @return Taille réelle du tag.
 * @req "s" doit être un entier "syncsafe".
 * @author Pierre Ayoub, Damien Delaunay
 */
static uint32_t mp3_id3v2_size_unsyncsafe(const uint32_t s)
{
    assert(!(0x80808080 & s) && "L'entier doit être un entier syncsafe");
    return (0x0000007F & s) | ((0x00007F00 & s) >> 1) | ((0x007F0000 & s) >> 2) | ((0x7F000000 & s) >> 3);
}

/**
 * @brief Saute le tag ID3v2 actuel.
 * @param f Fichier MP3.
 * @return Valeur de retour de fseek().
 * @req Le fichier f doit être ouvert en lecture. Lors du déplacement, il est
 * considéré que la signature du tag vient d'être lu, le curseur de lecture
 * est donc à "debut_du_fichier + sizeof(sig)".
 * @sideeffect Le curseur de lecture du fichier est modifié pour sauter le
 * tag.
 * @author Pierre Ayoub, Damien Delaunay
 */
static int mp3_id3v2_tag_seek(FILE * f)
{
    assert(f && ftell(f) == 4 && "Les 4 premiers octets du fichier (header ID3v2) doivent êtres lus");
    uint8_t flags = 0;
    uint32_t size = 0;
    /* Lecture des flags et de la taille. */
    if (fseek(f, 1, SEEK_CUR) || fread(&flags, sizeof(flags), 1, f) != 1)
        return perror("mp3_id3v2_tag_seek: Can't read flags of the header"), -1;
    if (fread(&size, sizeof(size), 1, f) != 1)
        return perror("mp3_id3v2_tag_seek: Can't read size of the header"), -1;
    assert(ftell(f) == 10);
    return fseek(f, mp3_id3v2_size_unsyncsafe(stegx_be32toh(size)) + TAG_ID3V2_HEADER_SIZE, SEEK_SET);
}

/**
 * @brief Obtient la version de la norme MPEG du header d'une frame MP3.
 * @param hdr Header MPEG.
 * @return 1 ou 2 si la version est reconnu, sinon retourne 0.
 * @req Le header doit être un header MPEG.
 * @author Pierre Ayoub, Damien Delaunay
 */
static int mp3_mpeg_hdr_get_version(const uint32_t hdr)
{
    assert(mp3_mpeg_hdr_test(hdr) && "Le header doit être un header MPEG 1/2 Layer III");
    static const int ver[4] = {0, 0, 2, 1};
    return ver[(hdr & 0x180000) >> 19];
}

/**
 * @brief Permet de savoir si une frame MP3 contient du padding.
 * @param hdr Header MPEG de la frame.
 * @return 1 si la frame contient du padding, 0 sinon.
 * @req Le header doit être un header MPEG.
 * @author Pierre Ayoub, Damien Delaunay
 */
static int mp3_mpeg_hdr_is_padding(const uint32_t hdr)
{
    assert(mp3_mpeg_hdr_test(hdr) && "Le header doit être un header MPEG 1/2 Layer III");
    return (hdr & 0x00000200) >> 9;
}

/**
 * @brief Obtient la fréquence d'échantillonage d'une frame MP3.
 * @param hdr Header MPEG de la frame.
 * @return La fréquence d'échantillonage en Hz si elle est reconnu, sinon 0.
 * @req Le header doit être un header MPEG.
 * @author Pierre Ayoub, Damien Delaunay
 */
static int mp3_mpeg_hdr_get_samprate(const uint32_t hdr)
{
    assert(mp3_mpeg_hdr_test(hdr) && "Le header doit être un header MPEG 1/2 Layer III");
    static const int samp[3][4] = {{0}, {44100, 48000, 32000, 0}, {22050, 24000, 16000, 0}};
    return samp[mp3_mpeg_hdr_get_version(hdr)][(hdr & 0x00000C00) >> 10];
}

/**
 * @brief Obtient la débit binaire d'une frame MP3.
 * @param hdr Header MPEG de la frame.
 * @return Le débit binaire en Kbps (10^3 bits par seconde) si il est reconnu,
 * sinon 0.
 * @req Le header doit être un header MPEG.
 * @author Pierre Ayoub, Damien Delaunay
 */
static int mp3_mpeg_hdr_get_bitrate(const uint32_t hdr)
{
    assert(mp3_mpeg_hdr_test(hdr) && "Le header doit être un header MPEG 1/2 Layer III");
    static const int bit[3][16] = {{0},
        {0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 0},
        {0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, 0}};
    return bit[mp3_mpeg_hdr_get_version(hdr)][(hdr & 0x0000F000) >> 12];
}

/**
 * @brief Obtient la taille d'une frame MP3.
 * @param hdr Header MPEG de la frame.
 * @return Taille d'une frame MP3 (header + données).
 * @req Le header doit être un header MPEG.
 * @author Pierre Ayoub, Damien Delaunay
 */
static int mp3_mpeg_hdr_get_size(const uint32_t hdr)
{
    assert(mp3_mpeg_hdr_test(hdr) && "Le header doit être un header MPEG 1/2 Layer III");
    return ((144000 * mp3_mpeg_hdr_get_bitrate(hdr)) / mp3_mpeg_hdr_get_samprate(hdr)) + mp3_mpeg_hdr_is_padding(hdr);
}

int mp3_mpeg_hdr_test(const uint32_t hdr)
{
    return (hdr & MASK_MPEG_LAYER3) == SIG_MPEG1_LAYER3 || (hdr & MASK_MPEG_LAYER3) == SIG_MPEG2_LAYER3;
}

int mp3_mpeg_fr_seek(const uint32_t hdr, FILE * f)
{
    assert(mp3_mpeg_hdr_test(hdr) && "Le header doit être un header MPEG 1/2 Layer III");
    assert(f);
    return fseek(f, mp3_mpeg_hdr_get_size(hdr) - sizeof(hdr), SEEK_CUR);
}

int mp3_mpeg_fr_write(uint32_t hdr, FILE * src, FILE * dst)
{
    assert(mp3_mpeg_hdr_test(hdr) && "Le header doit être un header MPEG 1/2 Layer III");
    assert(src && dst);
    uint8_t buf[BUFSIZ]; // Copie efficace avec un buffer.
    int s = mp3_mpeg_hdr_get_size(hdr) - sizeof(hdr);
    while (s && fread(buf, sizeof(*buf), s < BUFSIZ ? s : BUFSIZ, src))
        s -= fwrite(buf, sizeof(*buf), s < BUFSIZ ? s : BUFSIZ, dst);
    return ferror(src) || ferror(dst) ? -1 : 0;
}

long int mp3_mpeg_fr_find_first(FILE * f)
{
    assert(f);
    uint32_t hdr = 0;
    if (fseek(f, 0, SEEK_SET) || fread(&hdr, sizeof(hdr), 1, f) != 1)
        return perror("mp3_mpeg_fr_find_first: Can't read MP3 first signature"), -1;
    hdr = stegx_be32toh(hdr);
    /* Si on est sur de l'ID3v2, on saute le tag. */
    if (mp3_id3v2_hdr_test(hdr) && mp3_id3v2_tag_seek(f))
        return perror("mp3_mpeg_fr_find_first: Can't skip over ID3v2 tag"), -1;
    /* Si on était sur une frame MPEG 1/2 Layer III ou que l'on est dessus après avoir sauté le tag ID3v2. */
    return mp3_mpeg_hdr_test(hdr) || ((fread(&hdr, sizeof(hdr), 1, f) == 1) && mp3_mpeg_hdr_test(stegx_be32toh(hdr))) ?
        ftell(f) - (int)sizeof(hdr) : -1;
}

int mp3_id3v1_hdr_test(const uint32_t hdr)
{
    return (hdr & MASK_ID3) == SIG_ID3V1;
}

int mp3_id3v1_tag_seek(FILE * f)
{
    assert(f);
    return fseek(f, TAG_ID3V1_SIZE - sizeof(uint32_t), SEEK_CUR);
}

int mp3_id3v1_tag_write(FILE * src, FILE * dst)
{
    assert(src && dst);
    uint8_t buf[TAG_ID3V1_SIZE]; // Copie efficace avec un buffer.
    int s = TAG_ID3V1_SIZE - sizeof(uint32_t);
    fread(buf, sizeof(*buf), s, src), fwrite(buf, sizeof(*buf), s, dst);
    return ferror(src) || ferror(dst) ? -1 : 0;
}

type_e stegx_test_file_mp3(FILE * file)
{
    assert(file);
    uint32_t sig = 0;
    if (fseek(file, 0, SEEK_SET) || (fread(&sig, sizeof(sig), 1, file) != 1))
        return perror("stegx_test_file_mp3: Can't read first 4 bytes"), -1;
    sig = stegx_be32toh(sig);
    return mp3_id3v2_hdr_test(sig) || mp3_mpeg_hdr_test(sig) ? MP3 : UNKNOWN;
}
