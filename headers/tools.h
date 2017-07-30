#pragma once


/**
 * \file tools.h
 * \brief Several tools used in various part of the software.
 * \author lugand_j, cetre_c
 * \version 0.1
 * \date 29 juillet 2017
 */



#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "trie.h"


typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;


/*! \brief stucture containing word matching with the request given by the user.
**
** A Word is the basic structure that is used to keep results that
** will be displayed in JSon format later on.
**
** \param word A string containing the word matching the request.
** \param freq the frequence of the word given in the radix tree.
** \param dist the distance of the word compare to the original request.
**/
typedef struct
{
    char *word;
    int   freq;
    int   dist;
} Word;


/*! \brief stucture containing every Word matching the request.
**
** \param word A word pointer containing every word matching the request.
** \param index The current index used to add elts in the structure.
** \param size Number of elements in the structure.
**/
typedef struct
{
    Word *word;
    uint  index;
    uint  size;
} Words;



/*! \brief stucture containing a string.

 **
** This structure is used to keep the word while recursively iterating
** through the radix tree and allow to erase/add characters without
** fearing buffer overflow.
**
** \param str The string contained in the struct.
** \param index The current index used to add elts in the structure.
** \param size Number of elements in the structure.
**/
typedef struct
{
    char *str;
    int   index;
    int   size;
} String;



/*! \brief Sort a Words struct using C qsort implementation.
**
** As requested in the subject, we first sort the words found by
** distance, then by frequence and finally by alphabetical order.
**/
void sort_word(Words* words);


/*!
**  \brief The function used by qsort to sort two Word struct.
**/
int compare_word(const void* w1, const void* w2);


/*!
**  \brief Print a Words struct to the Json format.
**/
void print_json(Words* words);

/*!
**  \brief Export tests files for distance 0, 1 and 2
**         Ratio 1, 1/100, 1/1000.
**/
void export_test(void);

/*!
**  \brief Search all nodes of the dictionary in the constructed Trie
**         to test if all nodes can be reached and have the correct frequency.
**/
void test(TrieRadix *t);
