#include "unistd.h"
#include "stdio.h"
#include "getopt.h"
#include "cli.h"

void we_are_stegx(){
  printf("   _____ _            __   __\n");
  printf("  / ____| |           \\ \\ / /\n");
  printf(" | (___ | |_ ___  __ _ \\ V / \n");
  printf("  \\___ \\| __/ _ \\/ _` | > <  \n");
  printf("  ____) | ||  __/ (_| |/ . \\ \n");
  printf(" |_____/ \\__\\___|\\__, /_/ \\_\\\n");
  printf("                  __/ |      \n");
  printf("                 |___/   \n\n");
  printf("StegX - Steganographie & Steganalyse \n");
  printf("Université Versailles Saint Quentin en Yvelines - 2018 \n");
  printf("AYOUB Pierre - BASKEVITCH Claire - BESSAC Tristan - CAUMES Clément - ");
  printf("DELAUNAY Damien - DOUDOUH Yassin\n\n");
  printf("Faire \033[01m\033[31mstegx -help\033[0m ou \033[01m\033[31mstegx -h \033[0m pour un rappel des commandes. \n");
}

void besoin_d_aide(){
	printf("VOILA LES INFO\n");
}

void ligne_non_valide(){
  //quelque chose à afficher +
  besoin_d_aide();
}

void remplir_info(struct info* com,const int argc,char* const* argv){
    int optch;
    extern int opterr;

    char option_court[] = "o:c:r:p:deh"; // correspond au format taper en ligne de commande,  x: signifie qu'un argument est attendu après -x  
                  //o: pour l'option -o suivi du fichier hote
                  //c: pour l'option -c suivi du fichier à cacher 
                  //r: pour l'option -r suivi du fichier resultat
                  //p: pour l'option -p suivi du mot de passe 
                  //a: pour l'option -a suivi de l'algo à utiliser   !!! à voir avec groupe
                  //d pour l'option -d pour signifier la dissimulation
                  //e pour l'option -e pour signifier l'extraction
                  //h pour l'option -h qui affiche l'aide
     const struct option option_long[] = {
        {"hote", 1, NULL, 'o'},
        {"cache", 1, NULL, 'c'},
        {"resultat", 1, NULL, 'r'},
        {"lsb",0, NULL,ALGO_LSB},
        {"metadata",0,NULL,ALGO_METADATA},
        {"EOF",0,NULL, ALGO_EOF},
        {"password", 1, NULL, 'p'},
        {"help",0,NULL,'h'},
        {NULL, 0, NULL, 0}
};
    opterr = 1;
    int optindex = 0;

    while ((optch = getopt_long(argc, argv, option_court, option_long, &optindex)) != -1)
    switch (optch) {
        case 'o':
            com->hote=optarg;
            break;
        case 'c':
            com->cache=optarg;
            break; 
        case 'r':
            com->resultat=optarg;
            break;
       
        case 'd':
            com->d_e=1; 
            break;
        case 'e':
             com->d_e=0;
            break;
        case 'p':
             com->mdp=optarg;
        case ALGO_LSB:
             com->algo=ALGO_LSB;
             break;
        case ALGO_METADATA:
             com->algo=ALGO_METADATA;
             break;           
        case ALGO_EOF:
             com->algo=ALGO_EOF;
             break;
        case 'h':
             com->d_e = 3;
	     break;

};
 
}

void verif_infos(struct info* com){
  if (com->d_e==1){
    if((com->hote!="\0") && (com->cache!="\0") && (com->resultat!="\0") && (com->algo!=-1)){
     // lancement_stegx(com);
     printf("c'est ok\n");
    }
    else{
      ligne_non_valide();
    }  
  }
  else if (com->d_e==0){
    if((com->hote!="\0") && (com->resultat!="\0")){
        //lancement_stegx(com);

     printf("c'est ok\n");
    }
    else{
        ligne_non_valide();
    }

  }
  else if(com->d_e == 3)
	  besoin_d_aide();
  else 
	  ligne_non_valide();
   
}

