/**
 * @file protection.c
 * @brief Algorithme de protection des données avec le mot de passe.
 * @details Module gérant la création d'une seed à partir d'un mot de passe et
 * l'algorithme de protection des données cachées.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <limits.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "protection.h"

unsigned int create_seed(const char *passwd)
{
    unsigned int srand_nb = 0;
    int j = 0;
    char carac = passwd[j];
    do {
        srand_nb = (srand_nb + carac) % UINT_MAX;
        j++;
        carac = passwd[j];
    } while (carac != '\0');
    return srand_nb;
}

int protect_data(uint8_t * tab, uint32_t hidden_length, const char *passwd, mode_e mode)
{

    // copie temporaire de tab car le resultat sera dans tab
    uint8_t *cpy = malloc(hidden_length * sizeof(uint8_t));
    if (!cpy)
        return perror("Can't allocate memory protection data"), 1;

    uint32_t i;
    // Tableau pour savoir si cette case a deja ete inseree dans result
    uint8_t *done = malloc(hidden_length * sizeof(uint8_t));
    if (!done)
        return perror("Can't allocate memory protection data"), 1;
    // on initialise cpy comme tab
    for (i = 0; i < hidden_length; i++) {
        cpy[i] = tab[i];
        //tab[i]=0; // pas obligatoire
        done[i] = NOT_DONE;     // aucune case n'a ete encore inséré
    }

    // Création de la seed pour la generation pseudo aleatoires de nombres
    srand(create_seed(passwd));

    /* 
     * hidden_length_recalcul : Nombre d'éléments du tableau data au fur 
     * et a mesure que les elements ont ete inseres dans result.
     * l : Entier representant le nombre d'éléments passés (vus) dans le tableau
     * m : Entier representant le curseur
     * */
    uint32_t hidden_length_recalcul = hidden_length + 1;
    uint32_t l, m, rang;

    // pour chaque element a cacher
    for (i = 0; i < hidden_length; i++) {
        l = m = 0;
        // on choisit au hasard le n-ieme élément a cacher
        rang = rand() % (hidden_length_recalcul - 1);   //-1 (au dernier tour rang vaudra 1)

        // Cas spécial : si rang == 0 on cherche le prochain element non rangé dans result
        if (rang == 0) {
            while (done[m] == 1) {
                m++;
            }
        }
        // Recherche du prochain element a mettre dans result
        while (l < rang) {
            /* si on passe sur un element deja fait on incremente le curseur 
             * mais pas le nombre d'éléments passés
             */
            if (done[m] == DONE) {
                m++;
            }
            // sinon on incremente le curseur et le nombre d'élements passés
            else {
                l++;
                m++;
            }
        }

        /* Cas spécial : si pendant la recherche, il ne manque plus qu'un 
         * élement non vu pour trouver l'élément a chercher , il suffit de 
         * chercher le prochain element non vu.
         * */
        if ((rang == l) && (done[m] == DONE)) {
            while (done[m] == DONE) {
                m++;
            }
        }

        /* l'élément recherché a été trouvé, on indique dans done que cet 
         * élément a été inséré dans result. 
         * */
        if (mode == STEGX_MODE_INSERT) {
            tab[m] = cpy[i];
        } else if (mode == STEGX_MODE_EXTRACT) {
            tab[i] = cpy[m];
        } else
            return 1;
        done[m] = DONE;
        hidden_length_recalcul--;
    }

    free(done);
    free(cpy);

    return 0;

}
