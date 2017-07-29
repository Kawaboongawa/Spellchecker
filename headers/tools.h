#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;

typedef struct
{
    char *word;
    int   freq;
    int   dist;
} Word;


typedef struct
{
    Word *word;
    uint  index;
    uint  size;
} Words;

typedef struct
{
    char *str;
    int   index;
    int   size;
} String;


void sort_word(Words* words);

int compare_word(const void* w1, const void* w2);

void print_json(Words* words);
