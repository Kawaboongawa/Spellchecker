#pragma once

#include <string.h>
#include <stdio.h>


typedef unsigned int uint;

typedef struct
{
    char* word;
    int   freq;
    int   dist;
} Word;

void print_json(Word words[], uint len);
