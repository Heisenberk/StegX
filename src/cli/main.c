#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "commandes/cli.h"
#include "checkcompa.h" // a enlever pour n'avoir que libsteg.h

//fonction a enlever
void affiche(info_s* infos,stegx_choices_s* choices){
	
	//MODE
	if(infos->mode==STEGX_MODE_EXTRACT){
		printf("\nMODE EXTRACT\n");
	}
	else if(infos->mode==STEGX_MODE_INSERT) printf("\nMODE INSERT\n");
	else printf("\nMODE NON RECONNU\n");
	
	//METHOD
	if(infos->mode==STEGX_MODE_EXTRACT){
		printf("METHODE NON REMPLIE (REMPLIE DANS Detection algo)\n");
	}
	else if(infos->method==STEGX_WITHOUT_PASSWD){
		printf("METHODE SANS MDP\n");
	}
	else if(infos->method==STEGX_WITH_PASSWD) printf("METHODE AVEC MDP\n");
	else printf("METHODE NN RECONNU\n");
	
	//HOST.HOST
	if(infos->host.host!=NULL){
		printf("OUVERTURE FICHIER HOTE : %s\n",choices->host_path);
		if(infos->host.type==UNKNOWN) printf("TYPE:UNKNOWN\n");
		else if(infos->host.type==BMP_COMPRESSED) printf("TYPE:BMP_COMPRESSED\n");
		else if(infos->host.type==BMP_UNCOMPRESSED) printf("TYPE:BMP_UNCOMPRESSED\n");
		else if(infos->host.type==PNG) printf("TYPE:PNG\n");
		else if(infos->host.type==WAV_PCM) printf("TYPE:WAV-PCM\n");
		else if(infos->host.type==WAV_NO_PCM) printf("TYPE:WAV-NO-PCM\n");
		else if(infos->host.type==MP3) printf("TYPE:MP3\n");
		else if(infos->host.type==FLV) printf("TYPE:FLV\n");
		else if(infos->host.type==AVI_COMPRESSED) printf("TYPE:AVI_COMPRESSED\n");
		else if(infos->host.type==AVI_UNCOMPRESSED) printf("TYPE:AVI_UNCOMPRESSED\n");
		else printf("TYPE:?\n");
	}
	else{
		printf("ECHEC OUVERTURE FICHIER HOTE\n");
	}
	
	//HIDDEN
	if(infos->mode==STEGX_MODE_INSERT){
		if(infos->hidden!=NULL){
			printf("OUVERTURE FICHIER HIDDEN : %s\n",choices->insert_info->hidden_path);
		}
		else{
			printf("ECHEC OUVERTURE FICHIER HIDDEN\n");
		}
	}
	else{
		printf("HIDDEN NULL\n");
	}
	
	//PASSWD
	if(infos->passwd!=NULL){
		printf("PASSWD:%s\n",infos->passwd);
	}
	else printf("PASSWD:(NULL)\n");
	
	//RES
	if(infos->mode==STEGX_MODE_EXTRACT){
		printf("RES:(NULL) (REMPLI DANS Extraction)\n");
	}
	else{
		if(infos->res!=NULL){
			printf("OUVERTURE FICHIER RES : %s\n",choices->res_path);
		}
		else{
			printf("ECHEC OUVERTURE FICHIER RES\n");
		}
	}
	
	//HIDDEN_NAME
	if(infos->mode==STEGX_MODE_EXTRACT){
		printf("HIDDEN_NAME:(NULL) (REMPLI DANS Détection)\n");
	}
	else{
		printf("HIDDEN_NAME:\"%s\"\n",infos->hidden_name);
	}	
}

int main(int argc, char *argv[])
{
	stegx_choices_s* com=init_stegx_info();
	fill_info(com,argc,argv);
	check_info(com);
	info_s* infos=stegx_init(com);
	
	printf("\nINITIALISATION :");
	affiche(infos,com); //a enlever
	printf("\n");
	int compatibility=stegx_check_compatibility(infos);
	if(compatibility==1){
		//erreur
	}
	printf("VERIFICATION : ");
	affiche(infos,com);
	printf("\n");
	
	stegx_clear(infos);
	dest_stegx_info(com);
	
	return 1;
}
