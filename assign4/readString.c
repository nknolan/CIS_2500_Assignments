#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structDefn.h"

/* readString.c reads contact string data out of myContactList.db and
returns it to main(), one character at a time. Stops when it reaches a
null character. */

void readString(char *targetString, long start, long end, FILE *fptr)
{
    if(start == 0)
    {
        return;
    }
    else
    {
        fseek(fptr, start, SEEK_SET);
        targetString = malloc(sizeof(char) * (end - start));
        fread(targetString, sizeof(char), end - start, fptr);
    }
    return;
}
