#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

info_s *stegx_init(stegx_choices_s * choices)
{
    assert(choices);
    info_s *s = malloc(sizeof(info_s));
    int count, begin;
    int i, j;

    /* Initialisation de la variable globale de proposition des algorithmes. */
    if (!stegx_propos_algos)
        stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e));

    //OK mode
    s->mode = choices->mode;

    //OK host.host
    s->host.host = fopen(choices->host_path, "r");
    if (s->host.host == NULL) {
        stegx_errno = ERR_HOST_NULL;
        return NULL;
    }
    //OK hidden
    if (choices->mode == STEGX_MODE_INSERT) {
        s->hidden = fopen(choices->insert_info->hidden_path, "r");
        if (s->hidden == NULL) {
            stegx_errno = ERR_HIDDEN_NULL;
            return NULL;
        }
    } else
        s->hidden = NULL;

    //OK passwd+method
    if (choices->passwd != NULL) {
        count = strlen(choices->passwd);
        if (count == 0) {
            err_print(ERR_PASSWD);
        }
        count++;
        s->passwd = malloc(count * sizeof(char));

        for (i = 0; i < count; i++) {
            s->passwd[i] = choices->passwd[i];
        }
        if (choices->mode == STEGX_MODE_INSERT) {
            s->method = STEGX_WITH_PASSWD;
        }
    } else {
        if (choices->mode == STEGX_MODE_INSERT) {
            s->method = STEGX_WITHOUT_PASSWD;
        }
        s->passwd = NULL;
    }

    //OK res
    struct stat st;
    if (choices->mode == STEGX_MODE_EXTRACT) {
        // si on est en EXTRACT il faut absolument que le chemin soit un dossier
        if (stat(choices->res_path, &st) == 0) {
            if (!S_ISDIR(st.st_mode)) {
                stegx_errno = ERR_RES_EXTRACT;
                return NULL;
            }
        }
    }
    if (choices->mode == STEGX_MODE_EXTRACT) {
        s->res = NULL;
    } else {
        if (strcmp(choices->res_path, "stdout") == 0) {
            s->res = stdout;
        } else
            s->res = fopen(choices->res_path, "w");
        if (s->res == NULL) {
            // le fait que res_path ne soit pas un fichier est detecte ici
            stegx_errno = ERR_RES_INSERT;
            return NULL;
        }
    }

    // OK hidden_name
    if (choices->mode == STEGX_MODE_EXTRACT) {
        s->hidden_name = NULL;
    } else {
        count = strlen(choices->insert_info->hidden_path);
        begin = count - 1;
        while ((begin != 0) && (choices->insert_info->hidden_path[begin] != '/')) {
            begin--;
        }
        if (begin == 0)
            s->hidden_name = malloc((count + 1) * sizeof(char));
        else
            s->hidden_name = malloc((count - begin) * sizeof(char));
        j = 0;
        int begin_cdr;
        if (begin == 0)
            begin_cdr = begin;
        else
            begin_cdr = begin + 1;
        for (i = begin_cdr; i < count + 1; i++) {
            s->hidden_name[j] = choices->insert_info->hidden_path[i];
            j++;
        }
    }

    return s;
}

void stegx_clear(info_s * infos)
{
    if (infos->host.host != NULL)
        fclose(infos->host.host);
    if (infos->hidden != NULL)
        fclose(infos->hidden);
    if (infos->res != NULL)
        fclose(infos->res);
    free(infos->hidden_name);
    free(infos->passwd);
    free(infos);
    stegx_propos_algos = (free(stegx_propos_algos), NULL);
}
