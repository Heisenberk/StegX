#ifndef AVI_H
#define AVI_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "typesteg.h"
#include "wav.h" //necessaire la localisation de la signature RIFF

#define SIG_AVI_1 0x41
#define SIG_AVI_2 0x56
#define SIG_AVI_3 0x49
#define SIG_AVI_4 0x20
#define ADDRESS_SIG_AVI 8

struct avi{
	
};
typedef struct avi avi_s;

type_e stegx_test_file_avi(FILE* file);


#endif
