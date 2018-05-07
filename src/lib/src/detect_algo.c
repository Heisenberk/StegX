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

int fill_algo_method(info_s* infos,uint8_t algo_read){
	// cas algo EOF
	if(algo_read==BYTE_EOF_WITH_PASSWD){
		infos->algo=STEGX_ALGO_EOF;
		infos->method=STEGX_WITH_PASSWD;
		return 0;
	}
	else if(algo_read==BYTE_EOF_WITHOUT_PASSWD){
		infos->algo=STEGX_ALGO_EOF;
		infos->method=STEGX_WITHOUT_PASSWD;
		return 0;
	}
	// cas algo LSB
	else if(algo_read==BYTE_LSB_WITH_PASSWD){
		infos->algo=STEGX_ALGO_LSB;
		infos->method=STEGX_WITH_PASSWD;
		return 0;
	}
	else if(algo_read==BYTE_LSB_WITHOUT_PASSWD){
		infos->algo=STEGX_ALGO_LSB;
		infos->method=STEGX_WITHOUT_PASSWD;
		return 0;
	}
	// cas algo METADATA
	else if(algo_read==BYTE_METADATA_WITH_PASSWD){
		infos->algo=STEGX_ALGO_METADATA;
		infos->method=STEGX_WITH_PASSWD;
		return 0;
	}
	else if(algo_read==BYTE_METADATA_WITHOUT_PASSWD){
		infos->algo=STEGX_ALGO_METADATA;
		infos->method=STEGX_WITHOUT_PASSWD;
		return 0;
	}
	// cas algo EOC
	else if(algo_read==BYTE_EOC_WITH_PASSWD){
		infos->algo=STEGX_ALGO_EOC;
		infos->method=STEGX_WITH_PASSWD;
		return 0;
	}
	else if(algo_read==BYTE_EOC_WITHOUT_PASSWD){
		infos->algo=STEGX_ALGO_EOC;
		infos->method=STEGX_WITHOUT_PASSWD;
		return 0;
	}
	// cas algo JUNK CHUNK
	else if(algo_read==BYTE_JUNK_CHUNK_WITH_PASSWD){
		infos->algo=STEGX_ALGO_JUNK_CHUNK;
		infos->method=STEGX_WITH_PASSWD;
		return 0;
	}
	else if(algo_read==BYTE_JUNK_CHUNK_WITHOUT_PASSWD){
		infos->algo=STEGX_ALGO_JUNK_CHUNK;
		infos->method=STEGX_WITHOUT_PASSWD;
		return 0;
	}
	else return 1;
}

int read_signature(info_s* infos){
	assert(infos->host.host);
    assert(infos->mode == STEGX_MODE_EXTRACT);
    
	uint8_t algo_read,car_read;
	uint32_t hidden_length,hidden_length_read;
	uint8_t length_name_hidden;
	int read,length_passwd_default;
	int ii,jj;
	// faire ca pour chaque format /!\ --> a faire pour WAV,MP3, AVI, FLV 
	// on va a la signature
	if((infos->host.type==BMP_COMPRESSED)||(infos->host.type==BMP_UNCOMPRESSED)){
		fseek(infos->host.host,infos->host.file_info.bmp.header_size+infos->host.file_info.bmp.data_size,SEEK_SET);
	}
	
	/*
	on lit l'octet représentant l'algorithme utilisé et la méthode 
	utilisée (avec ou sans mdp choisi par l'utilisateur)
	*/
	read=fread(&algo_read, sizeof(uint8_t), 1, infos->host.host);
	fill_algo_method(infos,algo_read);
	printf("ALGO DETECTE: %d\n",infos->algo);
	printf("METHODE DETECTEE: %d\n",infos->method);
	
	// on lit la taille du fichier caché
	read=fread(&hidden_length_read, sizeof(uint32_t), 1, infos->host.host);
	// convertit read_length_pic de big-endian en l'endian de la machine
	hidden_length=be32toh(hidden_length_read);
	printf("TAILLE DU FICHIER CACHE : %d,%x\n",hidden_length,hidden_length);
	
	// on lit la taille du nom du fichier caché
	read=fread(&length_name_hidden, sizeof(uint8_t), 1, infos->host.host);
	printf("TAILLE DU NOM DU FICHIER CACHE : %d\n",length_name_hidden);
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
		fseek(infos->host.host,length_name_hidden,SEEK_CUR);
		for(ii=0;ii<(LENGTH_DEFAULT_PASSWD+1);ii++){
			read=fread(&car_read, sizeof(uint8_t), 1, infos->host.host);
			infos->passwd[ii]=car_read;
		}
		infos->passwd[LENGTH_DEFAULT_PASSWD]='\0';
		printf("PASSWD : \"%s\"\n",infos->passwd);
		
		// on va au niveau du nom du fichier pour pouvoir le lire dans la signature
		fseek(infos->host.host,-(LENGTH_DEFAULT_PASSWD+length_name_hidden+1),SEEK_CUR);
	}
	
	/*
	lecture du nom du fichier caché XOR avec le mot de passe 
	(choisi par l'utilisateur ou par l'application aléatoirement)
	*/
	ii=0;jj=0;
	while(ii<length_name_hidden){
		read=fread(&car_read, sizeof(uint8_t), 1, infos->host.host);
		infos->hidden_name[ii]=car_read^infos->passwd[jj]; //XOR
		ii++; jj++;
		if(infos->passwd[jj]=='\0') jj=0;
	}
	infos->hidden_name[length_name_hidden]='\0';
	printf("NOM DU FICHIER DETECTE : %s\n",infos->hidden_name);
		
	return 0;
}

// remplit host.file_info, hidden_length, algo, hidden_name, method
int stegx_detect_algo(info_s* infos){
	if (infos->mode == STEGX_MODE_INSERT) {
        stegx_errno = ERR_DETECT_ALGOS;
        return 1;
    }
	int fill=fill_host_info(infos);
	if(fill==1){
		stegx_errno = ERR_DETECT_ALGOS;
		return 1;
	}
	int read=read_signature(infos);
	if(read==1) return 1;
	
	return 0;
}
