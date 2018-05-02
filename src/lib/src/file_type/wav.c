#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "common.h"
#include "riff.h"

#define SIG_WAVE 0x57415645
#define SIG_PCM 0x0100
#define ADDRESS_WAV_WAVE 8
#define ADDRESS_WAV_PCM 20

type_e stegx_test_file_wav(FILE * file)
{
    if (!file)
        return UNKNOWN;
    fseek(file, 0, SEEK_SET);
    int i;
    int read;
    uint32_t sig_read, sig;
    read = fread(&sig_read, sizeof(uint32_t), 1, file);
    sig = htobe32(sig_read);
    if (sig != SIG_RIFF) {
        return UNKNOWN;
    }

    fseek(file, ADDRESS_WAV_WAVE, SEEK_SET);
    read = fread(&sig_read, sizeof(uint32_t), 1, file);
    sig = htobe32(sig_read);
    if (sig != SIG_WAVE) {
        return UNKNOWN;
    }

    fseek(file, ADDRESS_WAV_PCM, SEEK_SET);
    uint16_t pcm_read;
    uint16_t pcm;
    read = fread(&pcm_read, sizeof(uint16_t), 1, file);
    pcm = htobe16(pcm_read);
    if (pcm == SIG_PCM) {
        return WAV_PCM;
    } else
        return WAV_NO_PCM;
}
