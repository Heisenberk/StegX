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
    uint8_t byte_cpy;
    uint32_t data_size;
    uint8_t tag_type; 
    uint32_t cpt_video_tag=0;
	assert(infos);
    assert(infos->mode == STEGX_MODE_INSERT);
    assert(infos->algo == STEGX_ALGO_EOC);
    uint32_t prev_tag_size;
    uint32_t data_per_vtag=infos->hidden_length/infos->host.file_info.flv.nb_video_tag;
    uint32_t reste=infos->hidden_length%infos->host.file_info.flv.nb_video_tag;
   uint8_t *data;

    if ((fseek(infos->host.host, 0, SEEK_SET) == -1) || (fseek(infos->hidden,0,SEEK_SET) == -1)){
        return perror("Can't do insertion EOC"), 1;
	}

	data = malloc(infos->host.file_info.flv.nb_video_tag * sizeof(uint8_t));
	if (!data)
		return perror("Can't allocate memory Insertion"), 1;
		
	for(uint32_t i=0;i<infos->host.file_info.flv.nb_video_tag;i++){
		data[i]=i;
	 }
    if(infos->host.file_info.flv.nb_video_tag<256){
        protect_data(data,infos->host.file_info.flv.nb_video_tag,infos->passwd, infos->mode);
 }   
 //~ for(uint8_t i=0;i<infos->host.file_info.flv.nb_video_tag;i++){
            //~ printf("video_tag : %u  nb_blocks : %u\n",i, data[i]);
            
        //~ }
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
    		if (tag_type!=9){
    		    	fwrite(&tag_type, sizeof(uint8_t), 1, infos->res);
    		    	fread(&data_size, sizeof(data_size), 1, infos->host.host);
    		    	fwrite(&data_size, sizeof(uint32_t), 1, infos->res);
    		    	//passage en 24 bits      
           	  	  	data_size = be32toh(data_size) >> 8;
        			//recopie data + 6 octets
        			for(uint32_t j=0;j<data_size+6;j++){
        				fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host);
    			  		fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res);
    				}
    				//recopie prev tag size
    				fread(&prev_tag_size, sizeof(uint32_t), 1, infos->host.host);
    				fwrite(&prev_tag_size, sizeof(uint32_t), 1, infos->res);
    		}
    		else {
    			fwrite(&tag_type, sizeof(uint8_t), 1, infos->res);
    			fread(&data_size, sizeof(data_size), 1, infos->host.host);
    			 
    			/* /!\ */
    			uint8_t tmp = data_size; //l'octet de droite qui fait parti des datas
    			//passage en 24 bits      
            	data_size = be32toh(data_size) >> 8;

            	uint32_t data_size_host=data_size;
			/* Ecriture de la nouvelle taille des datas.
			 * /!\ verifier que la taille à inscrire < 2^24
			 * cas particulier dernier tag (ou du premier si on utilise pas l'algo de protection) */
            	if (data[cpt_video_tag] == infos->host.file_info.flv.nb_video_tag-1)
					data_size += reste + data_per_vtag;
            	else 
					data_size += data_per_vtag;
				
            	uint8_t tmp2=data_size;
            	uint8_t tmp3=data_size>>8;
            	uint8_t tmp4=data_size>>16;
            	//recopie data size en big endian

            	fwrite(&tmp4,sizeof(uint8_t),1,infos->res);
            	fwrite(&tmp3,sizeof(uint8_t),1,infos->res);
            	fwrite(&tmp2	,sizeof(uint8_t),1,infos->res);
            	fwrite(&tmp,sizeof(uint8_t),1,infos->res);
            	//copie des data d'origine + 6 octets

            	for(uint32_t j=0;j<data_size_host+6;j++){
        				fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host);
    			  		fwrite(&byte_cpy, sizeof(uint8_t), 1, infos->res);
    			 }
    			 
    			 //écriture données caché
    			uint8_t nb_block = data[cpt_video_tag];
    			fseek(infos->hidden, nb_block*data_per_vtag, SEEK_SET);
    			uint32_t limit;
				limit = (nb_block == infos->host.file_info.flv.nb_video_tag-1) ? 
										data_per_vtag + reste : data_per_vtag;
    			for(uint32_t i=0;i<limit;i++){
    				fread(&byte_cpy,sizeof(uint8_t),1,infos->hidden);
    				fwrite(&byte_cpy,sizeof(uint8_t),1,infos->res);

    			}
    			 //lecture previous tagsize
    			fread(&prev_tag_size,sizeof(uint32_t),1,infos->host.host);
    			prev_tag_size = be32toh(prev_tag_size);

    			// /!\ taille à verif 
    			//modif previous tag size + ecriture
    			if (nb_block == infos->host.file_info.flv.nb_video_tag-1)
					prev_tag_size += reste + data_per_vtag; //cas particulier dernier tag
            	else 
					prev_tag_size += data_per_vtag;
    			prev_tag_size = htobe32(prev_tag_size);
    			fwrite(&prev_tag_size,sizeof(uint32_t),1,infos->res);
    			cpt_video_tag += 1;
			}
        }while(cpt_video_tag < infos->host.file_info.flv.nb_video_tag);
	
	while(fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host)==1)
			fwrite(&byte_cpy,sizeof(uint8_t),1,infos->res);
		
    write_signature(infos);
    free(data);
    return 0;
}

int extract_eoc(info_s * infos)
{
	uint8_t byte_cpy;
    uint32_t data_size;
    uint8_t tag_type; 
    uint32_t cpt_video_tag=0;
	uint32_t nb_block = 0;
	uint32_t data_jump;
	uint32_t write_data;
	assert(infos);
    assert(infos->mode == STEGX_MODE_EXTRACT);
    assert(infos->algo == STEGX_ALGO_EOC);

    uint32_t data_per_vtag=infos->hidden_length/infos->host.file_info.flv.nb_video_tag;
    uint32_t reste=infos->hidden_length%infos->host.file_info.flv.nb_video_tag;
    uint8_t *data;
    uint32_t cursor = 0;

   if (fseek(infos->host.host, 0, SEEK_SET) == -1){
        return perror("Can't do extraction EOC"), 1;
	}

	data = malloc(infos->host.file_info.flv.nb_video_tag * sizeof(uint8_t));
	if (!data)
		return perror("Can't allocate memory Insertion"), 1;
	
	
	for(uint32_t i=0;i<infos->host.file_info.flv.nb_video_tag;i++){
		data[i]=i;
	}
	/* Initialisation de protect data */
   if(infos->host.file_info.flv.nb_video_tag<256){     
		protect_data(data,infos->host.file_info.flv.nb_video_tag,infos->passwd, infos->mode);
	}

		do {

				//saute de header
				fseek(infos->host.host, 13, SEEK_SET);
				cursor = 0;
				while(data[nb_block] != cursor)
					cursor++;
				cpt_video_tag = -1;
				/* Recherche du tag vidéo numéro cursor */
				while(cursor != cpt_video_tag){
					fread(&tag_type, sizeof(uint8_t), 1, infos->host.host);
					if(tag_type == 9)
						cpt_video_tag++;
					fread(&data_size, sizeof(uint32_t), 1, infos->host.host);
					//passage en 24 bits      
					data_size = be32toh(data_size) >> 8;
					/* Si c'est pas le tag recherché, on jump 
					 * les 6 octets après data_size + les data + le previous tag size (4 octets) */ 
					if(cursor != cpt_video_tag)
						fseek(infos->host.host, data_size + 10, SEEK_CUR);
				}
			
			/* Calcul le nombre d'octets à sauter pour arriver avant les données à récupérer */
			if (nb_block == infos->host.file_info.flv.nb_video_tag - 1){
				data_jump = data_size - reste - data_per_vtag + 6; //cas particulier dernier tag
				write_data = reste + data_per_vtag;
			}
			else {
				data_jump = data_size - data_per_vtag + 6;
				write_data = data_per_vtag;
			}
			fseek(infos->host.host, data_jump, SEEK_CUR);
			/* Recopie des données dans le fichhier resultat */
			for(uint32_t i = 0; i < write_data; i++){
				fread(&byte_cpy, sizeof(uint8_t), 1, infos->host.host);
				fwrite(&byte_cpy,sizeof(uint8_t),1,infos->res);
			}
			
			nb_block++;
		}while(nb_block < infos->host.file_info.flv.nb_video_tag);
	free(data);
	return 0;

}
