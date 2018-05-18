/** 
 * @file eof.c
 * @brief Algorithme EOF.
 * @details Contient les fonctions concernant l'algorithme EOF.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "insert.h"
#include "protection.h"

int insert_eof(info_s * infos)
{
    /* Initialisation. */
    assert(infos);
    assert(infos->mode == STEGX_MODE_INSERT);
    assert(infos->algo == STEGX_ALGO_EOF);
    if (fseek(infos->host.host, 0, SEEK_SET))
        return perror("EOF: Can't jump to the beginning of the host file"), 1;
    if (fseek(infos->hidden, 0, SEEK_SET))
        return perror("EOF: Can't jump to the beginning of the hidden file"), 1;

    // Octet lu.
    uint8_t byte_cpy;

    /* Déplacement à l'offset où il faut écrire la signature. */
    // Formats BMP, PNG, WAVE.
    if (((infos->host.type >= BMP_COMPRESSED) && (infos->host.type <= WAV_NO_PCM)) || (infos->host.type == PNG)) {
        // Recopie du fichier hôte.
        while (fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host) == 1) {
            if (fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res) != 1)
                return perror("EOF: Can't write a copy of the host file"), 1;
        }
        if (ferror(infos->host.host))
            return perror("EOF: Can't read a copy of the host file"), 1;
    }

    // Ecriture de la signature.
    if (write_signature(infos) == 1)
        return stegx_errno = ERR_INSERT, 1;

    // Ecriture des données du fichier a cacher.

    /* Si le fichier a cacher est trop gros, on fait un XOR avec la 
     * suite pseudo aleatoire générée avec le mot de passe. */
    if (infos->hidden_length > LENGTH_FILE_MAX) {
        srand(create_seed(infos->passwd));
        while (fread(&byte_cpy, sizeof(uint8_t), 1, infos->hidden) != 0) {
            byte_cpy = byte_cpy ^ (rand() % UINT8_MAX);       // XOR avec le nombre pseudo aleatoire generé.
            if (fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res) == 0)
                return perror("EOF: Can't write XORed hidden data"), 1;
        }
    }
    /* Sinon on utilise la méthode de protection des données du mélange
     * des octets. */
    else {
        uint8_t *data = malloc(infos->hidden_length * sizeof(uint8_t));
        if (!data)
            return perror("Can't allocate memory Insertion"), 1;
        // Copie les données de fichier à cacher dans data.
        if (fread(data, sizeof(uint8_t), infos->hidden_length, infos->hidden) != infos->hidden_length)
            return perror("EOF: Can't make a copy of hidden file"), 1;
        // Mélange des octets dans data.
        protect_data(data, infos->hidden_length, infos->passwd, infos->mode);
        // Écriture des données dans le fichier à cacher.
        if (fwrite(data, sizeof(uint8_t), infos->hidden_length, infos->res) != infos->hidden_length)
            return perror("EOF: Can't write hidden data"), 1;
        free(data);
    }
    return 0;
}

int extract_eof(info_s * infos)
{
    assert(infos);
    assert(infos->mode == STEGX_MODE_EXTRACT);
    assert(infos->algo == STEGX_ALGO_EOF);
    uint32_t header_size;
    uint32_t data_size;
    if (fseek(infos->host.host, 0, SEEK_SET) == -1)
        return perror("Can't make insertion EOF"), 1;

    // pour les formats BMP, PNG
    if ((infos->host.type == BMP_COMPRESSED) || (infos->host.type == BMP_UNCOMPRESSED)
        || (infos->host.type == PNG)) {

        // pour le format BMP manipulation structure bmp
        if ((infos->host.type == BMP_COMPRESSED) || (infos->host.type == BMP_UNCOMPRESSED)) {
            header_size = infos->host.file_info.bmp.header_size;
            data_size = infos->host.file_info.bmp.data_size;
        }
        // pour le format PNG manipulation structure png
        else if (infos->host.type == PNG) {
            header_size = infos->host.file_info.png.header_size;
            data_size = infos->host.file_info.png.data_size;
        }
        // déplacement jusqu'au debut de la signature
        if (fseek(infos->host.host, header_size, SEEK_SET) == -1)
            return perror("Can't make extraction EOF"), 1;
        if (fseek(infos->host.host, data_size, SEEK_CUR) == -1)
            return perror("Can't make extraction EOF"), 1;
    }

    /*  
       2 octets pour l'algo et la méthode
       4 octets pour la taille du fichier caché (uint32_t)
       1 octet pour la taille du nom du fichier caché
       1 à 255 octets pour le nom du fichier caché (sans '\0')
       64 octets si stegx a utilise un mot de passe par defaut 
     */
    // déplacement jusqu'à la fin de la signature
    int fseek_signature =
        2 + 4 + 1 + strlen(infos->hidden_name) + LENGTH_DEFAULT_PASSWD * (infos->method ==
                                                                          STEGX_WITHOUT_PASSWD);
    if (fseek(infos->host.host, fseek_signature, SEEK_CUR) == -1)
        return perror("Can't make extraction EOF"), 1;

    /* Si le fichier a cacher est trop gros, on fait XOR avec la 
     * suite pseudo aleatoire générée avec le mot de passe
     * */
    uint8_t byte_read, byte_cpy;
    if (infos->hidden_length > LENGTH_FILE_MAX) {
        srand(create_seed(infos->passwd));
        uint8_t random;
        while (fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host) != 0) {
            random = rand() % UINT8_MAX;
            byte_cpy = byte_cpy ^ random;       //XOR avec le nombre pseudo aleatoire generé
            if (fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res) == 0)
                return perror("Can't write hidden data"), 1;
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
