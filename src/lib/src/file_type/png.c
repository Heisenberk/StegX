#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "common.h"
#include "stegx_common.h"
#include "stegx_errors.h"

/** Signature PNG */
#define SIG_PNG 0x0A1A0A0D474E5089

type_e stegx_test_file_png(FILE * file)
{
    assert(file);
    if (fseek(file, 0, SEEK_SET) == -1)
        return UNKNOWN;
    // lecture signature PNG
    uint64_t sig_read;
    if (fread(&sig_read, sizeof(uint64_t), 1, file) != 1)
        return UNKNOWN;
    if (sig_read != SIG_PNG) {
        return UNKNOWN;
    }
    return PNG;
}
