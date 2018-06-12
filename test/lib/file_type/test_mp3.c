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

#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include "cmocka.h"

#include <errno.h>
#include <unistd.h>
#include "stegx.h"
#include "common.h"
#include "endian.h"
#include "file_type/mp3.h"

#define TEST_DIR "../../../env/test/"

/* Test la détection d'une frame de MP3. */
void test_mp3_mpeg_hdr_test(void **state)
{
    (void)state;                /* Unused */
    assert_true(mp3_mpeg_hdr_test(0xFFFBA060));
    assert_false(mp3_mpeg_hdr_test(0xFBFBA060));
    assert_false(mp3_mpeg_hdr_test(0xFFEBA060));
}

/* Test le saut d'une frame MPEG 1/2 Layer III. */
void test_mp3_mpeg_fr_seek(void **state)
{
    /* Initialisation. */
    (void)state;                /* Unused */
    uint32_t hdr;
    FILE * f = fopen(TEST_DIR"mp3/MP3_ID3v2.3_Stereo_44,1kHz_256kbps_1.mp3", "rb");
    assert_non_null(f);

    /* Déplacement sur le header, lecture du header puis saut du tag. */
    assert_false(fseek(f, 0x395, SEEK_SET));
    assert_int_equal(fread(&hdr, sizeof(hdr), 1, f), 1);
    assert_false(mp3_mpeg_fr_seek(stegx_be32toh(hdr), f));

    /* Comparaison de la position réelle avec la position attendue. */ 
    assert_int_equal(ftell(f), 0x6D9);
    /* Nettoyage. */
    fclose(f);
}

/* Test d'écriture d'une frame de MP3. */
void test_mp3_mpeg_fr_write(void **state)
{
    /* Initialisation. */
    (void)state;                /* Unused */
    uint32_t hdr, size;
    uint8_t bsrc, bdst;
    FILE * fsrc = fopen(TEST_DIR"mp3/MP3_ID3v2.3_Stereo_44,1kHz_256kbps_1.mp3", "rb");
    FILE * fdst = fopen("test_mp3_mpeg_fr_write", "w+b");
    assert_non_null(fsrc), assert_non_null(fdst);

    /* Déplacement sur le header. */
    assert_false(fseek(fsrc, 0x395, SEEK_SET));
    /* Lecture puis écriture du header. */
    assert_int_equal(fread(&hdr, sizeof(hdr), 1, fsrc), 1);
    assert_int_equal(fwrite(&hdr, sizeof(hdr), 1, fdst), 1);
    /* Écriture du tag. */
    assert_false(mp3_mpeg_fr_write(stegx_be32toh(hdr), fsrc, fdst));

    /* Comparaison du tag original avec tout le fichier resultant, qui ne
     * devrait que contenir le tag. */
    assert_false(fseek(fsrc, 0x395, SEEK_SET));
    assert_false(fseek(fdst, 0, SEEK_SET));
    for (size = 0; fread(&bdst, sizeof(bdst), 1, fdst); size++)
        fread(&bsrc, sizeof(bsrc), 1, fsrc), assert_int_equal(bsrc, bdst);
    assert_int_equal(size, 836);

    /* Nettoyage. */
    assert_false(remove("test_mp3_mpeg_fr_write"));
    fclose(fsrc), fclose(fdst);
}

/* Test de la détection de la première frame MPEG 1/2 Layer III. */
void test_mp3_mpeg_fr_find_first(void **state)
{
    /* Initialisation. */
    (void)state;                /* Unused */
    FILE * f = NULL;

    /* Test sur tout types différents de MP3. */
    f = fopen(TEST_DIR"mp3/MP3_ID3v1_Stereo_44,1kHz_160kbps.mp3", "rb");
    assert_non_null(f), assert_int_equal(mp3_mpeg_fr_find_first(f), 0x0);
    assert_false(fclose(f));
    f = fopen(TEST_DIR"mp3/MP3_ID3v2.3_Stereo_44,1kHz_256kbps_1.mp3", "rb");
    assert_non_null(f), assert_int_equal(mp3_mpeg_fr_find_first(f), 0x395);
    assert_false(fclose(f));
    f = fopen(TEST_DIR"mp3/MP3_ID3v2.3_Stereo_44,1kHz_256kbps_2.mp3", "rb");
    assert_non_null(f), assert_int_equal(mp3_mpeg_fr_find_first(f), 0x8e5);
    assert_false(fclose(f));
    f = fopen(TEST_DIR"mp3/MP3_ID3v2.4_Mono_44,1kHz_64kbps.mp3", "rb");
    assert_non_null(f), assert_int_equal(mp3_mpeg_fr_find_first(f), 0x2d);
    assert_false(fclose(f));
    f = fopen(TEST_DIR"mp3/MP3_ID3v2.4_Unsync_Stereo_44,1kHz_192kbps.mp3", "rb");
    assert_non_null(f), assert_int_equal(mp3_mpeg_fr_find_first(f), 0x8f5);
    assert_false(fclose(f));
}

/* Test la détection d'un tag ID3v1. */
void test_mp3_id3v1_hdr_test(void **state)
{
    (void)state;                /* Unused */
    assert_true(mp3_id3v1_hdr_test(0x54414734));
    assert_false(mp3_id3v1_hdr_test(0x54413447));
}

/* Test le saut d'un tag ID3v1. */
void test_mp3_id3v1_tag_seek(void **state)
{
    /* Initialisation. */
    (void)state;                /* Unused */
    uint32_t hdr;
    FILE * f = fopen(TEST_DIR"mp3/MP3_ID3v1_Stereo_44,1kHz_160kbps.mp3", "rb");
    assert_non_null(f);

    /* Déplacement sur le header, lecture du header puis saut du tag. */
    assert_false(fseek(f, 0x00039FC6, SEEK_SET));
    assert_int_equal(fread(&hdr, sizeof(hdr), 1, f), 1);
    assert_false(mp3_id3v1_tag_seek(f));

    /* Comparaison de la position réelle avec la position attendue. */ 
    assert_int_equal(ftell(f), 0x0003A046);
    /* Nettoyage. */
    fclose(f);
}

/* Test l'écriture d'un tag ID3v1. */
void test_mp3_id3v1_tag_write(void **state)
{
    /* Initialisation. */
    (void)state;                /* Unused */
    uint32_t hdr, size;
    uint8_t bsrc, bdst;
    FILE * fsrc = fopen(TEST_DIR"mp3/MP3_ID3v1_Stereo_44,1kHz_160kbps.mp3", "rb");
    FILE * fdst = fopen("test_mp3_id3v1_tag_write", "w+b");
    assert_non_null(fsrc), assert_non_null(fdst);

    /* Déplacement sur le header. */
    assert_false(fseek(fsrc, 0x00039FC6, SEEK_SET));
    /* Lecture puis écriture du header. */
    assert_int_equal(fread(&hdr, sizeof(hdr), 1, fsrc), 1);
    assert_int_equal(fwrite(&hdr, sizeof(hdr), 1, fdst), 1);
    /* Écriture du tag. */
    assert_false(mp3_id3v1_tag_write(fsrc, fdst));

    /* Comparaison du tag original avec tout le fichier resultant, qui ne
     * devrait que contenir le tag. */
    assert_false(fseek(fsrc, 0x00039FC6, SEEK_SET));
    assert_false(fseek(fdst, 0, SEEK_SET));
    for (size = 0; fread(&bdst, sizeof(bdst), 1, fdst); size++)
        fread(&bsrc, sizeof(bsrc), 1, fsrc), assert_int_equal(bsrc, bdst);
    assert_int_equal(size, 128);

    /* Nettoyage. */
    assert_false(remove("test_mp3_id3v1_tag_write"));
    fclose(fsrc), fclose(fdst);
}

/* Test la vérification du format MP3. */
void test_stegx_test_file_mp3(void **state)
{
    /* Initialisation. */
    (void)state;                /* Unused */
    FILE * f = NULL;

    /* Test tout les types de fichier MP3 et certains autres formats. */
    f = fopen(TEST_DIR"wave/WAVE_PCM(ALAW_16)_Mono_44,1kHz_1.wav", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_mp3(f), UNKNOWN);
    assert_false(fclose(f));
    f = fopen(TEST_DIR"bmp/test1.bmp", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_mp3(f), UNKNOWN);
    assert_false(fclose(f));
    f = fopen(TEST_DIR"mp3/MP3_ID3v1_Stereo_44,1kHz_160kbps.mp3", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_mp3(f), MP3);
    assert_false(fclose(f));
    f = fopen(TEST_DIR"mp3/MP3_ID3v2.3_Stereo_44,1kHz_256kbps_1.mp3", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_mp3(f), MP3);
    assert_false(fclose(f));
    f = fopen(TEST_DIR"mp3/MP3_ID3v2.4_Mono_44,1kHz_64kbps.mp3", "r");
    assert_non_null(f), assert_int_equal(stegx_test_file_mp3(f), MP3);
    assert_false(fclose(f));
}

/* Liste des tests. */
const struct CMUnitTest mp3_tests[] = {
    cmocka_unit_test(test_mp3_mpeg_hdr_test),
    cmocka_unit_test(test_mp3_mpeg_fr_seek),
    cmocka_unit_test(test_mp3_mpeg_fr_write),
    cmocka_unit_test(test_mp3_mpeg_fr_find_first),
    cmocka_unit_test(test_mp3_id3v1_hdr_test),
    cmocka_unit_test(test_mp3_id3v1_tag_seek),
    cmocka_unit_test(test_mp3_id3v1_tag_write),
    cmocka_unit_test(test_stegx_test_file_mp3)
};

int main(void)
{
    /* Exécute les tests. */
    return cmocka_run_group_tests(mp3_tests, NULL, NULL);
}
