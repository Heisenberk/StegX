#ifndef __COMMANDES_H
#define __COMMANDES_H

/**
 * \fn void commande_dissimulation_sans_mdp(int num,char** chaineCarac)
 * \brief Fonction qui fait la dissimulation sans mot de passe sur l'interface
 * en ligne de commande.
 * 
 * \param num nombre de parametres dans les arguments du main.
 * \param chaineCarac chaine de chaines de caracteres representant les 
 * parametres dans les arguments du main.
 */
void commande_dissimulation_sans_mdp(int num,char** chaineCarac);

/**
 * \fn void commande_dissimulation_avec_mdp(int num,char** chaineCarac)
 * \brief Fonction qui fait la dissimulation sans mot de passe sur l'interface
 * en ligne de commande.
 * 
 * \param num nombre de parametres dans les arguments du main.
 * \param chaineCarac chaine de chaines de caracteres representant les 
 * parametres dans les arguments du main.
 */
void commande_dissimulation_avec_mdp(int num,char** chaineCarac);

/**
 * \fn void commande_extraction_sans_mdp(int num,char** chaineCarac)
 * \brief Fonction qui fait la dissimulation sans mot de passe sur l'interface
 * en ligne de commande.
 * 
 * \param num nombre de parametres dans les arguments du main.
 * \param chaineCarac chaine de chaines de caracteres representant les 
 * parametres dans les arguments du main.
 */
void commande_extraction_sans_mdp(int num,char** chaineCarac);

/**
 * \fn void commande_extraction_avec_mdp(int num,char** chaineCarac)
 * \brief Fonction qui fait la dissimulation sans mot de passe sur l'interface
 * en ligne de commande.
 * 
 * \param num nombre de parametres dans les arguments du main.
 * \param chaineCarac chaine de chaines de caracteres representant les 
 * parametres dans les arguments du main.
 */
void commande_extraction_avec_mdp(int num,char** chaineCarac);

/**
 * \fn void affiche_presentation_stegx()
 * \brief Fonction qui presente l'application stegx.
 */
void affiche_presentation_stegx();

/**
 * \fn void affiche_presentation_stegx()
 * \brief Fonction qui presente les commandes possibles de stegx.
 */
void affiche_aide_stegx();

/**
 * \fn void affiche_message_fichier_illisible()
 * \brief Fonction qui previent que un ou plusieurs fichiers en entree sont
 * illisibles.
 */
void affiche_message_fichier_illisible();

/**
 * \fn void affiche_message_mode_non_reconnu()
 * \brief Fonction qui affiche le message de rappel des commandes si la 
 * commande n'a pas ete reconnu.
 */
void affiche_message_mode_non_reconnu();

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
int teste_commande_deux_arguments(int num, char** chaineCarac);

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
int teste_commande_quatre_arguments(int num, char** chaineCarac);

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
int teste_commande_six_arguments(int num,char** chaineCarac);
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
int teste_commande_huit_arguments(int num, char** chaineCarac);

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
int teste_commande_generale(int num,char** chaineCarac);

/**
 * \fn void realise_commande_generale(int num,char** chaineCarac,int mode)
 * \brief Fonction qui realise les actions choisies par l'utilisateur.
 * 
 * \param num nombre de parametres dans les arguments du main.
 * \param chaineCarac chaine de chaines de caracteres representant les 
 * parametres dans les arguments du main.
 * \param mode choix de l'utilisateur de dissimuler ou extraire
 */
void realise_commande_generale(int num,char** chaineCarac,int mode);

#endif
