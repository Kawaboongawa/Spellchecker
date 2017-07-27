#include "tools.h"

void sort_word(Words* words)
{
    qsort(words->word, words->index, sizeof(Word), compare_word);
}

int compare_word(const void* w1, const void* w2)
{
    return (((Word*) w1)->dist > ((Word*) w2)->dist)
        || (((Word*) w1)->dist == ((Word*) w2)->dist
            && ((Word*) w1)->freq < ((Word*) w2)->freq);
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

inline int min3(int a, int b, int c)
{
    int res = a;
    if (b < a && b <= c)
        res = b;
    else if (c < a && c < b)
        res = c;
    return res;
}
