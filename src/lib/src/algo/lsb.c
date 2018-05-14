#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "../insert.h"

int insert_lsb(info_s * infos)
{
	assert(infos);
	assert(infos->mode==STEGX_MODE_INSERT);
    assert(infos->algo==STEGX_ALGO_LSB);
    uint32_t nb_cpy=0;            //nb doctets recopies
    uint32_t header_size,data_size;
    uint8_t byte_read_hidden,byte_read_host;
    uint8_t mask_host,mask_hidden;
    int i;
    if (fseek(infos->host.host, 0, SEEK_SET) == -1)
        return perror("Can't make jump host file"), 1;
    if (fseek(infos->hidden, 0, SEEK_SET) == -1)
        return perror("Can't make jump hidden file"), 1;
    
    // pour les formats BMP
    if (infos->host.type == BMP_UNCOMPRESSED){
		// Recopie du header dans le fichier resultat -> taille du header de l'hote
		while(nb_cpy<(infos->host.file_info.bmp.header_size)){
			if (fread(&byte_read_host, sizeof(uint8_t), 1, infos->host.host) ==0)
				return perror("Can't read header host"), 1;
			if (fwrite(&byte_read_host, sizeof(uint8_t), 1, infos->res) != 1)
				return perror("Sig: Can't write header host"), 1;
			nb_cpy++;
		}
		
		nb_cpy=0;
	    if (fseek(infos->hidden, 0, SEEK_SET) == -1)
			return perror("Can't make jump hidden file"), 1;
			
		mask_host=0xFC; // 11111100 en binaire
		
		// Cacher en LSB les donnees du fichier a cacher -> taille du fichier a cacher
        while(nb_cpy<(infos->hidden_length)){
			// Lecture de l'octet du fichier a cacher
			if (fread(&byte_read_hidden, sizeof(uint8_t), 1, infos->hidden) ==0)
				return perror("Can't read data hidden"), 2;
			// pour chaque paire de bits dans un octet (soit 4)
			mask_hidden=0xC0; // 11000000 en binaire
			for(i=0;i<4;i++){

				if (fread(&byte_read_host, sizeof(uint8_t), 1, infos->host.host) ==0)
					return perror("Can't read data host"), 1;
				// on remplace les 2 bits de poids faible par 2 bits de l'octet a cacher
				byte_read_host=(byte_read_host & mask_host)+((byte_read_hidden & mask_hidden)>>(-2*i+6));
				// -2*i+6 correspond a l'équation correspondant au déclage effectue en fonction 
				// de la localisation des bits de l'octet a cacher
				/*
				 * i==0 -> decalage de 6 vers la gauche
				 * i==1 -> decalage de 4 vers la gauche
				 * i==2 -> decalage de 2 vers la gauche
				 * i==3 -> decalage de 0 vers la gauche
				 */
				if (fwrite(&byte_read_host, sizeof(uint8_t), 1, infos->res) != 1)
					return perror("Sig: Can't write data host modified"), 1;
				mask_hidden>>=2;
			}
			nb_cpy++;
		}
		
		// represente le nombre d'octets a copier de host vers res
		uint32_t rest_host_cpy=(infos->host.file_info.bmp.data_size)-nb_cpy*4; 
		nb_cpy=0;
		// Recopie du reste des donnees de l'hote -> taille de data de l'hote - taille des octets utilisés pour cacher
		int i=0;
		while(rest_host_cpy!=0){
			 if(fread(&byte_read_host, sizeof(uint8_t), 1, infos->host.host)==0)
				return perror("Can't read data host"), 1;
            if(fwrite(&byte_read_host, sizeof(uint8_t), 1, infos->res)==0)
				return perror("Can't write data host"), 1;
			rest_host_cpy--;
		}
		
		// Ecriture de la signature
		if(write_signature(infos)==1) {
			stegx_errno=ERR_INSERT;
			return 1;
		}
		return 0;
    }
    // si les formats ne sont pas corrects erreur 
    return 1;
}

int extract_lsb(info_s * infos)
{
	assert(infos);
	assert(infos->mode==STEGX_MODE_EXTRACT);
    assert(infos->algo == STEGX_ALGO_LSB);
    uint32_t header_size,data_size;
    uint32_t nb_cpy;
    uint8_t byte_read_host;
    if (fseek(infos->host.host, 0, SEEK_SET) == -1)
        return perror("Can't make extraction LSB"), 1;
        
    // pour les formats BMP
    if (infos->host.type == BMP_UNCOMPRESSED){
		header_size = infos->host.file_info.bmp.header_size;
        data_size = infos->host.file_info.bmp.data_size;
        
        // déplacement jusqu'au debut de l'image brute
		if (fseek(infos->host.host,header_size, SEEK_SET) == -1)
			return perror("Can't make extraction EOF"), 1;
	
		nb_cpy=0;int i;
		uint8_t mask_host,mask_hidden; 
		uint8_t byte_created;
		// Extraire en LSB les donnees du fichier a cacher -> taille du fichier a cacher
        while(nb_cpy<(infos->hidden_length)){
			
			mask_host=0x03; // 00000011 en binaire
			mask_hidden=0xC0; //11000000 en binaire
			byte_created=0;
			for(i=0;i<4;i++){
				// Lecture de l'octet du fichier hote
				if (fread(&byte_read_host, sizeof(uint8_t), 1, infos->host.host) ==0)
					return perror("Can't read data host"), 1;
				byte_read_host=byte_read_host&mask_host; // pour obtenir les 2 derniers bits
				/*
				 * i==0 -> decalage de 6 vers la gauche
				 * i==1 -> decalage de 4 vers la gauche
				 * i==2 -> decalage de 2 vers la gauche
				 * i==3 -> decalage de 0 vers la gauche
				 */
				byte_read_host<<=(-2*i+6); // equation pour trouver le decalage a faire
				byte_created=byte_created+byte_read_host;
			}
			if (fwrite(&byte_created, sizeof(uint8_t), 1, infos->res) != 1)
					return perror("Sig: Can't write data hidden extracted"), 1;
			nb_cpy++;
		}
		return 0;
	}
    
    // si le format du fichier n'est pas correct -> renvoie une erreur
    return 1;
}
