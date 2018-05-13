#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

int insert_junk_chunk(info_s * infos)
{
    (void) infos; /* Unused. */
    return 1;
}

int extract_junk_chunk(info_s * infos)
{
    (void) infos; /* Unused. */
    return 1;
}
