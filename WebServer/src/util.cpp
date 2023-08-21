#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void check(bool b,const char* msg)
{
    if(b)
    {
        perror(msg);
        exit(EXIT_FAILURE);
    }
}