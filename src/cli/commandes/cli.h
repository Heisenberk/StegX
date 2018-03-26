#ifndef CLI_H
#define CLI_H

#define ALGO_LSB 1
#define ALGO_METADATA 2
#define ALGO_EOF 3

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
