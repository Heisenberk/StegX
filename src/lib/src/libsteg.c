#include <stdio.h>
#include <stdlib.h>

#include "libsteg.h"

void hello_libsteg()
{
    printf("Hello libsteg v%d !\n", LIB_VER);
}

int hello_libsteg_v2(int ret)
{
    return ret;
}

info_s* stegx_init(stegx_choices_s* choices){
	info_s* s;
	
	s->mode=choices->mode; //OK mode
	
	/*s->host.host=fopen(choices->host_path,"r"); //OK host.host
	if(s->host.host==NULL){
		//erreur
	}
	
	//OK hidden
	if(choices->mode==STEGX_MODE_INSERT){ 
		s->hidden=fopen(choices->insert_info->hidden_path,"r");
		if(s->hidden==NULL){
			//erreur
		}
	}
	else s->hidden=NULL;
	
	
	s->res=NULL;
	
	
	if(choices->passwd!=NULL){
		int count=0;
		while(choices->passwd[count]!='\n'){
			count++;
		}
		if(count==0) {
			//erreur
		}
		s->passwd=malloc(count*sizeof(char));
		int i;
		for(i=0;i<count;i++){
			s->passwd[i]=choices->passwd[i];
		}
		if(choices->mode==STEGX_MODE_INSERT){
			s->method=STEGX_WITH_PASSWD;
		}
	}
	else{
		if(choices->mode==STEGX_MODE_INSERT){
			s->method=STEGX_WITHOUT_PASSWD;
		}
		s->passwd=NULL;
	}*/
	
	
	return s;
}

void stegx_clear(info_s* infos){
	
}
