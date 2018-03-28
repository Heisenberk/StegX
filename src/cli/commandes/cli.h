#ifndef CLI_H
#define CLI_H




void fill_info(stegx_info_t* com, const int arc, char* const* argv);
void we_are_stegx();
void help();
void unvalid_line(); 
void check_info(stegx_info_t* com);



struct info{
	char* hote;
	char* cache;
	char*resultat;
	int algo;
	int d_e;
	char* mdp;
};

void remplir_info(struct info *com, const int arc, char* const* argv);
void we_are_stegx();
void besoin_d_aide();
void ligne_non_valide();
void verif_infos(struct info* com);


#endif
