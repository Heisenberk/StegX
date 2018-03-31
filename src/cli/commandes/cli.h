#ifndef CLI_H
#define CLI_H

#include "libsteg.h"

void fill_info(stegx_info_t* com, const int arc, char* const* argv);
void we_are_stegx();
void help();
void unvalid_line(); 
void check_info(stegx_info_t* com);

#endif
