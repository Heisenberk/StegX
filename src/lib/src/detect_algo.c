#include <endian.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"
#include "sugg_algo.h"

#include "algo/lsb.h"
#include "algo/eof.h"
#include "algo/metadata.h"
#include "algo/eoc.h"
#include "algo/junk_chunk.h"


/** 
 * @brief Va à l'endroit de la signature dans le fichier et la lit. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si la signature a bien ete lue ; 1 sinon 
 */
static int read_signature(info_s* infos){
	assert(infos);
    assert(infos->mode == STEGX_MODE_EXTRACT);
    
	uint8_t algo_read,car_read;
	uint32_t hidden_length,hidden_length_read;
	uint8_t length_name_hidden;
	int read,length_passwd_default,move;
	int ii,jj;

	// on va a la signature
	// faire ca pour chaque format /!\ --> a faire pour WAV,MP3, AVI, FLV 
	if((infos->host.type==BMP_COMPRESSED)||(infos->host.type==BMP_UNCOMPRESSED)){
		if (fseek(infos->host.host, infos->host.file_info.bmp.header_size+infos->host.file_info.bmp.data_size, SEEK_SET) == -1)
			return 1;
	}
	
	/*
	on lit l'octet représentant l'algorithme utilisé et la méthode 
	utilisée (avec ou sans mdp choisi par l'utilisateur)
	*/
	if (fread(&algo_read, sizeof(uint8_t), 1, infos->host.host) != 1)
        return 1;
	
	// on remplit les champs algo et method de infos
	// cas algo EOF
	if(algo_read==BYTE_EOF_WITH_PASSWD){
		infos->algo=STEGX_ALGO_EOF;
		infos->method=STEGX_WITH_PASSWD;
	}
	else if(algo_read==BYTE_EOF_WITHOUT_PASSWD){
		infos->algo=STEGX_ALGO_EOF;
		infos->method=STEGX_WITHOUT_PASSWD;
	}
	// cas algo LSB
	else if(algo_read==BYTE_LSB_WITH_PASSWD){
		infos->algo=STEGX_ALGO_LSB;
		infos->method=STEGX_WITH_PASSWD;
	}
	else if(algo_read==BYTE_LSB_WITHOUT_PASSWD){
		infos->algo=STEGX_ALGO_LSB;
		infos->method=STEGX_WITHOUT_PASSWD;
	}
	// cas algo METADATA
	else if(algo_read==BYTE_METADATA_WITH_PASSWD){
		infos->algo=STEGX_ALGO_METADATA;
		infos->method=STEGX_WITH_PASSWD;
	}
	else if(algo_read==BYTE_METADATA_WITHOUT_PASSWD){
		infos->algo=STEGX_ALGO_METADATA;
		infos->method=STEGX_WITHOUT_PASSWD;
	}
	// cas algo EOC
	else if(algo_read==BYTE_EOC_WITH_PASSWD){
		infos->algo=STEGX_ALGO_EOC;
		infos->method=STEGX_WITH_PASSWD;
	}
	else if(algo_read==BYTE_EOC_WITHOUT_PASSWD){
		infos->algo=STEGX_ALGO_EOC;
		infos->method=STEGX_WITHOUT_PASSWD;
	}
	// cas algo JUNK CHUNK
	else if(algo_read==BYTE_JUNK_CHUNK_WITH_PASSWD){
		infos->algo=STEGX_ALGO_JUNK_CHUNK;
		infos->method=STEGX_WITH_PASSWD;
	}
	else if(algo_read==BYTE_JUNK_CHUNK_WITHOUT_PASSWD){
		infos->algo=STEGX_ALGO_JUNK_CHUNK;
		infos->method=STEGX_WITHOUT_PASSWD;
	}
	
	// on lit la taille du fichier caché
	if (fread(&hidden_length_read, sizeof(uint32_t), 1, infos->host.host) != 1)
        return 1;
	// convertit read_length_pic de big-endian en l'endian de la machine
	hidden_length=be32toh(hidden_length_read);
	infos->hidden_length=hidden_length;
	
	// on lit la taille du nom du fichier caché
	read=fread(&length_name_hidden, sizeof(uint8_t), 1, infos->host.host);
	if (read == 0)
        return 1;
	infos->hidden_name=malloc((length_name_hidden+1)*sizeof(char));
		
	// si l'emetteur a besoin d'un mdp et que le recepteur n'en a pas fourni 
	if((infos->method==STEGX_WITH_PASSWD)&&(infos->passwd==NULL)){
		stegx_errno=ERR_NEED_PASSWD;
		return 1;
	}
	
	/*
	si l'application a choisi un mot de passe par défaut aléatoirement
	on va le lire afin de pourvoir récupérer le nom du fichier qui 
	qui est XOR avec ce dernier
	*/
	if(infos->method==STEGX_WITHOUT_PASSWD){
		// important car si l'utilisateur tape un mdp alors qu'il nen a pas besoin 
		// il faut vider la memoire et realloue par dessus
		if(infos->passwd!=NULL) free(infos->passwd);
		infos->passwd=malloc((LENGTH_DEFAULT_PASSWD+1)*sizeof(char));
		
		// on lit le mdp ecrit dans la signature
		if (fseek(infos->host.host, length_name_hidden, SEEK_CUR) == -1)
			return 1;
		
		for(ii=0;ii<(LENGTH_DEFAULT_PASSWD+1);ii++){
		    if (fread(&car_read, sizeof(uint8_t), 1, infos->host.host) != 1)
				return 1;
			infos->passwd[ii]=car_read;
		}
		infos->passwd[LENGTH_DEFAULT_PASSWD]='\0';
		printf("PASSWD : \"%s\"\n",infos->passwd);
		
		// on va au niveau du nom du fichier pour pouvoir le lire dans la signature
		if (fseek(infos->host.host, -(LENGTH_DEFAULT_PASSWD+length_name_hidden+1), SEEK_CUR) == -1)
			return 1;
	}
	
	/*
	lecture du nom du fichier caché XOR avec le mot de passe 
	(choisi par l'utilisateur ou par l'application aléatoirement)
	*/
	ii=0;jj=0;
	while(ii<length_name_hidden){
		if (fread(&car_read, sizeof(uint8_t), 1, infos->host.host) != 1)
			return 1;
		infos->hidden_name[ii]=car_read^infos->passwd[jj]; //XOR
		ii++; jj++;
		if(infos->passwd[jj]=='\0') jj=0;
	}
	infos->hidden_name[length_name_hidden]='\0';
	printf("NOM DU FICHIER DETECTE : %s\n",infos->hidden_name);
		
	return 0;
}


int stegx_detect_algo(info_s* infos){
	if (infos->mode == STEGX_MODE_INSERT) {
        stegx_errno = ERR_DETECT_ALGOS;
        return 1;
    }
    // on remplit d'avoir la structure spécifique de infos->host.file_info
	int fill=fill_host_info(infos);
	if(fill==1){
		stegx_errno = ERR_DETECT_ALGOS;
		return 1;
	}
	/*
	on lit la signature pour connaitre l'algorithme, la méthode utilisée
	la taille des donnees cachees, le nom du fichier cache
	*/
	int read=read_signature(infos);
	if(read==1){
		if(stegx_errno==ERR_NEED_PASSWD){ // erreur particuliere
			return 1;
		}
		stegx_errno=ERR_DETECT_ALGOS;
		return 1;
	}
	return 0;
}
