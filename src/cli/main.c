#include <stdio.h>
#include <stdlib.h>

#include "maths/test.h"
#include "types.h"
#include "commandes/cli.h"

int main(int argc, char *argv[])
{
	struct info *com = malloc(sizeof(struct info));
	com->hote = "\0";
	com->cache = "\0";
	com->resultat = "\0";
	com->mdp = "\0";
	com->algo = -1;
	com->d_e = -1;
	we_are_stegx();
	remplir_info(com, argc, argv);
	verif_infos(com);
	return 0;
}
