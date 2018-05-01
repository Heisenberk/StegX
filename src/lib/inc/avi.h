#ifndef AVI_H
#define AVI_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "typesteg.h"
#include "wav.h" //necessaire la localisation de la signature RIFF

#define SIG_AVI 0x41564920
#define ADDRESS_SIG_AVI 8

struct avi{
	
};
typedef struct avi avi_s;

type_e stegx_test_file_avi(FILE* file);


#endif
