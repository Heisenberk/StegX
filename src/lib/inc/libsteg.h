#ifndef LIBSTEG_H
#define LIBSTEG_H

#define LIB_VER 2

void hello_libsteg(void);
int hello_libsteg_v2(int ret);
//public  
enum mode {STEGX_MODE_INSERT, STEGX_MODE_EXTRACT};
typedef enum mode mode_e;

enum algo {STEGX_ALGO_LSB, STEGX_ALGO_EOF, STEGX_ALGO_METADATA};
typedef enum algo algo_e;

struct stegx_info_ins {
    char* hidden_path;  // Requis
    algo_e algo;        // Requis si CLI, NULL si GUI car proposition d'algo
};
typedef struct stegx_info_ins stegx_info_ins_t;

struct stegx_info {
    char* host_path;                        // Requis
    char* res_path;                         // Requis
    char* passwd;                           // Optionnel
    mode_e mode;                            // Requis : INSERT / EXTRACT
    stegx_info_ins_t* ins_info;             // Requis si mode == INSERT
};
typedef struct stegx_info stegx_info_t;

	
//privé
enum type {BMP_COMPRESSED, BMP_UNCOMPRESSED, PNG, WAV_PCM, WAV_NO_PCM, MP3, AVI_COMPRESSED, AVI_UNCOMPRESSED, FLV, UNKNOWN};
typedef enum type type_e;

// Tout est requis
struct host_info {
    FILE* host;
    type_e type;
    union {
        //struct bmp bmp;
        //struct png png;
       // struct wav wav;
       // struct mp3 mp3;
       // struct avi avi;
       // struct flv flv;
    } file_type;
};
typedef struct host_info host_info_s;

struct info {
    mode_e mode;                // Requis : INSERT / EXTRACT
    host_info_s host;           // Requis
    FILE* res;                  // Requis
    FILE* hidden;               // Requis si mode == INSERT
    char* hidden_name;          // Requis (calculé à partir de hidden_path)
    char* passwd;               //optionnal    
};
typedef struct info info_s;



#endif
