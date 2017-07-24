#include <stdio.h>

#include "levenshtein.h"
#include "tools.h"

int main()
{
    char* s1 = "coucou";
    char* s2 = "coucuo";
    printf("%d\n", levenshtein(s1, s2));

    Word l[3] = {{.word = "blu", .freq = 52, .dist = 12},
                 {.word = "bleu", .freq = 40, .dist = 42},
                 {.word = "ble", .freq = 1, .dist = 3}};
    print_json(l, 3);
}
