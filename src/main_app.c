#include <stdio.h>
#include <stdlib.h>

#include "levenshtein.h"
#include "tools.h"

#define BUF_SIZE 128



int main(int argc, char** argv)
{
    /*Word l[3] = {{.word = "blu", .freq = 52, .dist = 12},
      {.word = "bleu", .freq = 40, .dist = 42},
      {.word = "ble", .freq = 1, .dist = 3}};
      print_json(l, 3);*/
    argv = argv;
    //printf("%c\n", fgetc(stdin));
    if (argc < 2)
    {
        printf("Usage: ./TextMiningApp /path/to/compiled/dict.bin\n");
        printf("Aborted (core dumped)\n");
        return 134;
    }
    
    size_t  size = 0;
    char* buf = NULL;
    getline(&buf, &size, stdin);
    printf("%s", buf);
    free(buf);
} 


