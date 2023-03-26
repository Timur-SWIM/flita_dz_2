#include "deblank.h"
char * deblank(char *str){
    char *out = str, *put = str;

    for(; *str != '\0'; ++str)
    {
        if(*str != ' ')
            *put++ = *str;
    }
    *put = '\0';

    return out;
}
