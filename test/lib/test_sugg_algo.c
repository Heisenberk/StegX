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

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "stegx.h"
#include "common.h"

#define TEST_DIR "../../../env/test/"

/* Setup des tests unitaires pour les formats de fichiers */
static int test_file_info__setup(void **state)
{
    info_s *infos = malloc(sizeof(info_s));
    assert_non_null(infos);
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->res = fopen("res.bmp", "w"), assert_non_null(infos->res);
    infos->hidden_name =
        malloc((strlen("test16.txt") + 1) * sizeof(char)), assert_non_null(infos->hidden_name);
    strcpy(infos->hidden_name, "test16.txt");
    infos->hidden =
        fopen("../../../env/test/others/test16.txt", "r"), assert_non_null(infos->hidden);
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char)), assert_non_null(infos->passwd);
    strcpy(infos->passwd, "stegx");
    stegx_propos_algos =
        malloc(STEGX_NB_ALGO * sizeof(algo_e)), assert_non_null(stegx_propos_algos);
    *state = infos;
    return 0;
}

/* Teardown des tests unitaires pour les formats de fichiers */
static int test_file_info__teardown(void **state)
{
    info_s *infos = *state;
    fclose(infos->res);
    fclose(infos->hidden);
    free(infos->hidden_name);
    free(infos->passwd);
    free(infos);
    free(stegx_propos_algos);
    return 0;
}

/*
 * Tests BMP pour fill_host_info
 * ===================================================================================
 * */

void test_file_info_bmp_v1(void **state)
{
    info_s *infos = *state;
    infos->host.host =
        fopen("../../../env/test/bmp/test1.bmp", "r"), assert_non_null(infos->host.host);
    infos->host.type = BMP_COMPRESSED;

    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
    //HEADER SIZE
    assert_int_equal(infos->host.file_info.bmp.header_size, 138);
    //DATA SIZE
    assert_int_equal(infos->host.file_info.bmp.data_size, 14056960);
    //PIXEL LENGTH
    assert_int_equal(infos->host.file_info.bmp.pixel_length, 16);
    //NUMBER OF PIXELS = (pixel width (2584) * pixel height (2720))
    assert_int_equal(infos->host.file_info.bmp.pixel_number, 7028480);

    fclose(infos->host.host);
}

void test_file_info_bmp_v2(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/bmp/test4.bmp", "r");
    infos->host.type = BMP_UNCOMPRESSED;

    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
    //HEADER SIZE
    assert_int_equal(infos->host.file_info.bmp.header_size, 122);
    //DATA SIZE
    assert_int_equal(infos->host.file_info.bmp.data_size, 21085440);
    //PIXEL LENGTH
    assert_int_equal(infos->host.file_info.bmp.pixel_length, 24);
    //NUMBER OF PIXELS = (pixel width (2584) * pixel height (2720))
    assert_int_equal(infos->host.file_info.bmp.pixel_number, 7028480);

    fclose(infos->host.host);
}

void test_file_info_bmp_v3(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/bmp/test6.bmp", "r");
    infos->host.type = BMP_COMPRESSED;

    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
    //HEADER SIZE
    assert_int_equal(infos->host.file_info.bmp.header_size, 138);
    //DATA SIZE
    assert_int_equal(infos->host.file_info.bmp.data_size, 28113920);
    //PIXEL LENGTH
    assert_int_equal(infos->host.file_info.bmp.pixel_length, 32);
    //NUMBER OF PIXELS = (pixel width (2584) * pixel height (2720))
    assert_int_equal(infos->host.file_info.bmp.pixel_number, 7028480);

    fclose(infos->host.host);
}

/*
 * Tests PNG pour fill_host_info
 * =========================================================================================
 * */

void test_file_info_png_v1(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/png/test8.png", "r");
    infos->host.type = PNG;

    /* Valeurs à trouver: */
    stegx_suggest_algo(infos);
    //HEADER SIZE
    assert_int_equal(infos->host.file_info.png.header_size, 21);
    //DATA SIZE
    assert_int_equal(infos->host.file_info.png.data_size, 139005);

    fclose(infos->host.host);
}

void test_file_info_png_v2(void **state)
{
    info_s *infos = *state;
    infos->host.host =
        fopen("../../../env/test/png/test9.png", "r"), assert_non_null(infos->host.host);
    infos->host.type = PNG;

    /* Valeurs à trouver: */
    stegx_suggest_algo(infos);
    //HEADER SIZE
    assert_int_equal(infos->host.file_info.png.header_size, 21);
    //DATA SIZE
    assert_int_equal(infos->host.file_info.png.data_size, 20525);

    fclose(infos->host.host);
}

/*
 * Tests FLV pour fill_host_info
 * =================================================================================
 * */

/* Test sur un fichier FLV basic */
void test_file_info_flv_v1(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/flv/test13.flv", "r"),
        assert_non_null(infos->host.host);
    infos->host.type = FLV;

    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
    // NOMBRE DE VIDEO TAG :
    assert_int_equal(infos->host.file_info.flv.nb_video_tag, 166);
    // NOMBRE DE METADATA TAG :
    assert_int_equal(infos->host.file_info.flv.nb_metadata_tag, 1);
    // TOTAL SIZE
    assert_int_equal(infos->host.file_info.flv.file_size, 439099);

    fclose(infos->host.host);
}

/* Test sur un fichier FLV avec des données écrite après l'end of file */
void test_file_info_flv_v2(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/flv/test17.flv", "r"),
        assert_non_null(infos->host.host);
    infos->host.type = FLV;

    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
    // NOMBRE DE VIDEO TAG :
    assert_int_equal(infos->host.file_info.flv.nb_video_tag, 2);
    // NOMBRE DE METADATA TAG :
    assert_int_equal(infos->host.file_info.flv.nb_metadata_tag, 1);
    // TOTAL SIZE
    assert_int_equal(infos->host.file_info.flv.file_size, 88722);

    fclose(infos->host.host);
}

/*
 * Tests WAVE pour fill_host_info
 * =============================================================================
 */

static void test_file_info_wav__pcm_alaw_1(void **state)
{
    info_s *infos = *state;
    infos->host.host =
        fopen("../../../env/test/wave/WAVE_PCM(ALAW_16)_Mono_44,1kHz_1.wav", "r"),
        assert_non_null(infos->host.host);
    infos->host.type = WAV_NO_PCM;

    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
    // CHUNK SIZE :
    assert_int_equal(infos->host.file_info.wav.chunk_size, 8);
    // HEADER SIZE :
    assert_int_equal(infos->host.file_info.wav.header_size, 56);
    // DATA SIZE :
    assert_int_equal(infos->host.file_info.wav.data_size, 106408);
    // TOTAL SIZE : 106464

    fclose(infos->host.host);
}

static void test_file_info_wav__pcm_alaw_2(void **state)
{
    info_s *infos = *state;
    infos->host.host =
        fopen("../../../env/test/wave/WAVE_PCM(ALAW_16)_Mono_44,1kHz_2.wav", "r"),
        assert_non_null(infos->host.host);
    infos->host.type = WAV_NO_PCM;

    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
    // CHUNK SIZE :
    assert_int_equal(infos->host.file_info.wav.chunk_size, 8);
    // HEADER SIZE :
    assert_int_equal(infos->host.file_info.wav.header_size, 56);
    // DATA SIZE :
    assert_int_equal(infos->host.file_info.wav.data_size, 160580);
    // TOTAL SIZE : 160636

    fclose(infos->host.host);
}

static void test_file_info_wav__pcm_s16le(void **state)
{
    info_s *infos = *state;
    infos->host.host =
        fopen("../../../env/test/wave/WAVE_PCM(S16_LE)_Stereo_44,1kHz.wav", "r"),
        assert_non_null(infos->host.host);
    infos->host.type = WAV_NO_PCM;

    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
    // CHUNK SIZE :
    assert_int_equal(infos->host.file_info.wav.chunk_size, 16);
    // HEADER SIZE :
    assert_int_equal(infos->host.file_info.wav.header_size, 78);
    // DATA SIZE :
    assert_int_equal(infos->host.file_info.wav.data_size, 34230272);
    // TOTAL SIZE : 34230350

    fclose(infos->host.host);
}

/**
 * Tests MP3
 * =============================================================================
 */

static void test_file_info_mp3(void **state)
{
    /* Initialisation. */
    info_s *infos = *state;
    infos->host.type = MP3;

    /* Test sur tout types différents de MP3. */

    /* MP3 ID3v1. */
    infos->host.host = fopen(TEST_DIR"mp3/MP3_ID3v1_Stereo_44,1kHz_160kbps.mp3", "rb");
    assert_non_null(infos->host.host), stegx_suggest_algo(infos);
    assert_int_equal(infos->host.file_info.mp3.fr_frst_adr, 0x0);
    assert_int_equal(infos->host.file_info.mp3.fr_nb, 455);
    assert_int_equal(infos->host.file_info.mp3.eof, 0x3A046);
    assert_false(fclose(infos->host.host));

    /* MP3 ID3v1 avec données à la fin. */
    infos->host.host = fopen(TEST_DIR"mp3/MP3_ID3v1_Stereo_44,1kHz_160kbps_EOF.mp3", "rb");
    assert_non_null(infos->host.host), stegx_suggest_algo(infos);
    assert_int_equal(infos->host.file_info.mp3.fr_frst_adr, 0x0);
    assert_int_equal(infos->host.file_info.mp3.fr_nb, 455);
    assert_int_equal(infos->host.file_info.mp3.eof, 0x3A046);
    assert_false(fclose(infos->host.host));

    /* MP3 ID3v2.3 n°1. */
    infos->host.host = fopen(TEST_DIR"mp3/MP3_ID3v2.3_Stereo_44,1kHz_256kbps_1.mp3", "rb");
    assert_non_null(infos->host.host), stegx_suggest_algo(infos);
    assert_int_equal(infos->host.file_info.mp3.fr_frst_adr, 0x395);
    assert_int_equal(infos->host.file_info.mp3.fr_nb, 5744);
    assert_int_equal(infos->host.file_info.mp3.eof, 0x494800);
    assert_false(fclose(infos->host.host));

    /* MP3 ID3v2.3 n°1 avec données à la fin. */
    infos->host.host = fopen(TEST_DIR"mp3/MP3_ID3v2.3_Stereo_44,1kHz_256kbps_1_EOF.mp3", "rb");
    assert_non_null(infos->host.host), stegx_suggest_algo(infos);
    assert_int_equal(infos->host.file_info.mp3.fr_frst_adr, 0x395);
    assert_int_equal(infos->host.file_info.mp3.fr_nb, 5744);
    assert_int_equal(infos->host.file_info.mp3.eof, 0x494800);
    assert_false(fclose(infos->host.host));

    /* MP3 ID3v2.3 n°2. */
    infos->host.host = fopen(TEST_DIR"mp3/MP3_ID3v2.3_Stereo_44,1kHz_256kbps_2.mp3", "rb");
    assert_non_null(infos->host.host), stegx_suggest_algo(infos);
    assert_int_equal(infos->host.file_info.mp3.fr_frst_adr, 0x8E5);
    assert_int_equal(infos->host.file_info.mp3.fr_nb, 6928);
    assert_int_equal(infos->host.file_info.mp3.eof, 0x58676E);
    assert_false(fclose(infos->host.host));

    /* MP3 ID3v2.4 n°1. */
    infos->host.host = fopen(TEST_DIR"mp3/MP3_ID3v2.4_Mono_44,1kHz_64kbps.mp3", "rb");
    assert_non_null(infos->host.host), stegx_suggest_algo(infos);
    assert_int_equal(infos->host.file_info.mp3.fr_frst_adr, 0x2D);
    assert_int_equal(infos->host.file_info.mp3.fr_nb, 94);
    assert_int_equal(infos->host.file_info.mp3.eof, 0x4CE9);
    assert_false(fclose(infos->host.host));

    /* MP3 ID3v2.4 n°2. */
    infos->host.host = fopen(TEST_DIR"mp3/MP3_ID3v2.4_Unsync_Stereo_44,1kHz_192kbps.mp3", "rb");
    assert_non_null(infos->host.host), stegx_suggest_algo(infos);
    assert_int_equal(infos->host.file_info.mp3.fr_frst_adr, 0x8F5);
    assert_int_equal(infos->host.file_info.mp3.fr_nb, 2209);
    assert_int_equal(infos->host.file_info.mp3.eof, 0x152AC0);
    assert_false(fclose(infos->host.host));

    /* MP3 ID3v2.4 n°2 avec des données à la fin. */
    infos->host.host = fopen(TEST_DIR"mp3/MP3_ID3v2.4_Unsync_Stereo_44,1kHz_192kbps_EOF.mp3", "rb");
    assert_non_null(infos->host.host), stegx_suggest_algo(infos);
    assert_int_equal(infos->host.file_info.mp3.fr_frst_adr, 0x8F5);
    assert_int_equal(infos->host.file_info.mp3.fr_nb, 2209);
    assert_int_equal(infos->host.file_info.mp3.eof, 0x152AC0);
    assert_false(fclose(infos->host.host));
}

/**
 * Tests généraux
 * =============================================================================
 */

/* Setup des tests unitaires pour les propositions d'algos */
static int test_propos_algos__setup(void **state)
{
    info_s *infos = malloc(sizeof(info_s));
    assert_non_null(infos);
    infos->mode = STEGX_MODE_INSERT;
    infos->algo = STEGX_ALGO_EOF;
    infos->method = STEGX_WITH_PASSWD;
    infos->res = fopen("res.bmp", "w"), assert_non_null(infos->res);
    infos->hidden_name =
        malloc((strlen("hide.txt") + 1) * sizeof(char)), assert_non_null(infos->hidden_name);
    strcpy(infos->hidden_name, "hide.txt");
    infos->passwd = malloc((strlen("stegx") + 1) * sizeof(char)), assert_non_null(infos->passwd);
    strcpy(infos->passwd, "stegx");
    stegx_propos_algos =
        malloc(STEGX_NB_ALGO * sizeof(algo_e)), assert_non_null(stegx_propos_algos);
    *state = infos;
    return 0;
}

/* Teardown des tests unitaires pour les propositions d'algos */
static int test_propos_algos__teardown(void **state)
{
    info_s *infos = *state;
    fclose(infos->res);
    free(infos->hidden_name);
    free(infos->passwd);
    free(infos);
    free(stegx_propos_algos);
    return 0;
}

/* Test vérifiant la taille du fichier à cacher */
void test_hidden_length(void **state)
{
    info_s *infos = *state;
    infos->host.host =
        fopen("../../../env/test/bmp/test1.bmp", "r"), assert_non_null(infos->host.host);
    infos->host.type = BMP_COMPRESSED;
    infos->hidden = fopen("../../../env/test/bmp/test2.bmp", "r"), assert_non_null(infos->hidden);
    /* Valeurs à trouver : */
    stegx_suggest_algo(infos);
    assert_int_equal(infos->hidden_length, 14057098);

    fclose(infos->host.host);
    fclose(infos->hidden);
}

/*
 * Tests proposition des algos
 * ==================================================================================
 * */

/* Test sur BMP compressé. 
 * Le fichier à cacher est trop gros pour pouvoir proposer l'algorithme lsb
 * */
void test_propos_algos_v1(void **state)
{
    info_s *infos = *state;
    infos->host.host =
        fopen("../../../env/test/bmp/test1.bmp", "r"), assert_non_null(infos->host.host);
    infos->hidden =
        fopen("../../../env/test/wave/WAVE_PCM(S16_LE)_Stereo_44,1kHz.wav", "r"),
        assert_non_null(infos->hidden);
    infos->host.type = BMP_COMPRESSED;

    /* Valeurs à trouver */
    stegx_suggest_algo(infos);
    //LSB
    assert_int_equal(stegx_propos_algos[0], 0);
    //EOF
    assert_int_equal(stegx_propos_algos[1], 1);
    //METADATA
    assert_int_equal(stegx_propos_algos[2], 1);
    //EOC : end of chunk
    assert_int_equal(stegx_propos_algos[3], 0);
    //JUNK_CHUNK
    assert_int_equal(stegx_propos_algos[4], 0);

    fclose(infos->host.host);
    fclose(infos->hidden);
}

/* Test sur BMP non compressé */
void test_propos_algos_v2(void **state)
{
    info_s *infos = *state;
    infos->host.host =
        fopen("../../../env/test/bmp/test4.bmp", "r"), assert_non_null(infos->host.host);
    infos->hidden =
        fopen("../../../env/test/others/test16.txt", "r"), assert_non_null(infos->hidden);
    infos->host.type = BMP_UNCOMPRESSED;

    /* Valeurs à trouver */
    stegx_suggest_algo(infos);
    //LSB
    assert_int_equal(stegx_propos_algos[0], 1);
    //EOF
    assert_int_equal(stegx_propos_algos[1], 1);
    //METADATA
    assert_int_equal(stegx_propos_algos[2], 1);
    //EOC : end of chunk
    assert_int_equal(stegx_propos_algos[3], 0);
    //JUNK_CHUNK
    assert_int_equal(stegx_propos_algos[4], 0);

    fclose(infos->host.host);
    fclose(infos->hidden);
}

/* Test sur FLV */
void test_propos_algos_v3(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/flv/test13.flv", "r"),
        assert_non_null(infos->host.host);
    infos->hidden =
        fopen("../../../env/test/others/test16.txt", "r"), assert_non_null(infos->hidden);
    infos->host.type = FLV;

    /* Valeurs à trouver */
    stegx_suggest_algo(infos);
    //LSB
    assert_int_equal(stegx_propos_algos[0], 0);
    //EOF
    assert_int_equal(stegx_propos_algos[1], 1);
    //METADATA
    assert_int_equal(stegx_propos_algos[2], 0);
    //EOC : end of chunk
    assert_int_equal(stegx_propos_algos[3], 1);
    //JUNK_CHUNK
    assert_int_equal(stegx_propos_algos[4], 0);

    fclose(infos->host.host);
    fclose(infos->hidden);
}

/* Test sur l'AVI non compressé */
void test_propos_algos_v4(void **state)
{
    info_s *infos = *state;
    infos->host.host = fopen("../../../env/test/avi/test14.avi", "r"),
        assert_non_null(infos->host.host);
    infos->hidden =
        fopen("../../../env/test/others/test16.txt", "r"), assert_non_null(infos->hidden);
    infos->host.type = AVI_UNCOMPRESSED;

    /* Valeurs à trouver */
    stegx_suggest_algo(infos);
    //LSB
    assert_int_equal(stegx_propos_algos[0], 0);
    //EOF
    assert_int_equal(stegx_propos_algos[1], 0);
    //METADATA
    assert_int_equal(stegx_propos_algos[2], 0);
    //EOC : end of chunk
    assert_int_equal(stegx_propos_algos[3], 0);
    //JUNK_CHUNK
    assert_int_equal(stegx_propos_algos[4], 1);

    fclose(infos->host.host);
    fclose(infos->hidden);
}

/* Test sur du MP3. */
void test_propos_algos_v5(void **state)
{
    info_s *infos = *state;
    infos->host.type = MP3;
    infos->host.host = fopen(TEST_DIR"mp3/MP3_ID3v2.3_Stereo_44,1kHz_256kbps_2.mp3", "rb");
    assert_non_null(infos->host.host);

    /* Valeurs à trouver */
    infos->hidden = fopen(TEST_DIR"others/short.txt", "rb"), assert_non_null(infos->hidden);
    stegx_suggest_algo(infos);
    assert_int_equal(stegx_propos_algos[STEGX_ALGO_LSB], 1);
    assert_int_equal(stegx_propos_algos[STEGX_ALGO_EOF], 1);
    assert_int_equal(stegx_propos_algos[STEGX_ALGO_METADATA], 0);
    assert_int_equal(stegx_propos_algos[STEGX_ALGO_EOC], 0);
    assert_int_equal(stegx_propos_algos[STEGX_ALGO_JUNK_CHUNK], 0);
    assert_false(fclose(infos->hidden));

    /* Valeurs à trouver */
    infos->hidden = fopen(TEST_DIR"bmp/test4.bmp", "rb"), assert_non_null(infos->hidden);
    stegx_suggest_algo(infos);
    assert_int_equal(stegx_propos_algos[STEGX_ALGO_LSB], 0);
    assert_int_equal(stegx_propos_algos[STEGX_ALGO_EOF], 1);
    assert_int_equal(stegx_propos_algos[STEGX_ALGO_METADATA], 0);
    assert_int_equal(stegx_propos_algos[STEGX_ALGO_EOC], 0);
    assert_int_equal(stegx_propos_algos[STEGX_ALGO_JUNK_CHUNK], 0);
    assert_false(fclose(infos->hidden));

    assert_false(fclose(infos->host.host));
}

/* Test la taille par défaut du mot de passe lorsque la méthode sans
 * mot de passe a été choisit par l'utilisateur. */
void test_passwd_default_length(void **state)
{
    (void)state;
    info_s *infos = malloc(sizeof(info_s));
    infos->mode = STEGX_MODE_INSERT;
    infos->method = STEGX_WITHOUT_PASSWD;
    infos->host.host = fopen("../../../env/test/avi/test14.avi", "r"),
        assert_non_null(infos->host.host);
    infos->host.type = AVI_UNCOMPRESSED;
    infos->res = fopen("res.bmp", "w"), assert_non_null(infos->res);
    infos->hidden_name = malloc((strlen("test16.txt") + 1) * sizeof(char)),
        assert_non_null(infos->hidden_name);
    strcpy(infos->hidden_name, "test16.txt");
    infos->hidden =
        fopen("../../../env/test/others/test16.txt", "r"), assert_non_null(infos->host.host);
    infos->passwd = NULL;
    stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e)),
        assert_non_null(stegx_propos_algos);

    stegx_suggest_algo(infos);
    stegx_choose_algo(infos, STEGX_ALGO_EOF);

    int length_passwd_default = strlen(infos->passwd);

    fclose(infos->host.host);
    fclose(infos->res);
    fclose(infos->hidden);
    free(infos->hidden_name);
    free(infos->passwd);
    free(infos);
    free(stegx_propos_algos);

    assert_int_equal(length_passwd_default, LENGTH_DEFAULT_PASSWD);
}

/**
 * Main
 * =============================================================================
 */

int main(void)
{
    /* Liste des tests généraux. */
    const struct CMUnitTest propos_algos_tests[] = {
        cmocka_unit_test(test_hidden_length),
        cmocka_unit_test(test_propos_algos_v1),
        cmocka_unit_test(test_propos_algos_v2),
        cmocka_unit_test(test_propos_algos_v3),
        cmocka_unit_test(test_propos_algos_v4),
        cmocka_unit_test(test_propos_algos_v5)
    };

    /* Liste des tests de chaque format. */
    const struct CMUnitTest sugg_algos_tests_format[] = {
        //liste des tests pour BMP
        cmocka_unit_test(test_file_info_bmp_v1),
        cmocka_unit_test(test_file_info_bmp_v2),
        cmocka_unit_test(test_file_info_bmp_v3),
        //Liste des tests pour le PNG
        cmocka_unit_test(test_file_info_png_v1),
        cmocka_unit_test(test_file_info_png_v2),
        //Liste des tests pour le WAV
        cmocka_unit_test(test_file_info_wav__pcm_alaw_1),
        cmocka_unit_test(test_file_info_wav__pcm_alaw_2),
        cmocka_unit_test(test_file_info_wav__pcm_s16le),
        //Liste des tests pour le MP3
        cmocka_unit_test(test_file_info_mp3),
        //Liste des tests pour le FLV
        cmocka_unit_test(test_file_info_flv_v1),
        cmocka_unit_test(test_file_info_flv_v2)
    };

    /* Exécute les tests et retourne le nombre d'erreurs. */
    return cmocka_run_group_tests(sugg_algos_tests_format, test_file_info__setup,
                                  test_file_info__teardown) +
        cmocka_run_group_tests(propos_algos_tests, test_propos_algos__setup,
                               test_propos_algos__teardown) + run_test(test_passwd_default_length);
}
