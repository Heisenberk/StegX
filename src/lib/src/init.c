/**
 * @file init.c
 * @brief Fonction d'initialisation et de libération de la bibliothèque.
 * @details Fichier contenant la fonction d'initialisation de la structure
 * privée de la bibliothèque, ainsi que sa réciproque avec la fonction de
 * libération mémoire.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <libgen.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

info_s *stegx_init(stegx_choices_s * choices)
{
    /* Lors de l'extraction et de l'insertion : */
    /* - Le fichier résultat peux être sur stdout. */
    /* Lors de l'extraction : */
    /* - Le fichier hôte peux être sur stdin. */
    /* Lors de l'insertion : */
    /* - Le fichier à cacher peux être sur stdin. */

    assert(choices);
    info_s *s = calloc(1, sizeof(info_s));
    if (!s)
        return perror("Can't allocate memory for library private information structure"), NULL;

    /* Initialisation de la variable globale de proposition des algorithmes si
     * elle n'est pas déjà initialisée. Lors du free, il remettre le pointeur à
     * NULL pour bien spécifié que la zone n'est plus allouée : on pourrait
     * partager cette variable entre plusieurs structures "info_s" si on imagine
     * une interface qui appellent plusieurs fois "stegx_init" et "stegx_clear" sur
     * des structures différentes. */
    if (!stegx_propos_algos && !(stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e))))
        return perror("Can't allocate memory for stegx_propos_algos tab"), NULL;

    /* Initialisation du mode. */
    s->mode = choices->mode;

    /* Initialisation du mot de passe. */
    if (choices->passwd) {
        s->method = STEGX_WITH_PASSWD;
        if (!strlen(choices->passwd))
            return stegx_errno = ERR_PASSWD, NULL;
        if (!(s->passwd = strdup(choices->passwd)))
            return perror("Can't allocate memory for password"), NULL;
    } else
        s->method = STEGX_WITHOUT_PASSWD;

    /* Vérification du résultat. */
    if (!strcmp(choices->res_path, "stdout"))
        s->res = stdout;

    /* Initialisations pour l'insertion. */
    if (choices->mode == STEGX_MODE_INSERT) {
        assert(choices->insert_info);
        /* Initialisation du fichier à cacher. */
        if (!strcmp(choices->insert_info->hidden_path, "stdin"))
            s->hidden = stdin;
        else if (!(s->hidden = fopen(choices->insert_info->hidden_path, "rb")))
            return perror(NULL), stegx_errno = ERR_HIDDEN, NULL;
        /* L'algorithme sera choisi avec stegx_choose_algo(). */

        /* Initialisation du nom du fichier à cacher. */
        if (!(s->hidden_name = strdup(basename(choices->insert_info->hidden_path))))
            return perror("Can't allocate memory for the name of hidden file"), NULL;

        /* Initialisation et vérification du fichier résultat pour l'insertion. */
        if ((s->res != stdout) && !(s->res = fopen(choices->res_path, "wb")))
            return stegx_errno = ERR_RES_INSERT, NULL;
    }

    /* Initialisation pour l'extraction. */
    if (choices->mode == STEGX_MODE_EXTRACT) {
        /* Vérification du fichier hôte. */
        if (!strcmp(choices->host_path, "stdin"))
            s->host.host = stdin;
        /* Vérification du dossier résultat pour l'extraction. */
        if (s->res != stdout) {
            struct stat st;
            if (!stat(choices->res_path, &st)) {
                if (!S_ISDIR(st.st_mode))
                    return stegx_errno = ERR_RES_EXTRACT, NULL;
            } else
                return perror("Can't read properties of res path"), NULL;
        }
    }

    /* Initialisation du fichier hôte. */
    if ((s->host.host != stdin) && !(s->host.host = fopen(choices->host_path, "rb")))
        return perror(NULL), stegx_errno = ERR_HOST, NULL;

    assert(s->mode == STEGX_MODE_INSERT || s->mode == STEGX_MODE_EXTRACT);
    assert(s->algo >= STEGX_ALGO_LSB && s->algo < STEGX_NB_ALGO);
    assert(s->method == STEGX_WITHOUT_PASSWD || s->method == STEGX_WITH_PASSWD);
    assert(s->host.host);
    return s;
}

void stegx_clear(info_s * infos)
{
    /* On remet tout à NULL en libérant la mémoire. */
    if (infos->host.host)
        infos->host.host = (fclose(infos->host.host), NULL);
    if (infos->hidden)
        infos->hidden = (fclose(infos->hidden), NULL);
    if (infos->res)
        infos->res = (fclose(infos->res), NULL);
    infos->hidden_name = (free(infos->hidden_name), NULL);
    infos->passwd = (free(infos->passwd), NULL);
    infos = (free(infos), NULL);
    stegx_propos_algos = (free(stegx_propos_algos), NULL);
}
