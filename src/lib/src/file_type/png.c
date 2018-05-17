#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "../insert.h"
#include "../protection.h"

/** Signature PNG */
#define SIG_PNG 0x0A1A0A0D474E5089

type_e stegx_test_file_png(FILE * file)
{
    assert(file);
    if (fseek(file, 0, SEEK_SET) == -1)
        return perror("Can't move to PNG signature"), -1;
    // lecture signature PNG
    uint64_t sig_read;
    if (fread(&sig_read, sizeof(uint64_t), 1, file) != 1)
        return perror("Can't read PNG signature"), -1;
    if (sig_read != SIG_PNG) {
        return UNKNOWN;
    }
    return PNG;
}

int insert_metadata_png(info_s * infos)
{
    assert(infos);
    assert(infos->mode == STEGX_MODE_INSERT);
    assert(infos->algo == STEGX_ALGO_METADATA);
    assert(infos->host.type == PNG);
    if (fseek(infos->host.host, 0, SEEK_SET) == -1)
        return perror("Can't make insertion METADATA"), 1;
    if (fseek(infos->hidden, 0, SEEK_SET) == -1)
        return perror("Can't make insertion METADATA"), 1;

    uint32_t nb_cpy = 0;
    uint8_t byte_read_png;
    // Recopie du header du fichier PNG
    while (nb_cpy < infos->host.file_info.png.header_size) {
        if (fread(&byte_read_png, sizeof(uint8_t), 1, infos->host.host) != 1)
            return perror("PNG file: Can't read header"), 1;
        if (fwrite(&byte_read_png, sizeof(uint8_t), 1, infos->res) == 0)
            return perror("PNG file: Can't write header"), 1;
        nb_cpy++;
    }

    // Recopie du data du fichier PNG
    nb_cpy = 0;
    while (nb_cpy < infos->host.file_info.png.data_size - LENGTH_CHUNK_IEND) {
        if (fread(&byte_read_png, sizeof(uint8_t), 1, infos->host.host) != 1)
            return perror("PNG file: Can't read data"), 1;
        if (fwrite(&byte_read_png, sizeof(uint8_t), 1, infos->res) == 0)
            return perror("PNG file: Can't write data"), 1;
        nb_cpy++;
    }
    
    // Lecture des donnees a cacher et stockage dans data
    uint8_t *data = malloc(infos->hidden_length * sizeof(uint8_t));
    if (!data)
		return perror("Can't allocate memory Extraction"), 1;
	if (fseek(infos->hidden, 0, SEEK_SET) == -1)
        return perror("Can't make insertion EOF"), 1;
    uint32_t length;
    for(length=0;length<infos->hidden_length;length++){
		if (fread(&byte_read_png, sizeof(uint8_t), 1, infos->hidden) != 1)
            return perror("PNG file: Can't read data"), 1;
        data[length]=byte_read_png;
	}
	
	/* Si le fichier depasse la limite de taille imposee
	 * on fait un XOR avec les nombres pseudo aleatoires generes à partir 
	 * du seed (grace au mot de passe)
	 **/
	if (infos->hidden_length > LENGTH_FILE_MAX) {
		srand(create_seed(infos->passwd));
		uint8_t random;
		for(length=0;length<infos->hidden_length;length++){
			random = rand() % UINT8_MAX;
            data[length] = data[length] ^ random;       //XOR avec le nombre pseudo aleatoire generé
		}
	}
	// Sinon on fait le melange des octets des donnees a cacher
	else{
		 protect_data(data,infos->hidden_length, infos->passwd, infos->mode);
	}

    // Creation de 2 chunks tEXt pour cacher les donnees dans le fichier PNG
    uint32_t part_length_hidden = ((infos->hidden_length) / 2) + 4;
    //+4 pour reconnaitre que ce chunk tEXt a ete cree par STEGX 
    length=0;
    uint32_t part_length_hidden_big_endian = htobe32(part_length_hidden);
    uint32_t sig = SIG_tEXt;
    for (int i = 0; i < 2; i++) {
        // Recopie en big endian de la taille du chunk tEXt
        if (fwrite(&part_length_hidden_big_endian, sizeof(uint32_t), 1, infos->res) == 0)
            return perror("PNG file: Can't write length of chunk tEXt"), 1;
        // Recopie de la signature tEXt
        if (fwrite(&sig, sizeof(uint32_t), 1, infos->res) == 0)
            return perror("PNG file: Can't write length of chunk tEXt"), 1;
        // Recopie des 4 octets STEGX pour reconnaitre le chunk tEXt
        sig = SIG_STEGX_PNG;
        if (fwrite(&sig, sizeof(uint32_t), 1, infos->res) == 0)
            return perror("PNG file: Can't write length of chunk tEXt"), 1;
        nb_cpy = 0; 
        // Recopie des donnees a cacher
        while (nb_cpy < (part_length_hidden - 4)) {
            if (fwrite(&data[length], sizeof(uint8_t), 1, infos->res) == 0)
                return perror("PNG file: Can't write data hidden"), 1; 
            nb_cpy++;length++;
        }
        // Ecriture du CRC du chunk tEXt nouvellement créé
        sig = 0x00;
        if (fwrite(&sig, sizeof(uint32_t), 1, infos->res) == 0)
            return perror("PNG file: Can't write CRC of chunk tEXt"), 1;

        // pour le deuxieme chunk cree on prend les donnees restantes a cacher
        part_length_hidden = (infos->hidden_length) - ((infos->hidden_length) / 2) + 4;
        part_length_hidden_big_endian = htobe32(part_length_hidden);
        sig = SIG_tEXt;
    }

    // Ecriture du chunk IEND 
    nb_cpy = 0;
    while (nb_cpy < LENGTH_CHUNK_IEND) {
        if (fread(&byte_read_png, sizeof(uint8_t), 1, infos->host.host) != 1)
            return perror("PNG file: Can't read data"), 1;
        if (fwrite(&byte_read_png, sizeof(uint8_t), 1, infos->res) == 0)
            return perror("PNG file: Can't write data"), 1;
        nb_cpy++;
    }

    // Ecriture de la signature
    if (write_signature(infos) == 1) {
        stegx_errno = ERR_INSERT;
        return 1;
    }
    free(data);
    return 0;
}

int extract_metadata_png(info_s * infos)
{
    assert(infos);
    assert(infos->mode == STEGX_MODE_EXTRACT);
    assert(infos->algo == STEGX_ALGO_METADATA);
    assert(infos->host.type == PNG);
    uint32_t chunk_size, chunk_id, sig, nb_cpy;
    uint8_t byte_read_png;

    // Jump apres la signature
    if (fseek(infos->host.host, LENGTH_SIG_PNG, SEEK_SET))
        return perror("PNG file: Can not move in the file"), 1;

    chunk_id = 0;
    if (fread(&chunk_size, sizeof(uint32_t), 1, infos->host.host) != 1)
        return perror("PNG file: Can't read length of chunk"), 1;
    chunk_size = be32toh(chunk_size);
    if (fread(&chunk_id, sizeof(uint32_t), 1, infos->host.host) != 1)
        return perror("PNG file: Can't read ID of chunk"), 1;
        
    uint8_t *data = malloc(infos->hidden_length * sizeof(uint8_t));
    if (!data)
		return perror("Can't allocate memory Extraction"), 1;
	uint32_t length=0;
    // Lecture de tous les chunks du fichier a analyser     
    uint8_t bool_stegx_text = 0;
    do {
        // si il s'agit d'un chunk tEXt
        if (chunk_id == SIG_tEXt) {
            nb_cpy = 0;         // lecture des 4 premiers octets de data du chunk tEXt
            if (fread(&sig, sizeof(uint32_t), 1, infos->host.host) != 1)
                return perror("PNG file: Can't read data"), 1;
            // si les 4 premiers octets sont STEG -> chunk tEXt utilisé par StegX
            if (sig == SIG_STEGX_PNG)
                bool_stegx_text = 1;
            while (nb_cpy < (chunk_size - 4)) {
                if (fread(&byte_read_png, sizeof(uint8_t), 1, infos->host.host) != 1)
                    return perror("PNG file: Can't read data"), 1;
                if (bool_stegx_text == 1) {     // Ecriture des donnees cachees
                    /*if (fwrite(&byte_read_png, sizeof(uint8_t), 1, infos->res) == 0)
                        return perror("PNG file: Can't write data"), 1;*/
                    data[length]=byte_read_png;
                    length++;
                }
                nb_cpy++;
            }
            if (fseek(infos->host.host, LENGTH_CRC, SEEK_CUR))
                return perror("PNG file: Can not move in the file"), 1;
            bool_stegx_text = 0;
        }

        else {
            if (fseek(infos->host.host, chunk_size + LENGTH_CRC, SEEK_CUR))
                return perror("PNG file: Can not move in the file"), 1;
        }

        // Lecture de la taille et de ID du prochain chunk (pour le prochain tour de boucle)
        if (fread(&chunk_size, sizeof(uint32_t), 1, infos->host.host) != 1)
            return perror("PNG file: Can't read length of chunk"), 1;
        chunk_size = be32toh(chunk_size);
        if (fread(&chunk_id, sizeof(uint32_t), 1, infos->host.host) != 1)
            return perror("PNG file: Can't read ID of chunk"), 1;
    } while (chunk_id != SIG_IEND);
    
    /* Si le fichier depasse la limite de taille imposee
	 * on fait un XOR avec les nombres pseudo aleatoires generes à partir 
	 * du seed (grace au mot de passe)
	 **/
    if (infos->hidden_length > LENGTH_FILE_MAX) {
		srand(create_seed(infos->passwd));
		uint8_t random;
		for(length=0;length<infos->hidden_length;length++){
			random = rand() % UINT8_MAX;
            data[length] = data[length] ^ random;       //XOR avec le nombre pseudo aleatoire generé
		}
	}
	// Sinon on fait remet dans l'ordre les octets des donnees cachées
	else{
		 protect_data(data,infos->hidden_length, infos->passwd, infos->mode);
	}
    
    for(length=0;length<infos->hidden_length;length++){
		if (fwrite(&data[length], sizeof(uint8_t), 1, infos->res) == 0)
			return perror("PNG file: Can't write data"), 1;
	}
    
    free(data);

    return 0;
}
