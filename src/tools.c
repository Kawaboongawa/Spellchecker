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
