#include "tools.h"

void sort_word(Words* words)
{
    qsort(words->word, words->index, sizeof(Word), compare_word);
}

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
