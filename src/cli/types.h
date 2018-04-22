
#ifndef __TYPES_H
#define __TYPES_H

/**
 * \def si l'utilisateur n'a pas reussi a utiliser correctement l'application.
 */
#define MODE_NON_RECONNU -1

/**
 * \def si l'utilisateur a donne des noms de fichiers illisibles ou inexistants. 
 */
#define FICHIERS_ILLISIBLES -2

/**
 * \def si l'utilisateur ne choisit pas de commandes particulieres. 
 */
#define PRESENTATION_STEGX 0

/**
 * \def si l'utilisateur demande de l'aide pour les commandes sur le terminal.  
 */
#define DEMANDE_AIDE 1

/**
 * \def si l'utilisateur choisit de dissimuler des donnees dans d'autres donnees sans mot de passe.
 */
#define MODE_DISSIMULATION_SANS_MDP 2

/**
 * \def si l'utilisateur choisit de dissimuler des donnees dans d'autres donnees avec mot de passe.
 */
#define MODE_DISSIMULATION_AVEC_MDP 3

/**
 * \def si l'utilisateur choisit d'extraire les donnees cachees d'un fichier sans mot de passe.
 */
#define MODE_EXTRACTION_SANS_MDP 4

/**
 * \def si l'utilisateur choisit d'extraire les donnees cachees d'un fichier avec mot de passe.
 */
#define MODE_EXTRACTION_AVEC_MDP 5

#endif
