#include <stdio.h>
#include <stdlib.h>

#include "maths/test.h"
#include "types.h"
#include "commandes/commandes.h"

int main(int argc, char *argv[])
{
    // determine quelle commande l'utilisateur a choisi.
	int mode=teste_commande_generale(argc,argv);
	
	/* en fonction de la commande choisi, l'application va faire ce que 
	 * l'utilisateur veut faire. 
	 */
	realise_commande_generale(argc,argv,mode);
	
	return 0;
}
