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
    uint32_t nb_cpy;            //nb doctets recopies
    uint8_t byte_cpy;           // octet recopie
    uint32_t header_size;
    // pour les formats BMP, PNG
    fseek(infos->host.host, 0, SEEK_SET);
    if ((infos->host.type == BMP_COMPRESSED) || (infos->host.type == BMP_UNCOMPRESSED)
        || (infos->host.type == PNG)) {
        if ((infos->host.type == BMP_COMPRESSED) || (infos->host.type == BMP_UNCOMPRESSED))
            header_size = infos->host.file_info.bmp.header_size;
        else if (infos->host.type == PNG)
            header_size = infos->host.file_info.png.header_size;

        nb_cpy = 0;
        // on recopie le header
        while (nb_cpy < header_size) {
            fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host);
            fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res);
            nb_cpy++;
        }
        // on recopie le data
        nb_cpy = 0;
        while (nb_cpy < (infos->host.file_info.bmp.data_size)) {
            fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host);
            fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res);
            nb_cpy++;
        }
    }
    
    // ecriture de la signature
    write_signature(infos);

    // on ne peut pas utiliser le melange des donnees pour EOF et Metadata
    // car cela prend trop de temps (6 secondes pour 4ko a cacher) -> 
    // testé par clement pendant les vacances -> solution = XOR avec MDP
    // ecriture des donnees du fichier a cacher
    int i = 0;
    // écriture des données à cacher en XOR avec le mot de passe
    fseek(infos->hidden, 0, SEEK_SET);
    while (fread(&byte_cpy, sizeof(uint8_t), 1, infos->hidden) != 0) {
        if (infos->passwd[i] == '\0')
            i = 0;
        byte_cpy ^= (infos->passwd[i]); //XOR
        i++;
        fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res);
    }

    return 0;
}

int extract_eof(info_s * infos)
{
    (void) infos; /* Unused. */
    return 1;
}
