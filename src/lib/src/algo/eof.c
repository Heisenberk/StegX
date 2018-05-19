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

/**
 * @brief Écrit des données XORées avec un mot de passe.
 * @internal Pas de gestion d'erreur dans la boucle car cela ralentit beaucoup.
 * Si tout à été bien fait avant, il ne devrait pas y avoir d'erreur !
 * @param src Fichier où lire la donnée.
 * @param res Fichier où écrire la donnée.
 * @param passwd Mot de passe utilisé pour générer la seed.
 * @return 0 si tout est ok, 1 s'il y a eu une erreur lors de la lecture du
 * fichier source.
 */
static int data_xor_write(FILE * src, FILE * res, const char * passwd)
{
    srand(create_seed(passwd));
    for (uint8_t b ; fread(&b, sizeof(b), 1, src) == 1 ;)
        fwrite((b ^= rand() % UINT8_MAX, &b), sizeof(b), 1, res);
    return ferror(src);
}

/**
 * @brief Écrit des données mélangé ou remise en ordre avec un mot de passe.
 * @param src Fichier où lire la donnée.
 * @param res Fichier où écrire la donnée.
 * @param pass Mot de passe utilisé pour générer la seed.
 * @param len Longueur des données à cacher / cacher.
 * @param m Mode d'utilisation (insertion ou extraction).
 * @return 0 si tout est ok, 1 s'il y a eu une erreur.
 */
static int data_scramble_write(FILE * src, FILE * res, const char * pass,
        const uint32_t len, const mode_e m)
{
    uint8_t *data = malloc(len * sizeof(uint8_t));
    if (!data)
        return perror("EOF: Can't allocate memory for copy hidden file"), 1;
    // Copie les données de fichier source dans data.
    if (fread(data, sizeof(*data), len, src) != len)
        return perror("EOF: Can't make a copy of hidden file"), 1;
    // Mélange ou remet en ordre les octets dans data.
    protect_data(data, len, pass, m);
    // Écriture des données dans le fichier resultat.
    if (fwrite(data, sizeof(*data), len, res) != len)
        return perror("EOF: Can't write hidden data"), 1;
    return free(data), 0;
}

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

    /* Déplacement à l'offset où il faut écrire la signature. */
    // Formats BMP, PNG, WAVE (structures identiques dans l'union).
    if ((infos->host.type >= BMP_COMPRESSED) && (infos->host.type <= PNG)) {
        // Recopie du fichier hôte. Utilisation de la taille et d'un compteur pour ne pas copier des données indésirables
        // qui serait à la fin du fichier. Pas des gestion d'erreur sur infos->res pour accélérer le traitement.
        for (unsigned int cnt = 0, size = infos->host.file_info.bmp.header_size + infos->host.file_info.bmp.data_size, b;
                fread(&b, sizeof(uint8_t), 1, infos->host.host) == 1 && cnt < size; cnt++)
            fwrite(&b, sizeof(uint8_t), 1, infos->res);
        if (ferror(infos->host.host))
            return perror("EOF: Can't read a copy of the host file"), 1;
    }
    //Format FLV
    if(infos->host.type == FLV){
		//Recopie du fichier hôte.
		for(uint8_t b; fread(&b, sizeof(uint8_t), 1, infos->host.host) == 1;)
			fwrite(&b, sizeof(uint8_t), 1, infos->res);
		if (ferror(infos->host.host))
            return perror("EOF: Can't read a copy of the host file"), 1;
    }

    /* Écriture de la signature. */
    if (write_signature(infos))
        return stegx_errno = ERR_INSERT, 1;

    /* Écriture des données du fichier à cacher. */

    /* Si le fichier à cacher est trop gros, on fait un XOR avec la 
     * suite pseudo aléatoire générée avec le mot de passe. */
    if (infos->hidden_length > LENGTH_FILE_MAX)
        return data_xor_write(infos->hidden, infos->res, infos->passwd) ? perror("EOF: Can't write XORed hidden data"), 1 : 0;
    /* Sinon on utilise la méthode de protection des données du mélange
     * des octets. */
    return data_scramble_write(infos->hidden, infos->res, infos->passwd, infos->hidden_length, infos->mode) ?
        perror("EOF: Can't write scrambled hidden data"), 1 : 0;
}

int extract_eof(info_s * infos)
{
    /* Initialisation. */
    assert(infos);
    assert(infos->mode == STEGX_MODE_EXTRACT);
    assert(infos->algo == STEGX_ALGO_EOF);
    if (fseek(infos->host.host, 0, SEEK_SET))
        return perror("EOF: Can't jump to the beginning of the host file"), 1;

    /* Déplacement à l'offset où la signature est écrite. */
    // Formats BMP, PNG, WAVE (structures identiques dans l'union).
    if ((infos->host.type >= BMP_COMPRESSED) && (infos->host.type <= PNG)) {
        if (fseek(infos->host.host, infos->host.file_info.bmp.header_size + infos->host.file_info.png.data_size, SEEK_SET))
            return perror("EOF: Can't jump to StegX signature"), 1;
    }
    //Format FLV
    if(infos->host.type == FLV) {
		if (fseek(infos->host.host, infos->host.file_info.flv.file_size, SEEK_SET))
			return perror("EOF: Can't jump to StegX signature"), 1;
    }

    /* Saut de la signature. */
    if (sig_fseek(infos->host.host, infos->hidden_name, infos->method))
        return perror("EOF: Can't jump over StegX signature"), 1;

    /* Écriture des données du fichier cacher. */

    /* Si le fichier cacher est trop gros, on fait un XOR avec la 
     * suite pseudo aléatoire générée avec le mot de passe. */
    if (infos->hidden_length > LENGTH_FILE_MAX)
        return data_xor_write(infos->host.host, infos->res, infos->passwd) ? perror("EOF: Can't write deXORed hidden data"), 1 : 0;
    /* Sinon on utilise la méthode de protection des données du mélange
     * des octets. */
    return data_scramble_write(infos->host.host, infos->res, infos->passwd, infos->hidden_length, infos->mode) ?
        perror("EOF: Can't write descrambled hidden data"), 1 : 0;
    return 0;
}
