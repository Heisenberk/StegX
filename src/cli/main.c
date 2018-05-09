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
    if (infos == NULL) {
        err_print(stegx_errno);
        return EXIT_FAILURE;
    }

    int compatibility = stegx_check_compatibility(infos);
    if (compatibility == 1) {
        err_print(stegx_errno);
        return EXIT_FAILURE;
    }

    if (com->mode == STEGX_MODE_INSERT) {
        int suggest = stegx_suggest_algo(infos);
        if (suggest == 1) {
            err_print(stegx_errno);
            return EXIT_FAILURE;
        }
        // a mettre com->insert_info->algo mettre STEGX_ALGO_EOF par defaut
        int choosen = stegx_choose_algo(infos,com->insert_info->algo);
        if (choosen == 1) {
			stegx_errno=ERR_READ;
            err_print(stegx_errno);
            return EXIT_FAILURE;
        }

        /*int insert = stegx_insert(infos);
        if (insert == 1) {
            err_print(stegx_errno);
            return EXIT_FAILURE;
        }*/
    }
    
    else if(com->mode==STEGX_MODE_EXTRACT){
		int detect=stegx_detect_algo(infos);
		if(detect==1){
			err_print(stegx_errno);
			return EXIT_FAILURE;
		}
	}
    stegx_clear(infos);
    dest_stegx_info(com);

    return EXIT_SUCCESS;
}
