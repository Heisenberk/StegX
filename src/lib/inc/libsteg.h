#ifndef LIBSTEG_H
#define LIBSTEG_H

#include "typesteg.h"
#include "structsteg.h"
#include "checkcompa.h"
#include "bmp.h"
#include "png.h"
#include "wav.h"
#include "mp3.h"
#include "avi.h"
#include "flv.h"

//public
info_s* stegx_init(stegx_choices_s* choices);

void stegx_clear(info_s* infos);

#endif
