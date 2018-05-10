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

/**
 * @brief fait le XOR entre le message et le mot de passe et le stocke dans message. 
 * @param *message représente le message a XOR avec le mot de passe.
 * @param *passwd représente le mot de passe choisi pour XOR le message. 
 */
void xor(char *message, char *passwd)
{
    int i = 0;
    int j = 0;
    do {
        message[i] = message[i] ^ passwd[j];    //XOR
        i++;
        j++;
        if (passwd[j] == '\0')
            j = 0;
    } while (message[i] != '\0');
}

int write_signature(info_s * infos)
{
    assert(infos->host.host);
    assert(infos->hidden);
    assert(infos->res);
    assert(infos->hidden_name);
    assert(infos->mode != STEGX_MODE_EXTRACT);
    int write;
    char car;
    int i = 0;
    uint8_t algo_used;

    // on ecrit quel algorithme a été utilisé (1 octet)
    if (infos->algo == STEGX_ALGO_EOF) {
        if (infos->method == STEGX_WITH_PASSWD) {
            algo_used = BYTE_EOF_WITH_PASSWD;
        } else if (infos->method == STEGX_WITHOUT_PASSWD) {
            algo_used = BYTE_EOF_WITHOUT_PASSWD;
        } else
            return 1;
    } else if (infos->algo == STEGX_ALGO_LSB) {
        if (infos->method == STEGX_WITH_PASSWD) {
            algo_used = BYTE_LSB_WITH_PASSWD;
        } else if (infos->method == STEGX_WITHOUT_PASSWD) {
            algo_used = BYTE_LSB_WITHOUT_PASSWD;
        } else
            return 1;
    } else if (infos->algo == STEGX_ALGO_METADATA) {
        if (infos->method == STEGX_WITH_PASSWD) {
            algo_used = BYTE_METADATA_WITH_PASSWD;
        } else if (infos->method == STEGX_WITHOUT_PASSWD) {
            algo_used = BYTE_METADATA_WITHOUT_PASSWD;
        } else
            return 1;
    } else if (infos->algo == STEGX_ALGO_EOC) {
        if (infos->method == STEGX_WITH_PASSWD) {
            algo_used = BYTE_EOC_WITH_PASSWD;
        } else if (infos->method == STEGX_WITHOUT_PASSWD) {
            algo_used = BYTE_EOC_WITHOUT_PASSWD;
        } else
            return 1;
    } else if (infos->algo == STEGX_ALGO_JUNK_CHUNK) {
        if (infos->method == STEGX_WITH_PASSWD) {
            algo_used = BYTE_JUNK_CHUNK_WITH_PASSWD;
        } else if (infos->method == STEGX_WITHOUT_PASSWD) {
            algo_used = BYTE_JUNK_CHUNK_WITHOUT_PASSWD;
        } else
            return 1;
    } else
        return 1;
    write = fwrite(&algo_used, sizeof(uint8_t), 1, infos->res);
    if (write == 0)
        return 1;

    // on ecrit en BIG ENDIAN la taille du fichier a cacher (4 octets)
    // on convertit la taille du fichier a cacher de la machine en BIG ENDIAN
    uint32_t length_written = infos->hidden_length;
    printf("INSERTION %x\n",length_written);
    write = fwrite(&length_written, sizeof(uint32_t), 1, infos->res);
    if (write == 0)
        return 1;

    // on ecrit la taille du nom du fichier caché (1 octet)
    uint8_t length = strlen(infos->hidden_name);
    if (length > 0xFF)
        length = LENGTH_HIDDEN_NAME_MAX;
    write = fwrite(&length, sizeof(uint8_t), 1, infos->res);
    if (write == 0)
        return 1;

    // on copie le nom du fichier a cacher car on fait un xor apres
    char *cpy_hidden_name = malloc(sizeof(char) * (length + 1));
    // on ne peut pas utiliser strlen car les 2 chaines ne sont pas de la meme longueur
    for (i = 0; i < length + 1; i++) {
        cpy_hidden_name[i] = infos->hidden_name[i];
    }
    cpy_hidden_name[length] = '\0';

    // on cache le nom du fichier a cache en XOR avec le mdp (255 octets)
    xor(cpy_hidden_name, infos->passwd);
    i = 0;
    srand(time(NULL));
    for (i = 0; i < length; i++) {
        car = cpy_hidden_name[i];
        fwrite(&car, sizeof(uint8_t), 1, infos->res);
    }
    free(cpy_hidden_name);

    /*
       on ecrit le mot de passe si il s'agit d'un mot de passe par défaut 
       choisi aléatoirement par l'application (64 octets)
     */
    if (infos->method == STEGX_WITHOUT_PASSWD) {
        for (i = 0; i < LENGTH_DEFAULT_PASSWD; i++) {
            car = infos->passwd[i];
            fwrite(&car, sizeof(uint8_t), 1, infos->res);
        }
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
