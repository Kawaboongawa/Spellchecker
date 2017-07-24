#include "levenshtein.h"

static inline int min3(int a, int b, int c)
{
    int res = a;
    if (b < a && b < c)
        res = b;
    if (c < a && c < b)
        res = c;
    return res;
}

int levenshtein(char *s1, char *s2)
{
    uint len1 = strlen(s1); //x
    uint len2 = strlen(s2); //y
    uint matrix[len2 + 1][len1 + 1];

    for (uint x = 0; x <= len1; x++)
        matrix[0][x] = x;
    for (uint y = 1; y <= len2; y++)
        matrix[y][0] = y;
    for (uint y = 1; y <= len2; y++)
        for (uint x = 1; x <= len1; x++)
        {
            int tmp = (s1[x] == s2[y] ? 0 : 1);
            matrix[y][x] = min3(matrix[y - 1][x] + 1,
                                matrix[y][x - 1] + 1,
                                matrix[y - 1][x - 1] + tmp);
            if (y > 1 && x > 1 && s1[x] == s2[y - 1]
                && s1[x - 1] == s2[x]
                && matrix[y - 2][x - 2] + tmp < matrix[y][x])
                matrix[y][x] = matrix[y - 2][x - 2] + tmp;
        }
    return(matrix[len2][len1]);
}
