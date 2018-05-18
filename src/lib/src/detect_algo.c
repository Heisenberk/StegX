/**
 * @file detect_algo.c
 * @brief Module de détection de l'algorithme.
 * @details Lecture de la signature d'un fichier hôte.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "stegx_common.h"
#include "stegx_errors.h"
#include "common.h"
#include "sugg_algo.h"

/** 
 * @brief Lit la signature contenu dans le fichier hôte.
 * @sideeffect Renseigne la structure \r{infos_s} avec les informations
 * contenues dans la signature.
 * @error \r{ERR_NEED_PASSWD} si le récepteur n'as pas fourni de mot de passe
 * alors qu'il aurait dû.
 * @param infos Structure représentant les informations concernant l'extraction.
 * @return 0 si la signature a bien été lue, sinon 1 et assigne \r{stegx_errno}
 * à l'erreur survenue.
 */
static int read_signature(info_s * infos)
{
    assert(infos && infos->mode == STEGX_MODE_EXTRACT);

    /* Longueur du nom du fichier caché. */
    uint8_t length_hidden_name;

    /* Saut à l'offset de la signature. Il faut prendre en compte les
     * spécificités de chaque format. */

    /* BMP, PNG et WAVE (car ils ont tout les trois "header_size" et "data_size"
     * en "uint32_t" au début de leurs structures). */
    if ((infos->host.type >= BMP_COMPRESSED) && (infos->host.type <= PNG)) {
        if (fseek(infos->host.host, infos->host.file_info.wav.header_size +
                  infos->host.file_info.wav.data_size, SEEK_SET))
            return perror("BMP, PNG & WAVE: Can't move to StegX signature"), 1;
    } else if (infos->host.type == MP3) {
    } else if (infos->host.type == AVI_COMPRESSED || infos->host.type == AVI_UNCOMPRESSED) {
    } else if (infos->host.type == FLV) {
    }

    /* Lecture de l'algorithme utilisé et de la méthode de protection utilisée. */
    if (fread(&(infos->method), sizeof(uint8_t), 1, infos->host.host) != 1)
        return perror("Sig: Can't read method"), 1;
    if (fread(&(infos->algo), sizeof(uint8_t), 1, infos->host.host) != 1)
        return perror("Sig: Can't read algo"), 1;

    /* Si l'émetteur a fournis un mot de passe et que le récepteur n'en a pas
     * fourni, on lève une erreur. */
    if ((infos->method == STEGX_WITH_PASSWD) && (infos->passwd == NULL))
        return stegx_errno = ERR_NEED_PASSWD, 1;

    /* Lecture de la taille du fichier caché. */
    if (fread(&(infos->hidden_length), sizeof(uint32_t), 1, infos->host.host) != 1)
        return perror("Sig: Can't read length hidden file"), 1;
    /* Lecture de la taille du nom du fichier caché + allocation. */
    if (fread(&length_hidden_name, sizeof(uint8_t), 1, infos->host.host) != 1)
        return perror("Sig: Can't read name length of hidden file"), 1;
    free(infos->hidden_name);
    if (!(infos->hidden_name = calloc((length_hidden_name + 1), sizeof(char))))
        return perror("Sig: Can't calloc for name of hidden file"), 1;

    /* Lecture du nom du fichier caché XOR avec le mot de passe (choisi par
     * l'utilisateur ou par l'application aléatoirement). */
    if (fread(infos->hidden_name, sizeof(char), length_hidden_name, infos->host.host) !=
        length_hidden_name)
        return perror("Sig: Can't read the name of hidden file"), 1;

    /* Si l'application a choisi un mot de passe par défaut aléatoirement, on va
     * le lire afin de pouvoir récupérer le nom du fichier qui est XOR avec
     * ce dernier. */
    if (infos->method == STEGX_WITHOUT_PASSWD) {
        /* Si l'utilisateur tape un mot de passe alors qu'il n'en a pas besoin,
         * il faut vider la memoire et réallouer par dessus. */
        free(infos->passwd);
        if (!(infos->passwd = calloc((LENGTH_DEFAULT_PASSWD + 1), sizeof(char))))
            return perror("Sig: Can't calloc password"), 1;
        if (fread(infos->passwd, sizeof(char), LENGTH_DEFAULT_PASSWD, infos->host.host) !=
            LENGTH_DEFAULT_PASSWD)
            return perror("Sig: Can't read password"), 1;
    }

    /* DéXOR du nom du fichier cacher. */
    for (int i = 0, j = 0; i < length_hidden_name; i++) {
        infos->hidden_name[i] = infos->hidden_name[i] ^ infos->passwd[j];
        j = infos->passwd[j + 1] ? j + 1 : 0;   /* Boucle sur le mot de passe. */
    }
    return 0;
}

int sig_fseek(FILE* f, char * h, method_e m)
{
    /* 2 octets pour l'algorithme et la méthode.
     * 4 octets pour la taille du fichier caché (uint32_t).
     * 1 octet pour la taille du nom du fichier caché.
     * 1 à 255 octets pour le nom du fichier caché (sans '\0').
     * 64 octets si StegX à utilisé un mot de passe par defaut . */
    return fseek(f, 2 + 4 + 1 + strlen(h) + LENGTH_DEFAULT_PASSWD * (m == STEGX_WITHOUT_PASSWD), SEEK_CUR);
}

int stegx_detect_algo(info_s * infos)
{
    /* Vérifie le mode d'utilisation, puis remplit la structure afin d'avoir la
     * structure spécifique de "infos->host.file_info". */
    if (infos->mode == STEGX_MODE_INSERT || fill_host_info(infos))
        return stegx_errno = ERR_DETECT_ALGOS, 1;
    /* Lecture de la signature pour connaître l'algorithme, la méthode,
       la taille des données cachées et le nom du fichier caché. */
    if (read_signature(infos))
        return stegx_errno == ERR_NEED_PASSWD ? 1 : (stegx_errno = ERR_DETECT_ALGOS), 1;
    return 0;
}
