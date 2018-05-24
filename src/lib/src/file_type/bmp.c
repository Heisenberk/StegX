/** 
 * @file bmp.c
 * @brief Fichier BMP.
 * @details Contient les informations (fonctions, types, structures) relatives
 * aux fichiers au format BMP.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "../insert.h"
#include "../protection.h"
#include "../endian.h"

/** Signature BMP */
#define SIG_BMP 0x4D42

type_e stegx_test_file_bmp(FILE * file)
{
    assert(file);
    if (fseek(file, 0, SEEK_SET) == -1)
        return perror("Can't move to BMP signature"), -1;
    // lecture de la signature BMP
    uint16_t sig_read;
    if (fread(&sig_read, sizeof(uint16_t), 1, file) != 1)
        return perror("Can't read BMP signature"), -1;
    if (sig_read != SIG_BMP) {
        return UNKNOWN;
    }

    if (fseek(file, ADDRESS_BMP_COMPRESS, SEEK_SET) == -1)
        return perror("Can't move to BMP Compression signature"), -1;
    // lecture pour déterminer si c'est compressé ou non
    uint32_t compress;
    if (fread(&compress, sizeof(uint32_t), 1, file) != 1)
        return perror("Can't read BMP Compression signature"), -1;
    if (compress == 0) {
        return BMP_UNCOMPRESSED;
    } else {
        return BMP_COMPRESSED;
    }
}

int insert_metadata_bmp(info_s * infos)
{
    assert(infos);
    assert(infos->mode == STEGX_MODE_INSERT);
    assert(infos->algo == STEGX_ALGO_METADATA);
    assert((infos->host.type == BMP_UNCOMPRESSED) || (infos->host.type == BMP_COMPRESSED));
    if (fseek(infos->host.host, 0, SEEK_SET) == -1)
        return perror("Can't make insertion METADATA"), 1;
    if (fseek(infos->hidden, 0, SEEK_SET) == -1)
        return perror("Can't make insertion METADATA"), 1;

    uint8_t byte_read_bmp;
    uint32_t nb_cpy = 0;
    uint32_t begin_def_pic;
    uint32_t new_length_file = infos->host.file_info.bmp.header_size +
        infos->host.file_info.bmp.data_size + infos->hidden_length;

    /* Recopie des octets jusqu'aux octets representant l'offset de 
     * définition de l'image
     * */
    uint16_t sig = SIG_BMP;
    if (fwrite(&sig, sizeof(uint16_t), 1, infos->res) == 0)
        return perror("BMP file: Can't write data host"), 1;

    // Ecriture de la nouvelle taille du fichier (incluant les donnees a cacher)
    if (fwrite(&new_length_file, sizeof(uint32_t), 1, infos->res) == 0)
        return perror("BMP file: Can't write data host"), 1;

    // Recopie des donnees jusqu'aux octets de l'offset de definition de l'image
    nb_cpy = sizeof(uint32_t) + sizeof(uint16_t);
    if (fseek(infos->host.host, sizeof(uint32_t) + sizeof(uint16_t), SEEK_SET))
        return perror("BMP file: Can not move in the file"), 1;
    while (nb_cpy < BMP_DEF_PIC) {
        if (fread(&byte_read_bmp, sizeof(uint8_t), 1, infos->host.host) != 1)
            return perror("BMP file: Can't read data host"), 1;
        if (fwrite(&byte_read_bmp, sizeof(uint8_t), 1, infos->res) == 0)
            return perror("BMP file: Can't write data host"), 1;
        nb_cpy++;
    }

    // Saut des 4 octets représentant l'offset de définition de l'image
    if (fseek(infos->host.host, sizeof(uint32_t), SEEK_CUR))
        return perror("BMP file: Can not move in the file"), 1;
    // Ecriture du nouvel offset apres insertion des donnees cachees
    begin_def_pic = infos->host.file_info.bmp.header_size + infos->hidden_length;
    if (fwrite(&begin_def_pic, sizeof(uint32_t), 1, infos->res) == 0)
        return perror("BMP file: Can't write data host"), 1;

    // Recopie du reste du header du fichier BMP
    nb_cpy = BMP_DEF_PIC + sizeof(uint32_t);
    while (nb_cpy < infos->host.file_info.bmp.header_size) {
        if (fread(&byte_read_bmp, sizeof(uint8_t), 1, infos->host.host) != 1)
            return perror("BMP file: Can't read data host"), 1;
        if (fwrite(&byte_read_bmp, sizeof(uint8_t), 1, infos->res) == 0)
            return perror("BMP file: Can't write data host"), 1;
        nb_cpy++;
    }

    // Ecriture des donnees du fichier a cacher
    /* Si le fichier a cacher est trop gros, on fait XOR avec la 
     * suite pseudo aleatoire générée avec le mot de passe
     * */
    if (infos->hidden_length > LENGTH_FILE_MAX) {
        srand(create_seed(infos->passwd));
        uint8_t random;
        while (fread(&byte_read_bmp, sizeof(uint8_t), 1, infos->hidden) != 0) {
            random = rand() % UINT8_MAX;
            byte_read_bmp = byte_read_bmp ^ random;     //XOR avec le nombre pseudo aleatoire generé
            if (fwrite(&byte_read_bmp, sizeof(uint8_t), 1, infos->res) == 0)
                return perror("Can't write hidden data"), 1;
        }
    }

    /* Sinon on utilise la méthode de protection des données du mélange
     * des octets. 
     * */
    else {
        uint8_t *data = malloc(infos->hidden_length * sizeof(uint8_t));
        if (!data)
            return perror("Can't allocate memory Insertion"), 1;
        uint32_t cursor = 0;
        // Lecture des donnees a cacher et stockage ds data
        while (fread(&byte_read_bmp, sizeof(uint8_t), 1, infos->hidden) != 0) {
            data[cursor] = byte_read_bmp;
            cursor++;
        }
        // Melange des octets dans data
        protect_data(data, infos->hidden_length, infos->passwd, infos->mode);
        // Ecriture des donnees dans le fichier a cacher
        for (cursor = 0; cursor < infos->hidden_length; cursor++) {
            if (fwrite(&data[cursor], sizeof(uint8_t), 1, infos->res) == 0)
                return perror("Can't write hidden data"), 1;
        }
        free(data);
    }

    // Recopie de data du fichier BMP
    nb_cpy = 0;
    while (nb_cpy < infos->host.file_info.bmp.data_size) {
        if (fread(&byte_read_bmp, sizeof(uint8_t), 1, infos->host.host) != 1)
            return perror("BMP file: Can't read data host"), 1;
        if (fwrite(&byte_read_bmp, sizeof(uint8_t), 1, infos->res) == 0)
            return perror("BMP file: Can't write data host"), 1;
        nb_cpy++;
    }

    // Ecriture de la signature
    if (write_signature(infos) == 1) {
        stegx_errno = ERR_INSERT;
        return 1;
    }
    return 0;
}

int extract_metadata_bmp(info_s * infos)
{
    assert(infos);
    assert(infos->mode == STEGX_MODE_EXTRACT);
    assert(infos->algo == STEGX_ALGO_METADATA);
    assert((infos->host.type == BMP_UNCOMPRESSED) || (infos->host.type == BMP_COMPRESSED));

    // Jump a au debut des donnees cachees
    if (fseek
        (infos->host.host, (infos->host.file_info.bmp.header_size) - (infos->hidden_length),
         SEEK_SET))
        return perror("BMP file: Can not move in the file"), 1;

    // Extraction des donnees cachees
    /* Si le fichier a cacher est trop gros, on fait XOR avec la 
     * suite pseudo aleatoire générée avec le mot de passe
     * */
    uint8_t byte_read, byte_cpy;
    if (infos->hidden_length > LENGTH_FILE_MAX) {
        srand(create_seed(infos->passwd));
        int i = 0;
        uint8_t random;
        while (fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host) != 0) {
            random = rand() % UINT8_MAX;
            byte_cpy = byte_cpy ^ random;       //XOR avec le nombre pseudo aleatoire generé
            if (fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res) == 0)
                return perror("Can't write hidden data"), 1;
            i++;
        }
    }
    /* Sinon on utilise la méthode de protection des données du mélange
     * des octets. 
     * */
    else {
        uint8_t *data = malloc(infos->hidden_length * sizeof(uint8_t));
        if (!data)
            return perror("Can't allocate memory Extraction"), 1;

        // Lecture des donnees a extraire et stockage ds data
        uint32_t cursor = 0;
        while (cursor < infos->hidden_length) {
            if (fread(&byte_read, sizeof(uint8_t), 1, infos->host.host) == 0)
                return perror("Can't read hidden data"), 1;
            data[cursor] = byte_read;
            cursor++;
        }
        // Remise dans l'ordre des octets dans data
        protect_data(data, infos->hidden_length, infos->passwd, infos->mode);

        // Ecriture des donnees dans le fichier a cacher
        for (cursor = 0; cursor < infos->hidden_length; cursor++) {
            if (fwrite(&data[cursor], sizeof(uint8_t), 1, infos->res) == 0)
                return perror("Can't write hidden data"), 1;
        }
        free(data);
    }

    return 0;
}
