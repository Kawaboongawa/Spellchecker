#include "tools.h"

void sort_word(Words* words)
{
    qsort(words->word, words->index, sizeof(Word), compare_word);
}

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
int compare_word(const void* w1, const void* w2)
{
    if ((((Word*) w1)->dist > ((Word*) w2)->dist)
        || (((Word*) w1)->dist == ((Word*) w2)->dist
            && ((Word*) w1)->freq < ((Word*) w2)->freq)
        || (((Word*) w1)->dist == ((Word*) w2)->dist
            && ((Word*) w1)->freq == ((Word*) w2)->freq
            && strcmp(((Word*) w1)->word, ((Word*) w2)->word) > 0))
        return 1;
    return -1;
}

void print_json(Words* words)
{
    printf("[");
    for (uint i = 0; i < words->index; i++)
    {
        printf("{\"word\":\"%s\",\"freq\":%d,"
               "\"distance\":%d}", words->word[i].word,
               words->word[i].freq, words->word[i].dist);
        if (i < words->index - 1)
            printf(",");
    }
    printf("]\n");
}

inline int min3 (int a, int b, int c)
{
  __asm__ (
           "cmp     %0, %1\n\t"
           "cmovle  %1, %0\n\t"
           "cmp     %0, %2\n\t"
           "cmovle  %2, %0\n\t"
          : "+r"(a) :
            "%r"(b), "r"(c)
          );
  return a;
}
