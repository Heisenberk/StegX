#include <stdio.h>
#include <stdlib.h>

#include "maths/test.h"
#include "types.h"
#include "commandes/cli.h"

int main(int argc, char *argv[])
{
	stegx_info_t *com = malloc(sizeof(stegx_info_t));
	com->host_path = "\0";
	com->res_path = "\0";
	com->passwd = "\0";
	we_are_stegx();
	fill_info(com, argc, argv);
	check_info(com);
	if(com->mode == STEGX_MODE_INSERT)
		free(com->ins_info);
	free(com);
	return 0;
}
