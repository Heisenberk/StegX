#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "../types.h"
#include "commandes.h"

/**
 * \fn void commande_dissimulation_sans_mdp(int num,char** chaineCarac)
 * \brief Fonction qui fait la dissimulation sans mot de passe sur l'interface
 * en ligne de commande.
 * 
 * \param num nombre de parametres dans les arguments du main.
 * \param chaineCarac chaine de chaines de caracteres representant les 
 * parametres dans les arguments du main.
 */
void commande_dissimulation_sans_mdp(int num,char** chaineCarac){
	//ecrire le code dintegration avec la librairie
	//ecrire un message en fonction de la reussite ou non de la commande
}

/**
 * \fn void commande_dissimulation_avec_mdp(int num,char** chaineCarac)
 * \brief Fonction qui fait la dissimulation sans mot de passe sur l'interface
 * en ligne de commande.
 * 
 * \param num nombre de parametres dans les arguments du main.
 * \param chaineCarac chaine de chaines de caracteres representant les 
 * parametres dans les arguments du main.
 */
void commande_dissimulation_avec_mdp(int num,char** chaineCarac){
	//ecrire le code dintegration avec la librairie
	//ecrire un message en fonction de la reussite ou non de la commande
}

/**
 * \fn void commande_extraction_sans_mdp(int num,char** chaineCarac)
 * \brief Fonction qui fait la dissimulation sans mot de passe sur l'interface
 * en ligne de commande.
 * 
 * \param num nombre de parametres dans les arguments du main.
 * \param chaineCarac chaine de chaines de caracteres representant les 
 * parametres dans les arguments du main.
 */
void commande_extraction_sans_mdp(int num,char** chaineCarac){
	//ecrire le code dintegration avec la librairie
	//ecrire un message en fonction de la reussite ou non de la commande
}

/**
 * \fn void commande_extraction_avec_mdp(int num,char** chaineCarac)
 * \brief Fonction qui fait la dissimulation sans mot de passe sur l'interface
 * en ligne de commande.
 * 
 * \param num nombre de parametres dans les arguments du main.
 * \param chaineCarac chaine de chaines de caracteres representant les 
 * parametres dans les arguments du main.
 */
void commande_extraction_avec_mdp(int num,char** chaineCarac){
	//ecrire le code dintegration avec la librairie
	//ecrire un message en fonction de la reussite ou non de la commande
}

/**
 * \fn void affiche_presentation_stegx()
 * \brief Fonction qui presente l'application stegx.
 */
void affiche_presentation_stegx(){
	//ecrire un message pr presenter stegx
	printf("presnetation stegx");
}

/**
 * \fn void affiche_presentation_stegx()
 * \brief Fonction qui presente les commandes possibles de stegx.
 */
void affiche_aide_stegx(){
	printf("aide");
}

/**
 * \fn void affiche_message_fichier_illisible()
 * \brief Fonction qui previent que un ou plusieurs fichiers en entree sont
 * illisibles.
 */
void affiche_message_fichier_illisible(){
	printf("\033[01mFichier(s) en entrée choisi(s) par l'utilisateur non reconnu par StegX. ");
	printf("Veuillez réessayer avec des chemins fichiers corrects. \n");
	printf("Le fichier à cacher et le fichier hote (pour la dissimulation) et ");
	printf("le fichier à analyser (pour l'extraction) doivent exister. \n\n\033[0m");
}

/**
 * \fn void affiche_message_mode_non_reconnu()
 * \brief Fonction qui affiche le message de rappel des commandes si la 
 * commande n'a pas ete reconnu.
 */
void affiche_message_mode_non_reconnu(){
	printf("\033[01mMode choisi par l'utilisateur non reconnu par StegX. ");
	printf("Veuillez réessayer selon les commandes suivantes : \n\n\033[0m");
	printf("Si vous voulez dissimuler des données dans des fichiers de format BMP, PNG, WAV, MP3, FLV ou AVI : \n");
	printf("\033[01m\033[31mstegx -dissimulation/-d [chemin cache] [chemin hote] [-lsb/-eof/-meta] [chemin resultat] \n\033[0m");
	printf("\033[01m\033[31mstegx -dissimulation/-d [chemin cache] [chemin hote] [-lsb/-eof/-meta] [chemin resultat] -mdp [mdp choisi]\n\n\033[0m");
	printf("Si vous voulez extraire des données cachées dans un fichier contenant des données cachées : \n");
	printf("\033[01m\033[31mstegx -extraction/-e [chemin analyse] [chemin resultat]\n\033[0m");
	printf("\033[01m\033[31mstegx -extraction/-e [chemin analyse] [chemin resultat] -mdp [mdp choisi] \n\n\033[0m");
}

/**
 * \fn int teste_commande_quatre_arguments(int num, char** chaineCarac)
 * \brief Fonction qui teste quel mode l'utilisateur a choisi avec 4 arguments.
 * 
 * \param num nombre de parametres dans les arguments du main.
 * \param chaineCarac chaine de chaines de caracteres representant les 
 * parametres dans les arguments du main.
 * \return DEMANDE_AIDE si l'utilisateur ne sait pas comment utiliser l'application en ligne de commande,  
 * MODE_NON_RECONNU si la commande n'est pas reconnu.
 */
int teste_commande_deux_arguments(int num, char** chaineCarac){
	if((strcmp(chaineCarac[1],"-help")==0)||(strcmp(chaineCarac[1],"-h")==0)){
		return DEMANDE_AIDE;
	}
	return MODE_NON_RECONNU;
}

/**
 * \fn int teste_commande_quatre_arguments(int num, char** chaineCarac)
 * \brief Fonction qui teste quel mode l'utilisateur a choisi avec 4 arguments.
 * 
 * \param num nombre de parametres dans les arguments du main.
 * \param chaineCarac chaine de chaines de caracteres representant les 
 * parametres dans les arguments du main.
 * \return MODE_EXTRACTION_SANS_MDP si l'utilisateur veut extraire des donnees cachees sans mot de passe, 
 * MODE_NON_RECONNU si la commande n'est pas reconnu, FICHIERS_ILLISIBLES si le fichier a analyser ne peut pas
 * etre lu.
 */
int teste_commande_quatre_arguments(int num, char** chaineCarac){
	 //si le deuxieme argument est "-extraction"
	if((strcmp(chaineCarac[1],"-extraction")==0)||(strcmp(chaineCarac[1],"-e")==0)){
		int test_lecture_analyse;
		test_lecture_analyse=access(chaineCarac[2],F_OK|R_OK);
		if(test_lecture_analyse==0){
			return MODE_EXTRACTION_SANS_MDP;
		}
		else{
			return FICHIERS_ILLISIBLES;
		}
	}
	return MODE_NON_RECONNU;
}

/**
 * \fn int teste_commande_six_arguments(int num,char** chaineCarac)
 * \brief Fonction qui teste quel mode l'utilisateur a choisi avec 6 arguments.
 * 
 * \param num nombre de parametres dans les arguments du main.
 * \param chaineCarac chaine de chaines de caracteres representant les 
 * parametres dans les arguments du main.
 * \return MODE_DISSIMULATION_SANS_MDP si l'utilisateur veut cacher des donnees sans mot de passe, 
 * MODE_EXTRACTION_AVEC_MDP si l'utilisateur veut extraire des donnees cachees avec mot de passe, 
 * MODE_NON_RECONNU si la commande n'est pas reconnu, FICHIERS_ILLISIBLES si les fichiers a lire en entree
 * ne peuvent pas etre lus.
 */
int teste_commande_six_arguments(int num,char** chaineCarac){
	//si le deuxieme argument est "-dissimulation"
	if((strcmp(chaineCarac[1],"-dissimulation")==0)||(strcmp(chaineCarac[1],"-d")==0)){ 
		//si il a choisi parmi les 3 algos
		if((strcmp(chaineCarac[4],"-lsb")==0)||(strcmp(chaineCarac[4],"-meta")==0)||(strcmp(chaineCarac[4],"-eof")==0)){
			int test_lecture_cache, test_lecture_hote;
			test_lecture_cache=access(chaineCarac[2],F_OK|R_OK);
			test_lecture_hote=access(chaineCarac[3],F_OK|R_OK);
			if((test_lecture_cache==0)&&(test_lecture_hote==0)){
				return MODE_DISSIMULATION_SANS_MDP;
			}
			else return FICHIERS_ILLISIBLES;
		}
	}
	else if((strcmp(chaineCarac[1],"-extraction")==0)||(strcmp(chaineCarac[1],"-e")==0)){
		if(strcmp(chaineCarac[4],"-mdp")==0){
			int test_lecture_analyse;
			test_lecture_analyse=access(chaineCarac[2],F_OK|R_OK);
			if(test_lecture_analyse==0){
				return MODE_EXTRACTION_AVEC_MDP;
			}
			else{
				return FICHIERS_ILLISIBLES;
			}
		}
	}
	return MODE_NON_RECONNU;
}

/**
 * \fn int teste_commande_huit_arguments(int num, char** chaineCarac)
 * \brief Fonction qui teste quel mode l'utilisateur a choisi avec 8 arguments.
 * 
 * \param num nombre de parametres dans les arguments du main.
 * \param chaineCarac chaine de chaines de caracteres representant les 
 * parametres dans les arguments du main.
 * \return MODE_EXTRACTION si l'utilisateur veut extraire des donnees cachees, 
 * MODE_NON_RECONNU si la commande n'est pas reconnu ou que les fichiers 
 * ne peuvent pas etre lus.
 */
int teste_commande_huit_arguments(int num, char** chaineCarac){
	//si le deuxieme argument est "-dissimulation"
	if((strcmp(chaineCarac[1],"-dissimulation")==0)||(strcmp(chaineCarac[1],"-d")==0)){ 
		//si il a choisi parmi les 3 algos
		if((strcmp(chaineCarac[4],"-lsb")==0)||(strcmp(chaineCarac[4],"-meta")==0)||(strcmp(chaineCarac[4],"-eof")==0)){
			if(strcmp(chaineCarac[6],"-mdp")==0){ //si il a choisi de mettre un mdp
				int test_lecture_cache, test_lecture_hote;
				test_lecture_cache=access(chaineCarac[2],F_OK|R_OK);
				test_lecture_hote=access(chaineCarac[3],F_OK|R_OK);
				if((test_lecture_cache==0)&&(test_lecture_hote==0)){
					return MODE_DISSIMULATION_AVEC_MDP;
				}
				else return FICHIERS_ILLISIBLES;
			}
		}
	}
	return MODE_NON_RECONNU;
}

/**
 * \fn int teste_commande_generale(int num,char** chaineCarac)
 * \brief Fonction qui renvoie le mode choisi par l'utilisateur.
 * 
 * \param num nombre de parametres dans les arguments du main.
 * \param chaineCarac chaine de chaines de caracteres representant les 
 * parametres dans les arguments du main.
 * \return MODE_DISSIMULATION si l'utilisateur veut cacher des donnees, 
 * MODE_EXTRACTION si il veut extraire des donnees cachees, 
 * MODE_NON_RECONNU si la commande n'est pas reconnu.
 */
int teste_commande_generale(int num,char** chaineCarac){
	if(num==1){
		return PRESENTATION_STEGX;
	}
	else if(num==2){
		return teste_commande_deux_arguments(num,chaineCarac);
	}
	// ./stegx -dissimulation [chemin cache] [chemin hote] [-lsb/-eof/-meta] [chemin resultat]
	// ./stegx -extraction [chemin analyse] [chemin resultat] -mdp [mdp choisi]
	else if(num==6){
		return teste_commande_six_arguments(num,chaineCarac);
	}
	// ./stegx -extraction [chemin analyse] [chemin resultat]
	else if(num==4){
		return teste_commande_quatre_arguments(num,chaineCarac);
	}
	// ./stegx -dissimulation [chemin cache] [chemin hote] [-lsb/-eof/-meta] [chemin resultat] -mdp [mdp choisi]
	else if(num==8){
		return teste_commande_huit_arguments(num,chaineCarac);
	}
	return MODE_NON_RECONNU;
}

/**
 * \fn void realise_commande_generale(int num,char** chaineCarac,int mode)
 * \brief Fonction qui realise les actions choisies par l'utilisateur.
 * 
 * \param num nombre de parametres dans les arguments du main.
 * \param chaineCarac chaine de chaines de caracteres representant les 
 * parametres dans les arguments du main.
 * \param mode choix de l'utilisateur de dissimuler ou extraire
 */
void realise_commande_generale(int num,char** chaineCarac,int mode){
	if(mode==PRESENTATION_STEGX){
		affiche_presentation_stegx();
	}
	else if(mode==DEMANDE_AIDE){
		affiche_aide_stegx();
	}
	else if(mode==MODE_DISSIMULATION_SANS_MDP){
		commande_dissimulation_sans_mdp(num,chaineCarac);
	}
	else if(mode==MODE_DISSIMULATION_AVEC_MDP){
		commande_dissimulation_avec_mdp(num,chaineCarac);
	}
	else if(mode==MODE_EXTRACTION_SANS_MDP){
		commande_extraction_sans_mdp(num,chaineCarac);
	}
	else if(mode==MODE_EXTRACTION_AVEC_MDP){
		commande_extraction_avec_mdp(num,chaineCarac);
	}
	else if(mode==FICHIERS_ILLISIBLES){
		affiche_message_fichier_illisible();
	}
	else{ //si la commande n'est pas reconnu par l'application
		affiche_message_mode_non_reconnu();
	}
}
