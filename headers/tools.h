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


typedef struct
{
    Word*  word;
    uint   index;
    uint   size;
} Words;

typedef struct
{
    char* str;
    int   index;
    int   size;
} String;


void print_json(Words* words);

int min3(int a, int b, int c);
