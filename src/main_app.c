#include <stdio.h>

#include "levenshtein.h"

int main()
{
    char* s1 = "coucou";
    char* s2 = "pouou";
    printf("%d\n", levenshtein(s1, s2));
}

