#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "../insert.h"
#include "../protection.h"

int insert_eof(info_s * infos)
{
    assert(infos);
    assert(infos->mode == STEGX_MODE_INSERT);
    assert(infos->algo == STEGX_ALGO_EOF);
    uint32_t nb_cpy;            //nb doctets recopies
    uint8_t byte_cpy;           // octet recopie
    uint32_t header_size;
    uint32_t data_size;
    if (fseek(infos->host.host, 0, SEEK_SET) == -1)
        return perror("Can't make insertion EOF"), 1;
    if (fseek(infos->hidden, 0, SEEK_SET) == -1)
        return perror("Can't make insertion EOF"), 1;

    // pour les formats BMP, PNG
    if ((infos->host.type == BMP_COMPRESSED) || (infos->host.type == BMP_UNCOMPRESSED)
        || (infos->host.type == PNG)) {
        if ((infos->host.type == BMP_COMPRESSED) || (infos->host.type == BMP_UNCOMPRESSED)) {
            header_size = infos->host.file_info.bmp.header_size;
            data_size = infos->host.file_info.bmp.data_size;
        } else if (infos->host.type == PNG) {
            header_size = infos->host.file_info.png.header_size;
            data_size = infos->host.file_info.png.data_size;
        }
        // Recopie du header
        nb_cpy = 0;
        while (nb_cpy < header_size) {
            if (fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host) != 1)
                return perror("Can't read Header"), 1;
            if (fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res) == 0)
                return perror("Can't writ Header"), 1;
            nb_cpy++;
        }

        // Recopie du data
        nb_cpy = 0;
        while (nb_cpy < data_size) {
            if (fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host) == 0)
                return perror("Can't read Data"), 1;
            if (fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res) == 0)
                return perror("Can't write Data"), 1;
            nb_cpy++;
        }
    }
    // Ecriture de la signature
    if (write_signature(infos) == 1) {
        stegx_errno = ERR_INSERT;
        return 1;
    }
    
    // Ecriture des donnees du fichier a cacher
    if (fseek(infos->hidden, 0, SEEK_SET) == -1)
        return perror("Can't make insertion EOF"), 1;
    
    /* Si le fichier a cacher est trop gros, on fait XOR avec la 
     * suite pseudo aleatoire générée avec le mot de passe
     * */
    if(infos->hidden_length>LENGTH_HIDDEN_FILE_MAX){
		srand(create_seed(infos->passwd));
		int i = 0;  uint8_t random;
		while (fread(&byte_cpy, sizeof(uint8_t), 1, infos->hidden) != 0) {
			random=rand()%UINT8_MAX;
			byte_cpy=byte_cpy^random; //XOR avec le nombre pseudo aleatoire generé
			if (fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res) == 0)
				return perror("Can't write hidden data"), 1;
			i++;
		}
	}
	
	/* Sinon on utilise la méthode de protection des données du mélange
	 * des octets. 
	 * */
	else{
		uint8_t* data=malloc(infos->hidden_length*sizeof(uint8_t));
		if(!data)
			return perror("Can't allocate memory Insertion"), 1;
		uint32_t cursor=0;
		// Lecture des donnees a cacher et stockage ds data
		while (fread(&byte_cpy, sizeof(uint8_t), 1, infos->hidden) != 0) {
			data[cursor]=byte_cpy;
			cursor++;
		}
		// Melange des octets dans data
		protect_data(data,infos->hidden_length,infos->passwd,infos->mode);
		// Ecriture des donnees dans le fichier a cacher
		for(cursor=0;cursor<infos->hidden_length;cursor++){
			if (fwrite(&data[cursor], sizeof(uint8_t), 1, infos->res) == 0)
				return perror("Can't write hidden data"), 1;
		}
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
    if(infos->hidden_length>LENGTH_HIDDEN_FILE_MAX){
		srand(create_seed(infos->passwd));
		int i = 0; uint8_t random;
		while (fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host) != 0) {
			random=rand()%UINT8_MAX;
			byte_cpy=byte_cpy^random; //XOR avec le nombre pseudo aleatoire generé
			if (fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res) == 0)
				return perror("Can't write hidden data"), 1;
			i++;
		}
	}
	/* Sinon on utilise la méthode de protection des données du mélange
	 * des octets. 
	 * */
	else{
		uint8_t* data=malloc(infos->hidden_length*sizeof(uint8_t));
		if(!data)
			return perror("Can't allocate memory Extraction"), 1;
		
		// Lecture des donnees a extraire et stockage ds data
		uint32_t cursor=0;
		while (cursor<infos->hidden_length) {
			if(fread(&byte_read, sizeof(uint8_t), 1, infos->host.host) == 0)
				return perror("Can't read hidden data"), 1;
			data[cursor]=byte_read;
			cursor++;
		}
		// Remise dans l'ordre des octets dans data
		protect_data(data,infos->hidden_length,infos->passwd,infos->mode);
		
		// Ecriture des donnees dans le fichier a cacher
		for(cursor=0;cursor<infos->hidden_length;cursor++){
			if (fwrite(&data[cursor], sizeof(uint8_t), 1, infos->res) == 0)
				return perror("Can't write hidden data"), 1;
		}
		free(data);
	}
    
    return 0;
}
