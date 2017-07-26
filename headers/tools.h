#pragma once

#include <string.h>
#include <stdio.h>

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;

typedef struct
{
    char* word;
    int   freq;
    int   dist;
} Word;

void print_json(Word words[], uint len);

int min3(int a, int b, int c);
