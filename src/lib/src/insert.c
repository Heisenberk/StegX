/**
 * @file insert.c
 * @brief Insertion des donnees cachees dans une copie de l'hote.
 * @details Module qui contient les fonctions qui permettent de faire 
 * l'insertion.
 */

#include <endian.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

#include "algo/lsb.h"
#include "algo/eof.h"
#include "algo/metadata.h"
#include "algo/eoc.h"
#include "algo/junk_chunk.h"

int write_signature(info_s * infos)
{
    assert(infos->host.host && infos->hidden && infos->res && infos->hidden_name
           && infos->mode != STEGX_MODE_EXTRACT);

    /* Ecriture de l'algorithme utilisé et de la méthode de protection utilisée. */
    if (fwrite(&(infos->method), sizeof(uint8_t), 1, infos->res) != 1)
        return perror("Sig: Can't write method"), 1;
    if (fwrite(&(infos->algo), sizeof(uint8_t), 1, infos->res) != 1)
        return perror("Sig: Can't write algo"), 1;


    /* Ecriture de la taille du fichier à cacher. */
    if (fwrite(&(infos->hidden_length), sizeof(uint32_t), 1, infos->res) != 1)
        return perror("Sig: Can't write length hidden file"), 1;

    /* Ecriture de la taille du nom du fichier à cacher. */
    uint16_t length_hidden_name = strlen(infos->hidden_name);
    if (length_hidden_name > LENGTH_HIDDEN_NAME_MAX)
        length_hidden_name = LENGTH_HIDDEN_NAME_MAX;
    if (fwrite(&length_hidden_name, sizeof(uint8_t), 1, infos->res) != 1)
        return perror("Sig: Can't write length hidden file"), 1;

    /* Copie du nom du fichier a cacher car on fait un XOR après. */
    char cpy_hidden_name[LENGTH_HIDDEN_NAME_MAX + 1] = { 0 };
    strncpy(cpy_hidden_name, infos->hidden_name, length_hidden_name + 1);

    /* Ecriture du XOR du nom du fichier a cacher avec le mot de passe
     * (length_hidden_name octets). */
    for (int i = 0, j = 0; cpy_hidden_name[i]; i++) {
        cpy_hidden_name[i] = cpy_hidden_name[i] ^ infos->passwd[j];
        j = infos->passwd[j + 1] ? j + 1 : 0;   /* Boucle sur le mot de passe. */
    }
    if (fwrite(cpy_hidden_name, sizeof(char), length_hidden_name, infos->res) != length_hidden_name)
        return perror("Sig: Can't write hidden file name"), 1;

    /* Ecriture du mot de passe s'il s'agit d'un mot de passe par défaut 
       choisi aléatoirement par l'application (64 octets). */
    if (infos->method == STEGX_WITHOUT_PASSWD) {
        if (fwrite(infos->passwd, sizeof(char), LENGTH_DEFAULT_PASSWD, infos->res) !=
            LENGTH_DEFAULT_PASSWD)
            return perror("Sig: Can't write default password"), 1;
    }
    return 0;
}

int stegx_insert(info_s * infos)
{
    int insertion;
    if (infos->mode != STEGX_MODE_INSERT) {
        stegx_errno = ERR_INSERT;
        return 1;
    }
    if (infos->algo == STEGX_ALGO_EOF) {
        insertion = insert_eof(infos);
    } else if (infos->algo == STEGX_ALGO_LSB) {
        insertion = insert_lsb(infos);
    } else if (infos->algo == STEGX_ALGO_METADATA) {
        insertion = insert_metadata(infos);
    } else if (infos->algo == STEGX_ALGO_EOC) {
        insertion = insert_eoc(infos);
    } else if (infos->algo == STEGX_ALGO_JUNK_CHUNK) {
        insertion = insert_junk_chunk(infos);
    } else {
        stegx_errno = ERR_INSERT;
        insertion = 1;
    }
    return insertion;
}
