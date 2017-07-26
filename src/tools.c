#include "tools.h"

void print_json(Word words[], uint len)
{
    printf("[");
    for (uint i = 0; i < len; i++)
    {
        printf("{\"word\":\"%s\",\"freq\":%d,"
               "\"distance\":%d}", words[i].word,
               words[i].freq, words[i].dist);
        if (i < len - 1)
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
