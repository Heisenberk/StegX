/**
 * @file sugg_algo.c
 * @brief Proposition des algorithmes.
 * @details Module qui contient les fonctions qui permettent de proposer et
 * vérifier l'algorithme de stéganographie à utiliser.
 */

#include <endian.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

/** Longueur du mot de passe choisi par défaut. */
#define LENGTH_DEFAULT_PASSWD  64 /* 64 caractères sans compter le '\0'. */

/** 
 * @brief Teste si l'on peut utiliser l'algorithme LSB pour la dissimulation. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 Si l'algorithme est proposé, 1 sinon.
 */

static int can_use_lsb(info_s * infos)
{
	assert(infos->host.host);
    // Si le fichier hôte est un fichier BMP non compressé.
    if (infos->host.type == BMP_UNCOMPRESSED) {
        /* 
           Si le nombre de bits utilisés pour coder la couleur de chaque 
           pixel est inférieur ou égal à 8 (soit 256 couleurs), le deuxième 
           en-tête est suivi d’une table des couleurs utilisées dans l’image. 
           LSB non proposé 
         */
        if (infos->host.file_info.bmp.pixel_length <= 8)
            return 1;

        // calcul du nombre d'octets représentant l'image brute
        uint64_t nb_bits_pic =
            ((infos->host.file_info.bmp.pixel_length) * (infos->host.file_info.bmp.pixel_number))/8;
        // calcul du nombre de bits modifiables pour l'algorithme LSB
        nb_bits_pic /= 4;
        
        // si la taille du fichier a cacher est trop importante -> LSB impossible
        if ((infos->hidden_length * 8) > nb_bits_pic) {
            return 1;
        }
        return 0;
    }
    
    // si le fichier hôte est un fichier WAV PCM
    else if (infos->host.type == WAV_PCM) {
        /* 
           calcul du nombre de bits modifiables pour l'algorithme LSB
           on fait -8 car data_size inclut [signature DATA](4 octets) et [taille du chunk DATA](4 octets)
           ([nb doctets data]/[nb de bits par sample])=[nb doctets representant l'audio]
           [nb doctets representant l'audio]*2 -> nb de bits modifiable avec LSB 
         */
        uint64_t nb_bits_audio =
            (((infos->host.file_info.wav.data_size) -
              8) / (infos->host.file_info.wav.chunk_size)) * 2;

        if ((infos->hidden_length * 8) > nb_bits_audio) {
            return 1;
        }
    } 
    
    else return 1;
}
/** 
 * @brief Teste si l'on peut utiliser l'algorithme EOF pour la dissimulation. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si l'algorithme est proposé, 1 sinon.
 */
static int can_use_eof(info_s * infos)
{
    assert(infos);
    // Pour tous les formats proposés par StegX, on propose EOF.
    return !IS_FILE_TYPE(infos->host.type);
}

/** 
 * @brief Teste si l'on peut utiliser l'algorithme Metadata pour la dissimulation. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si l'algorithme est proposé, 1 sinon.
 */
static int can_use_metadata(info_s * infos)
{
    assert(infos);
    // Pas toujours pour BMP car cela depend de la taille. A remplir.
    if ((infos->host.type == BMP_COMPRESSED) || (infos->host.type == BMP_UNCOMPRESSED))
        return 0;
    // Pour tous les formats proposés par StegX, on propose Metadata.
    return !IS_FILE_TYPE(infos->host.type);
}

/** 
 * @brief Teste si l'on peut utiliser l'algorithme EOC pour la dissimulation. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si l'algorithme est proposé, 1 sinon.
 */
static int can_use_eoc(info_s * infos)
{	
    assert(infos);
    // Pour le format FLV, on propose EOC. Pour tous le reste, on ne propose pas EOC.
    if (infos->host.type == FLV)
        return 0;
    else
        return 1;
}

/** 
 * @brief Teste si l'on peut utiliser l'algorithme Junk Chunk pour la dissimulation. 
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si l'algorithme est proposé, 1 sinon.
 */
static int can_use_junk_chunk(info_s * infos)
{
    assert(infos);
    // Pour le format AVI, on propose Junk Chunk. Pour tous le reste, on ne propose pas Junk Chunk.
    if ((infos->host.type == AVI_COMPRESSED) || (infos->host.type == AVI_UNCOMPRESSED))
        return 0;
    else
        return 1;
}

/** 
 * @brief Remplit les informations du fichier hôte. 
 * @details Remplit les informations du fichier hôte en fonction du type de
 * fichier. Effectue la lecture des données pour remplir la structure. 
 * @sideeffect Initialise et rempli le champ \r{info_s.host.file_info}.
 * @param infos Structure représentant les informations concernant la dissimulation.
 * @return 0 si tout se passe bien ; 1 si il y a une erreur détectée dans 
 * la fonction. 
 */
int fill_host_info(info_s * infos)
{
	assert(infos->host.host);
    if (fseek(infos->host.host, 0, SEEK_SET) == -1)
        return 1;
    
    // remplit la structure BMP de infos.host.file_info
    //http://www.mysti2d.net/polynesie2/ETT/C044/31/Steganographie/index.html?Formatbmp.html
    if ((infos->host.type == BMP_COMPRESSED) || (infos->host.type == BMP_UNCOMPRESSED)) {
        uint32_t begin_pic, length_pic, pixel_width, pixel_height;
        uint16_t pixel_length;

        // lecture de la taille totale du fichier
        if (fseek(infos->host.host, BMP_DEF_LENGTH, SEEK_SET) == -1)
			return 1;
		if (fread(&length_pic, sizeof(uint32_t), 1, infos->host.host) != 1)
			return 1;
        length_pic = le32toh(length_pic);

        // lecture de la taille du header (qui correspond au debut de data)
        if (fseek(infos->host.host, BMP_DEF_PIC, SEEK_SET) == -1)
			return 1;
		if (fread(&begin_pic, sizeof(uint32_t), 1, infos->host.host) != 1)
			return 1;
        begin_pic = le32toh(begin_pic);

        infos->host.file_info.bmp.header_size = begin_pic;
        infos->host.file_info.bmp.data_size = length_pic - begin_pic;

        // lecture du nombre de bits par pixel
        if (fseek(infos->host.host, BMP_DEF_PIX_LENGTH, SEEK_SET) == -1)
			return 1;
		if (fread(&pixel_length, sizeof(uint32_t), 1, infos->host.host) != 1)
			return 1;
        pixel_length = le32toh(pixel_length);
        infos->host.file_info.bmp.pixel_length = pixel_length;

        // lecture de la largeur de l'image
        if (fseek(infos->host.host, BMP_DEF_NB_PIXEL, SEEK_SET) == -1)
			return 1;
		if (fread(&pixel_width, sizeof(uint32_t), 1, infos->host.host) != 1)
			return 1;
        pixel_width = le32toh(pixel_width);

        // lecture de la hauteur de l'image
		if (fread(&pixel_height, sizeof(uint32_t), 1, infos->host.host) != 1)
			return 1;
        pixel_height = le32toh(pixel_height);
        infos->host.file_info.bmp.pixel_number = pixel_width * pixel_height;
        return 0;
    }
    
    // remplit la structure BMP de infos.host.file_info
    // http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html
    else if (infos->host.type == PNG) {
        // lecture de la taille du chunk IHDR (header)
        if (fseek(infos->host.host, PNG_DEF_IHDR, SEEK_SET) == -1)
			return 1;
        uint32_t ihdr_length;
        if (fread(&ihdr_length, sizeof(uint32_t), 1, infos->host.host) != 1)
			return 1;
        ihdr_length = be32toh(ihdr_length);        
        infos->host.file_info.png.header_size = PNG_DEF_IHDR + ihdr_length;

        uint64_t file_length = 0;
        uint8_t byte_read_png;
        int read_iend = 0;
        int stop_png = 0;
        if (fseek(infos->host.host, 0, SEEK_SET) == -1)
			return 1;
        // detection du chunk IEND et lecture de la taille de data (jusqu'a IEND)
        while (stop_png == 0) {
	        if (fread(&byte_read_png, sizeof(uint8_t), 1, infos->host.host) != 1)
				stop_png = 1;
            else {
                if (byte_read_png == HEXA_i)
                    read_iend++;
                else if ((byte_read_png == HEXA_e) && (read_iend == 1)) {
                    read_iend++;
                } else if ((byte_read_png == HEXA_n) && (read_iend == 2)) {
                    read_iend++;
                } else if ((byte_read_png == HEXA_d) && (read_iend == 3)) {
                    read_iend++;
                } else
                    read_iend = 0;
                if (read_iend == 4) {
                    file_length = file_length + 4;
                    stop_png = 1;
                }
                file_length++;
            }
        }
        infos->host.file_info.png.data_size = file_length - infos->host.file_info.png.header_size;
        return 0;
    }
    
    // remplit la structure WAV de infos.host.file_info
    // http://soundfile.sapp.org/doc/WaveFormat/
    else if ((infos->host.type == WAV_PCM) || (infos->host.type == WAV_NO_PCM)) {
        uint8_t byte_read_wav;  //lecture de l'octet a chaque iteration
        uint64_t header_length = 0;     // longueur du header
        int stop_wav = 0;       // sort de la boucle quand on a lu les lettres "DATA"
        int read_data = 0;      // compte les lettres "DATA"
        // lecture de la taille du header (jusqu'a DATA)
        while (stop_wav == 0) {
			if (fread(&byte_read_wav, sizeof(uint8_t), 1, infos->host.host) != 1)
				stop_wav=1;
            else {
                if (byte_read_wav == HEXA_D)
                    read_data++;
                else if ((byte_read_wav == HEXA_A) && (read_data == 1)) {
                    read_data++;
                } else if ((byte_read_wav == HEXA_T) && (read_data == 2)) {
                    read_data++;
                } else if ((byte_read_wav == HEXA_A) && (read_data == 3)) {
                    read_data++;
                } else
                    read_data = 0;
                if (read_data == 4) {
                    header_length = header_length - 4;
                    stop_wav = 1;
                }
                header_length++;
            }
        }
        infos->host.file_info.wav.header_size = header_length;

        // lecture de la taille du chunk DATA
        uint64_t data_length;
        if (fseek(infos->host.host, header_length + WAV_DATA_SIZE, SEEK_SET) == -1)
			return 1;
		if (fread(&data_length, sizeof(uint64_t), 1, infos->host.host) != 1)
			return 1;
        data_length = le32toh(data_length);
        infos->host.file_info.wav.data_size = data_length + WAV_SUBCHUNK_LENGTH;

        // lecture du nombre de channels (canaux)
        uint16_t bloc_align;
        uint16_t nb_channels;
        if (fseek(infos->host.host, WAV_NUM_CHANNELS, SEEK_SET) == -1)
			return 1;
		if (fread(&nb_channels, sizeof(uint16_t), 1, infos->host.host) != 1)
			return 1;
        nb_channels = le32toh(nb_channels);

        // lecture du nombre de bloc align 
        if (fseek(infos->host.host, WAV_NB_BLOC_ALIGN, SEEK_SET) == -1)
			return 1;
		if (fread(&bloc_align, sizeof(uint16_t), 1, infos->host.host) != 1)
			return 1;
        bloc_align = le32toh(bloc_align);

        // nb_bits_par_sample=(nb_bloc_align/nb_channels)*8;
        infos->host.file_info.wav.chunk_size = (bloc_align / nb_channels) * 8;
        return 0;
    }
    
    // remplit la structure FLV de infos.host.file_info
    // https://www.adobe.com/content/dam/acom/en/devnet/flv/video_file_format_spec_v10.pdf
    else if (infos->host.type == FLV) {
    	uint8_t check_tags; 
		uint32_t header_size;
		uint8_t tag_type;
		uint32_t data_size;
		uint32_t prev_tag_size;


		infos->host.file_info.flv.nb_video_tag=0;
    	infos->host.file_info.flv.nb_metadata_tag=0;
    	infos->host.file_info.flv.file_size=0;
    	fseek(infos.host.host,4,SEEK_SET);
    
    	//lecture du header
    	fread(&check_tags,sizeof(check_tags),1,infos->host.host);
		fread(&header_size,sizeof(header_size),1,infos->host.host);
    
    	header_size=be32toh(header_size);
    	infos->host.file_info.flv.file_size+=header_size;
    	fseek(infos->host.host,4,SEEK_CUR);
    	infos->host.file_info.flv.file_size+=4;

    	//lecture des tags
    	while(fread(&tag_type,sizeof(tag_type),1,infos->host.host)==1){
	    
	    	if(tag_type==METATAG){infos->host.file_info.flv.nb_metadata_tag+=1;}
	   		else if(tag_type==VIDEO_TAG){nb_video_tag+=1;}
			else if(!(tag_type==AUDIO_TAG || tag_type==SCRIPT_DATA_TAG)){break;}	
	    	fread(&data_size,sizeof(data_size),1,infos->host.host);
	    	//lecture de la taille des data
	  	 	data_size=be32toh(data_size);
	  	 	//passage en 24 bits      
	     	data_size>>=8;
	     	//deplacement jusqu'au prochain previous tag size (data size + 6octets qui comportent d'autres informations non utiles) 
	     	fseek(infos->host.host,data_size+6,SEEK_CUR);
	     	//lecture du previous tag size 
	     	fread(&prev_tag_size,sizeof(prev_tag_size),1,infos->host.host);
		 	prev_tag_size=be32toh(prev_tag_size);
		 	infos->host.file_info.flv.file_size+=prev_tag_size+4;
		}
        return 0;
    }
    
    // pour les structures AVI et MP3 leurs structures sont vides
    else if ((infos->host.type == MP3) || (infos->host.type == AVI_COMPRESSED)
             || (infos->host.type == AVI_UNCOMPRESSED)) return 0;

    else
        return 1;
}

int stegx_suggest_algo(info_s * infos)
{
    /* Test si on est en mode insertion, si oui, remplit la structure
       infos->host.file_info. */
    if (infos->mode == STEGX_MODE_EXTRACT || fill_host_info(infos))
        return stegx_errno = ERR_SUGG_ALGOS, 1;
    
    // Lecture de la taille du fichier à cacher.
    if (fseek(infos->hidden, 0, SEEK_END))
        return stegx_errno = ERR_SUGG_ALGOS, perror("Can't move to the end of hidden file"), 1;
    uint64_t read_hidden_length=ftell(infos->hidden);
    // Précaution overflow.
    if(read_hidden_length>=UINT32_MAX)
        return stegx_errno=ERR_LENGTH_HIDDEN, 1;
    else
        infos->hidden_length = (uint32_t)read_hidden_length;

    /*
       remplissage du tableau stegx_propos_algos pour savoir 
       quels algos sont proposés par l'application en fonction des 
       entrées de l'utilisateur. 
     */
    //stegx_propos_algos = malloc(STEGX_NB_ALGO * sizeof(algo_e));
    for (algo_e i = 0; i < STEGX_NB_ALGO; i++) {
        if (i == STEGX_ALGO_LSB)
            stegx_propos_algos[i] = !can_use_lsb(infos);
        else if (i == STEGX_ALGO_EOF)
            stegx_propos_algos[i] = !can_use_eof(infos);
        else if (i == STEGX_ALGO_METADATA)
            stegx_propos_algos[i] = !can_use_metadata(infos);
        else if (i == STEGX_ALGO_EOC)
            stegx_propos_algos[i] = !can_use_eoc(infos);
        else if (i == STEGX_ALGO_JUNK_CHUNK)
            stegx_propos_algos[i] = !can_use_junk_chunk(infos);
    }
    return 0;
}

int stegx_choose_algo(info_s * infos, algo_e algo_choosen)
{
    /* 
       Si l'utilisateur n'a pas choisi de mot de passe, 
       StegX va en créer un par défaut aléatoirement
     */
    if (infos->method == STEGX_WITHOUT_PASSWD) {
        srand(time(NULL));
        infos->passwd = calloc((LENGTH_DEFAULT_PASSWD+1), sizeof(char));
        // Génération de symboles ASCII >= 32 et <= 126.
        for (int i = 0; i < LENGTH_DEFAULT_PASSWD; i++)
            infos->passwd[i] = 32 + (rand() % 95);
    }

    /* Test que l'algorithme choisis à bien été proposé comme étant possible. Si
     * oui, alors il est sauvegardé. */
    if (stegx_propos_algos[algo_choosen])
        infos->algo = algo_choosen;
    /* Si l'utilisateur ne choisis rien ou un algorithme invalide, alors on
     * choisis EOF par défaut. */
    else
        infos->algo = STEGX_ALGO_EOF;
    return 0;
}
