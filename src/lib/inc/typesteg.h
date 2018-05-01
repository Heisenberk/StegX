#ifndef TYPESTEG_H
#define TYPESTEG_H

//public  
enum mode {STEGX_MODE_INSERT, STEGX_MODE_EXTRACT};
typedef enum mode mode_e;

enum algo {STEGX_ALGO_LSB, STEGX_ALGO_EOF, STEGX_ALGO_METADATA, 
	STEGX_ALGO_EOC, STEGX_ALGO_JUNK_CHUNK};
typedef enum algo algo_e;

enum method {STEGX_WITHOUT_PASSWD, STEGX_WITH_PASSWD};
typedef enum method method_e;
	
//privé
enum type {BMP_COMPRESSED, BMP_UNCOMPRESSED, PNG, WAV_PCM, WAV_NO_PCM, 
	MP3, AVI_COMPRESSED, AVI_UNCOMPRESSED, FLV, UNKNOWN};
typedef enum type type_e;

#endif
