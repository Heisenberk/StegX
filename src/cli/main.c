#include <stdio.h>
#include <stdlib.h>

#include "stegx.h"
#include "stegx_common.h"
#include "commandes/cli.h"

int main(int argc, char *argv[])
{
    stegx_choices_s *com = init_stegx_info();
    fill_info(com, argc, argv);
    check_info(com);
    info_s *infos = stegx_init(com);

    int compatibility = stegx_check_compatibility(infos);
    if (compatibility == 1) {
        printf("ERREUR COMPATIBILITY");
        //erreur
    }

    stegx_clear(infos);
    dest_stegx_info(com);

    return 1;
}
