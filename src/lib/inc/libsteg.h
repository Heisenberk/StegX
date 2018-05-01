#ifndef LIBSTEG_H
#define LIBSTEG_H

#include "typesteg.h"
//#include "checkcompa.h" // on ne peut pas linclure car checkcompa en a besoin
#include "bmp.h"
#include "png.h"
#include "wav.h"
#include "mp3.h"
#include "avi.h"
#include "flv.h"

//public
/**
 * @brief Informations du fichier caché. 
 * @details Permet de représenter les informations nécessaires sur le fichier 
 * à cacher, c'est a dire son chemin et l'algorithme que l'on utilisera 
 * pour dissimuler ce dernier.
 */
struct stegx_info_insert {
    char* hidden_path;  /*!< chaine de caracteres representant le nom du fichier a cacher (requis). */
    algo_e algo;        /*!< algorithme qui sera utilise pour dissimuler (requis si CLI). */ 
};
typedef struct stegx_info_insert stegx_info_insert_s;

/**
 * @brief Données choisies par l'utilisateur. 
 * @details Représente les données choisies par l'utilisateur s'il veut 
 * dissimuler ou extraire des données.
 */
struct stegx_choices {
    char* host_path;                  /*!< chaine de caracteres representant le chemin du fichier à analyser (requis). */ 
    char* res_path;                   /*!< chaine de caracteres representant le chemin du fichier résultant (requis). */
    char* passwd;                     /*!< chaine de caracteres representant le mot de passe choisi par l'utilisateur (optionnel). */
    mode_e mode;                      /*!< variable représentant ce que l'utilisateur veut faire, soit une extraction soit une dissimulation (requis). */
    stegx_info_insert_s* insert_info; /*!< pointeur sur la structure stockant les informations sur le fichier à cacher (requis si insertion). */ 
};
typedef struct stegx_choices stegx_choices_s;
	
//privé

struct host_info {
    FILE* host;
    type_e type;
    union {
        struct bmp bmp;
        struct png png;
        struct wav wav;
        struct mp3 mp3;
        struct avi avi;
        struct flv flv;
    } file_info;
};
typedef struct host_info host_info_s;

struct info {
    mode_e mode;                // Requis : INSERT / EXTRACT
    algo_e algo;
    method_e method;
    host_info_s host;           // Requis
    FILE* res;                  // Requis
    FILE* hidden;               // Requis si mode == INSERT
    char* hidden_name;          // Requis (calculé à partir de hidden_path)
    uint32_t hidden_length;     // taille en octets du fichier a a
    char* passwd;               //optionnel    
};
typedef struct info info_s;

//public
info_s* stegx_init(stegx_choices_s* choices);

void stegx_clear(info_s* infos);

#endif
