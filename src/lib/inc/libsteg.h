#ifndef LIBSTEG_H
#define LIBSTEG_H

#define LIB_VER 2

#include "bmp.h"
#include "png.h"
#include "wav.h"
#include "mp3.h"
#include "avi.h"
#include "flv.h"

void hello_libsteg(void);
int hello_libsteg_v2(int ret);

//public  
enum mode {STEGX_MODE_INSERT, STEGX_MODE_EXTRACT};
typedef enum mode mode_e;

enum algo {STEGX_ALGO_LSB, STEGX_ALGO_EOF, STEGX_ALGO_METADATA, 
	STEGX_ALGO_EOC, STEGX_ALGO_JUNK_CHUNK};
typedef enum algo algo_e;

enum method {STEGX_WITHOUT_PASSWD, STEGX_WITH_PASSWD};
typedef enum method method_e;

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
enum type {BMP_COMPRESSED, BMP_UNCOMPRESSED, PNG, WAV_PCM, WAV_NO_PCM, 
	MP3, AVI_COMPRESSED, AVI_UNCOMPRESSED, FLV, UNKNOWN};
typedef enum type type_e;

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
    int hidden_length;
    char* passwd;               //optionnel    
};
typedef struct info info_s;

//public
info_s* stegx_init(stegx_choices_s* choices);

void stegx_clear(info_s* infos);



#endif
