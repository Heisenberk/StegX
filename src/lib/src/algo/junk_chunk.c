/** 
 * @file junk_chunk.c
 * @brief Algorithme JUNK CHUNK.
 * @details Contient les fonctions concernant l'algorithme JUNK CHUNK.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "insert.h"
#include "protection.h"
#include "detect_algo.h"
#include "../file_type/avi.h"

int insert_junk_chunk(info_s * infos)
{
    /* Initialisation. */
    assert(infos);
    assert(infos->mode == STEGX_MODE_INSERT);
    assert(infos->algo == STEGX_ALGO_JUNK_CHUNK);
    if (fseek(infos->host.host, 0, SEEK_SET))
        return perror("JUNK_CHUNK: Can't jump to the beginning of the host file"), 1;
    if (fseek(infos->hidden, 0, SEEK_SET))
        return perror("JUNK_CHUNK: Can't jump to the beginning of the hidden file"), 1;

    uint8_t bytecpy;
    uint32_t bytecpy2;
    uint32_t file_size;
    uint32_t junk = JUNK;

    //copie RIFF
    fread(&bytecpy2, sizeof(uint32_t), 1, infos->host.host);
    fwrite(&bytecpy2, sizeof(uint32_t), 1, infos->res);

    //copie file_size       
    fread(&file_size, sizeof(uint32_t), 1, infos->host.host);
    fwrite(&file_size, sizeof(uint32_t), 1, infos->res);

    //copie du fichier hote sans les éventuelles données en eof
    for (uint32_t j = 0; j < file_size - 4; j++) {
        fread(&bytecpy, sizeof(uint8_t), 1, infos->host.host);
        fwrite(&bytecpy, sizeof(uint8_t), 1, infos->res);
    }
    //écriture JUNK
    fwrite(&junk, sizeof(uint32_t), 1, infos->res);
    if (write_signature(infos))
        return stegx_errno = ERR_INSERT, 1;

    /* Écriture des données du fichier à cacher. */

    /* Si le fichier à cacher est trop gros, on fait un XOR avec la 
     * suite pseudo aléatoire générée avec le mot de passe. */
    if (infos->hidden_length > LENGTH_FILE_MAX)
        return data_xor_write_file(infos->hidden, infos->res,
                                   infos->
                                   passwd) ? perror("JUNK_CHUNK: Can't write XORed hidden data"),
            1 : 0;
    /* Sinon on utilise la méthode de protection des données du mélange
     * des octets. */
    return data_scramble_write(infos->hidden, infos->res, infos->passwd, infos->hidden_length,
                               infos->
                               mode) ? perror("JUNK_CHUNK: Can't write scrambled hidden data"),
        1 : 0;

}

int extract_junk_chunk(info_s * infos)
{
    /* Initialisation. */
    assert(infos);
    assert(infos->mode == STEGX_MODE_EXTRACT);
    assert(infos->algo == STEGX_ALGO_JUNK_CHUNK);
    uint32_t file_size;
    if (fseek(infos->host.host, 0, SEEK_SET))
        return perror("EOF: Can't jump to the beginning of the host file"), 1;
    if (fseek(infos->host.host, 4, SEEK_SET))
        return perror("JUNK_CHUNK: Can't jump to file_size"), 1;

    //lecture de la taille du fichier
    fread(&file_size, sizeof(uint32_t), 1, infos->host.host);
    //deplacement jusqu'à la signature
    if (fseek(infos->host.host, file_size + 8, SEEK_SET))
        return perror("JUNK_CHUNK: Can't jump to StegX signature"), 1;

    if (sig_fseek(infos->host.host, infos->hidden_name, infos->method))
        return perror("JUNK_CHUNK: Can't jump over StegX signature"), 1;

    /* Écriture des données du fichier cacher. */

    /* Si le fichier cacher est trop gros, on fait un XOR avec la 
     * suite pseudo aléatoire générée avec le mot de passe. */
    if (infos->hidden_length > LENGTH_FILE_MAX)
        return data_xor_write_file(infos->host.host, infos->res,
                                   infos->
                                   passwd) ? perror("JUNK_CHUNK: Can't write deXORed hidden data"),
            1 : 0;
    /* Sinon on utilise la méthode de protection des données du mélange
     * des octets. */
    return data_scramble_write(infos->host.host, infos->res, infos->passwd, infos->hidden_length,
                               infos->
                               mode) ? perror("JUNK_CHUNK: Can't write descrambled hidden data"),
        1 : 0;
}
