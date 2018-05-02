#include <stdio.h>
#include <stdlib.h>

#include "stegx.h"
#include "commandes/cli.h"

int main(int argc, char *argv[])
{
    stegx_choices_s *com = init_stegx_info();
    fill_info(com, argc, argv);
    check_info(com);
    info_s *infos = stegx_init(com);

    int compatibility = stegx_check_compatibility(infos);
    if (compatibility == 1) return EXIT_FAILURE;
    
    if(com->mode==STEGX_MODE_INSERT){
		int suggest=stegx_suggest_algo(infos);
		if(suggest==1){
			err_print(ERR_SUGG_ALGOS);
			return EXIT_FAILURE;
		}
	
		// a mettre com->insert_info->algo mettre STEGX_ALGO_EOF par defaut
		int choosen=stegx_choose_algo(infos,STEGX_ALGO_EOF);
	
		//stegx_insert(infos);
	}

    stegx_clear(infos);
    dest_stegx_info(com);

    return EXIT_SUCCESS;
}
