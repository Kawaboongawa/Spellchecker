#include "levenshtein.h"

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

void levenshtein(char *s1, char *s2, uint len1,
                 uint len2, uint matrix[][len2])
{
    // uint len1 = strlen(s1); //x
    // uint len2 = strlen(s2); //y
    // uint matrix[len2 + 1][len1 + 1];

    for (uint x = 0; x <= len1; ++x)
        matrix[0][x] = x;

    for (uint y = 1; y <= len2; ++y)
        matrix[y][0] = y;

    for (uint y = 1; y <= len2; y++)
        for (uint x = 1; x <= len1; x++)
        {
            int tmp = (s1[x - 1] == s2[y - 1] ? 0 : 1);
            matrix[y][x] = MIN3(matrix[y - 1][x] + 1,
                                matrix[y][x - 1] + 1,
                                matrix[y - 1][x - 1] + tmp);
            if (y > 1 && x > 1
                && s1[x - 1] == s2[y - 2]
                && s1[x - 2] == s2[y - 1]
                && matrix[y - 2][x - 2] + tmp < matrix[y][x])
                matrix[y][x] = matrix[y - 2][x - 2] + tmp;
        }


    for (uint y = 0; y <= len2; y++)
    {
        for (uint x = 0; x <= len1; x++)
        {
            printf("%d ", matrix[y][x]);
        }
        printf("\n");
    }
}
