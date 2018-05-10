#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "../insert.h"

int insert_eof(info_s * infos)
{	
	assert(infos);
	assert(infos->mode==STEGX_MODE_INSERT);
    assert(infos->algo == STEGX_ALGO_EOF);
    int read;
    uint32_t nb_cpy;            //nb doctets recopies
    uint8_t byte_cpy;           // octet recopie
    uint32_t header_size;
    uint32_t data_size;
    if (fseek(infos->host.host, 0, SEEK_SET) == -1)
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

        nb_cpy = 0;
        // Recopie du header
        while (nb_cpy < header_size) {
			if (fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host) != 1)
				return perror("Can't read Header"), -1;
            if(fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res)==0)
				return perror("Can't writ Header"), -1;
            nb_cpy++;
        }
        // Recopie du data
        nb_cpy = 0;
        while (nb_cpy < (infos->host.file_info.bmp.data_size)) {
            if(fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host)==0)
				return perror("Can't read Data"), -1;
            if(fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res)==0)
				return perror("Can't write Data"), -1;
            nb_cpy++;
        }
    }
    
    // Ecriture de la signature
    write_signature(infos);

    // Ecriture des donnees du fichier a cacher
    int i = 0;
    // Ecriture des données à cacher en XOR avec le mot de passe
    if (fseek(infos->hidden, 0, SEEK_SET) == -1)
        return perror("Can't make insertion EOF"), 1;
    while (fread(&byte_cpy, sizeof(uint8_t), 1, infos->hidden) != 0) {
        if (infos->passwd[i] == '\0')
            i = 0;
        //byte_cpy ^= (infos->passwd[i]); //XOR
        if(fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res)==0)
			return perror("Can't write hidden data"), 1;
        i++;
    }

    return 0;
}

int extract_eof(info_s * infos)
{
    return 1;
}
