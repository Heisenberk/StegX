#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "commandes/cli.h"

int main(int argc, char *argv[])
{
	stegx_choices_s* com=init_stegx_info();
	fill_info(com,argc,argv);
	check_info(com);
	dest_stegx_info(com);
	return 1;
}
