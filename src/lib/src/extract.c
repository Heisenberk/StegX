#include <endian.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

#include "algo/lsb.h"
#include "algo/eof.h"
#include "algo/metadata.h"
#include "algo/eoc.h"
#include "algo/junk_chunk.h"

int stegx_extract(info_s * infos, char *res_path)
{
    (void) infos; /* Unused. */
    (void) res_path; /* Unused. */
    return 1;
}
