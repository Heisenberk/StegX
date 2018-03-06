#include <stdio.h>
#include <stdlib.h>

#include "libsteg.h"

void hello_libsteg()
{
    printf("Hello libsteg v%d !\n", LIB_VER);
}

int hello_libsteg_v2(int ret)
{
    return ret;
}
