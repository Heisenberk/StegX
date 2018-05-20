#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "../insert.h"
#include "../protection.h"

int insert_eoc(info_s * infos)
{
    assert(infos);
    assert(infos->mode == STEGX_MODE_INSERT);
    assert(infos->algo == STEGX_ALGO_EOC);
    uint8_t byte_cpy;
    uint8_t tmp;
    uint32_t limit;
    uint32_t data_size;
    uint32_t data_size_host;
    uint8_t tag_type; 
    uint32_t cpt_video_tag=0;
	uint32_t prev_tag_size;
    uint32_t data_per_vtag = infos->hidden_length / infos->host.file_info.flv.nb_video_tag;
    uint32_t reste = infos->hidden_length % infos->host.file_info.flv.nb_video_tag;
   
   uint8_t *data;
    if (fseek(infos->host.host, 0, SEEK_SET) == -1)
        return perror("Can't do insertion EOC"), 1;
	
	/* Si on peut utiliser l'algorithme de protection des données :
	 * initialisation de la protection */
    if(infos->host.file_info.flv.nb_video_tag<256){
		printf("ICIIIII\n");
    	data = malloc(infos->host.file_info.flv.nb_video_tag * sizeof(uint8_t));
        	if (!data)
            	return perror("Can't allocate memory Insertion"), 1;
        uint32_t cursor = 0;
        
        for(uint8_t i=0;i<infos->host.file_info.flv.nb_video_tag;i++){
            data[cursor]=i;
            cursor++;
         }
        protect_data(data,infos->host.file_info.flv.nb_video_tag,infos->passwd, infos->mode);
    }
    else
		if(data_per_vtag == 0)
			cpt_video_tag = infos->host.file_info.flv.nb_video_tag;
	
	//recopie header
	for(int j=0;j<13;j++){
		if (fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host) != 1)
			return perror("Can't read Header"), 1;
		if (fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res) == 0)
			return perror("Can't write Header"), 1;
		}
	
	do{
		//recherche video tag
		fread(&tag_type, sizeof(uint8_t), 1, infos->host.host);
		/* Si ce n'est pas un vidéo tag : recopie du chunk dans le fichier res */
		if (tag_type!=9){
				fwrite(&tag_type, sizeof(uint8_t), 1, infos->res);
				fread(&data_size, sizeof(data_size), 1, infos->host.host);
				fwrite(&data_size, sizeof(uint32_t), 1, infos->res);
				//passage en 24 bits      
					data_size = be32toh(data_size);
				data_size >>= 8;
				
				//recopie data + 6 octets
				for(uint32_t j=0;j<data_size+6;j++){
					fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host);
					fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res);
				}
				//recopie prev tag size
				fread(&prev_tag_size, sizeof(uint32_t), 1, infos->host.host);
				fwrite(&prev_tag_size, sizeof(uint32_t), 1, infos->res);
		}
		/* Si c'est un vidéo tag : insertion des données à cacher à la fin du chunk */
		else 
		{
			fwrite(&tag_type, sizeof(uint8_t), 1, infos->res);
			fread(&data_size, sizeof(data_size), 1, infos->host.host);
			 
			data_size_host=data_size;
			//passage en 24 bits      
			data_size = be32toh(data_size);
			data_size >>= 8;
			
			/* Ecriture de la nouvelle taille des datas.
			 * /!\ verifier que la taille à inscrire < 2^24
			 * cas particulier dernier tag (ou du premier si on utilise pas l'algo de protection) */
			if (cpt_video_tag==infos->host.file_info.flv.nb_video_tag-1 ||
					((infos->host.file_info.flv.nb_video_tag >= 256) && (data_per_vtag == 0)))
				data_size += reste+data_per_vtag;
			else
				data_size += data_per_vtag;
			//recopie data size en big endian			
			for(int i = 2; i >= 0; i--)
			{
				tmp = data_size>>(i*8);
				fwrite(&tmp,sizeof(uint8_t),1,infos->res);
			}
			
			//l'octet de droite qui fait parti des datas
			tmp = data_size_host;
			fwrite(&tmp,sizeof(uint8_t),1,infos->res);
			
			//copie des data d'origine + 6 octets
			data_size_host = be32toh(data_size_host) >> 8;
			for(uint32_t j=0; j < data_size_host + 6; j++){
					fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host);
					fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res);
			}
			//écriture données caché
			/* Si on utilise l'algo de mélange, on cherche le block de données à écrire. */
			if(infos->host.file_info.flv.nb_video_tag<256){
				uint8_t nb_chunk = data[cpt_video_tag];
				fseek(infos->hidden,nb_chunk*data_per_vtag, SEEK_SET);
				limit = (cpt_video_tag == infos->host.file_info.flv.nb_video_tag-1) ? 
						data_per_vtag + reste : data_per_vtag;
			}
			else
				/* Si on utilise pas l'algo de protection : */
				limit = ((data_per_vtag == 0) || (cpt_video_tag == infos->host.file_info.flv.nb_video_tag-1)) ? 
						data_per_vtag+reste : data_per_vtag;
			
			/* Ecriture des données cachées */
			for(uint32_t i=0;i<limit;i++){
				fread(&byte_cpy,sizeof(uint8_t),1,infos->hidden);
				fwrite(&byte_cpy,sizeof(uint8_t),1,infos->res);
			}

			 //lecture previous tagsize
			fread(&prev_tag_size,sizeof(uint32_t),1,infos->host.host);
			prev_tag_size=be32toh(prev_tag_size);

			/*modification du previous tag size pour rajouter le nombre d'octets venant d'être écrits.
			 * Et écriture de ce nombre */
			if (cpt_video_tag==infos->host.file_info.flv.nb_video_tag-1 || 
					((infos->host.file_info.flv.nb_video_tag >= 256) && (data_per_vtag == 0)))
				prev_tag_size += reste+data_per_vtag; //cas particulier dernier tag
			else 
				prev_tag_size +=data_per_vtag;
				
			prev_tag_size =htobe32(prev_tag_size);
			fwrite(&prev_tag_size,sizeof(uint32_t),1,infos->res);
			cpt_video_tag+=1;
		}
	}while(cpt_video_tag<infos->host.file_info.flv.nb_video_tag);
	
	/* Ecriture la fin du fichier, s'il reste d'autres données dans le fichier hôte,
	 * et de la signature */
	while(fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host)==1)
			fwrite(&byte_cpy,sizeof(uint8_t),1,infos->res);
    write_signature(infos);
    
    return 0;
}	

int extract_eoc(info_s * infos)
{
	assert(infos);
    assert(infos->mode == STEGX_MODE_EXTRACT);
    assert(infos->algo == STEGX_ALGO_EOC);
	uint8_t byte_cpy;
    uint32_t data_size;
    uint8_t tag_type; 
    uint32_t cpt_video_tag=0;
	uint32_t data_jump;
	uint32_t write_data;
	uint32_t data_per_vtag = infos->hidden_length / infos->host.file_info.flv.nb_video_tag;
    uint32_t reste = infos->hidden_length % infos->host.file_info.flv.nb_video_tag;
    uint8_t k=0;
    uint8_t search_tag;
	uint32_t cursor = 0;
   uint8_t *data;
   
   if (fseek(infos->host.host, 0, SEEK_SET) == -1)
        return perror("Can't do extraction EOC"), 1;

	/* Initialisation de protect data */
   if(infos->host.file_info.flv.nb_video_tag<256){
		data = malloc(infos->host.file_info.flv.nb_video_tag * sizeof(uint8_t));
        if (!data)
           	return perror("Can't allocate memory Insertion"), 1;        
        for(uint8_t i=0;i<infos->host.file_info.flv.nb_video_tag;i++){
            data[cursor]=i;
            cursor++;
        }
		protect_data(data,infos->host.file_info.flv.nb_video_tag,infos->passwd, infos->mode);
	}
	else
		if (data_per_vtag == 0)
			k = infos->host.file_info.flv.nb_video_tag-1;

	do {
		/* On saute le header */
		fseek(infos->host.host, 13, SEEK_SET);
		cpt_video_tag = 0;
		/* Si l'algo de protection des données a été utilisé */
		if(infos->host.file_info.flv.nb_video_tag<256)
		{
			cursor = 0;
			while(data[cursor] != k)
				cursor++;			
			/* Recherche du tag vidéo numéro cursor */
			while(cursor != (cpt_video_tag - 1)){
				fread(&tag_type, sizeof(uint8_t), 1, infos->host.host);
				if(tag_type == 9)
					cpt_video_tag++;
				fread(&data_size, sizeof(uint32_t), 1, infos->host.host);
				//passage en 24 bits      
				data_size = be32toh(data_size);
				data_size >>= 8;
				/* Si ce n'est pas le tag vidéo recherché, on jump 
				 * les 6 octets après data_size + les data + le previous tag size (4 octets) */ 
				if(cursor != (cpt_video_tag - 1))
					fseek(infos->host.host, data_size + 10, SEEK_CUR);
			}
		}
		/* Si l'algo de protection des données n'a pas été utilisé */
		else
		{
			cpt_video_tag = k;
			search_tag = 1;
			/* Recherche du prochain tag vidéo */
			while(search_tag)
			{
				fread(&tag_type, sizeof(uint8_t), 1, infos->host.host);
				if(tag_type != 9)
				{
					fread(&data_size, sizeof(uint32_t), 1, infos->host.host);
					//passage en 24 bits      
					data_size = be32toh(data_size);
					data_size >>= 8;
					fseek(infos->host.host, data_size + 10, SEEK_CUR);
				}
				else
					search_tag = 0;
			}
		}

		/* Calcul le nombre d'octets à sauter pour arriver avant les données à récupérer */
		if (cpt_video_tag==infos->host.file_info.flv.nb_video_tag){
			data_jump = data_size - reste - data_per_vtag + 6; //cas particulier dernier tag
			write_data = reste + data_per_vtag;
		}
		else {
			data_jump = data_size - data_per_vtag;
			write_data = data_per_vtag;
		}
		fseek(infos->host.host, data_jump, SEEK_CUR);
		/* Recopie des données dans le fichhier resultat */
		for(uint32_t i = 0; i < write_data; i++){
			fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host);
			fwrite(&byte_cpy,sizeof(uint8_t),1,infos->res);
		} 
		
		k++;
	}while(k != infos->host.file_info.flv.nb_video_tag-1);

	return 0;
}
