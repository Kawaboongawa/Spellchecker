#include "tools.h"

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
    if (b < a && b < c)
        res = b;
    else if (c < a && c < b)
        res = c;
    return res;
}
