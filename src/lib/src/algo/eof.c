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
#include "detect_algo.h"

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
    // Formats BMP, PNG, WAVE (structures identiques dans l'union).
    if ((infos->host.type >= BMP_COMPRESSED) && (infos->host.type <= PNG)) {
        // Recopie du fichier hôte.
        while (fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host) == 1) {
            if (fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res) != 1)
                return perror("EOF: Can't write a copy of the host file"), 1;
        }
        if (ferror(infos->host.host))
            return perror("EOF: Can't read a copy of the host file"), 1;
    }

    /* Écriture de la signature. */
    if (write_signature(infos))
        return stegx_errno = ERR_INSERT, 1;

    /* Écriture des données du fichier à cacher. */

    /* Si le fichier à cacher est trop gros, on fait un XOR avec la 
     * suite pseudo aléatoire générée avec le mot de passe. */
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
            return perror("EOF: Can't allocate memory for copy hidden file"), 1;
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
    /* Initialisation. */
    assert(infos);
    assert(infos->mode == STEGX_MODE_EXTRACT);
    assert(infos->algo == STEGX_ALGO_EOF);
    if (fseek(infos->host.host, 0, SEEK_SET))
        return perror("EOF: Can't jump to the beginning of the host file"), 1;

    // Octet lu.
    uint8_t byte_cpy;

    /* Déplacement à l'offset où la signature est écrite. */
    // Formats BMP, PNG, WAVE (structures identiques dans l'union).
    if ((infos->host.type >= BMP_COMPRESSED) && (infos->host.type <= PNG)) {
        if (fseek(infos->host.host, infos->host.file_info.bmp.header_size + infos->host.file_info.png.data_size, SEEK_SET))
            return perror("EOF: Can't jump to StegX signature"), 1;
    }

    /* Saut de la signature. */
    if (sig_fseek(infos->host.host, infos->hidden_name, infos->method))
        return perror("EOF: Can't jump over StegX signature"), 1;

    /* Écriture des données du fichier cacher. */

    /* Si le fichier cacher est trop gros, on fait un XOR avec la 
     * suite pseudo aléatoire générée avec le mot de passe. */
    if (infos->hidden_length > LENGTH_FILE_MAX) {
        srand(create_seed(infos->passwd));
        while (fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host) != 0) {
            byte_cpy = byte_cpy ^ (rand() % UINT8_MAX);       // XOR avec le nombre pseudo aleatoire generé.
            if (fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res) == 0)
                return perror("EOF: Can't write deXORed hidden data"), 1;
        }
    }
    /* Sinon on utilise la méthode de protection des données du mélange
     * des octets. */
    else {
        uint8_t *data = malloc(infos->hidden_length * sizeof(uint8_t));
        if (!data)
            return perror("EOF: Can't allocate memory for copy hidden file"), 1;
        // Copie les données de fichier cacher dans data.
        if (fread(data, sizeof(uint8_t), infos->hidden_length, infos->host.host) != infos->hidden_length)
            return perror("EOF: Can't make a copy of hidden file"), 1;
        // Remise dans l'ordre des octets dans data.
        protect_data(data, infos->hidden_length, infos->passwd, infos->mode);
        // Écriture des données dans le fichier résultat.
        if (fwrite(data, sizeof(uint8_t), infos->hidden_length, infos->res) != infos->hidden_length)
            return perror("EOF: Can't write hidden data"), 1;
        free(data);
    }
    return 0;
}
