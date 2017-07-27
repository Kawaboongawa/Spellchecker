#include <stdio.h>
#include <stdlib.h>

#include "levenshtein.h"
#include "tools.h"
#include "word_struct.h"
#include "trie.h"
#include "search.h"
#define BUF_SIZE 128



int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Usage: ./TextMiningApp /path/to/compiled/dict.bin\n");
        printf("Aborted (core dumped)\n");
        return 134;
    }
    //uint matrix[7][2];
    //levenshtein("rlamar", "r", 6, 1, matrix);
    //printf("%d %d % d\n", matrix[5][4], matrix[5][5], matrix[5][6]);
    Trie* trie = load_binarize_trie(argv[1]); 
    /*size_t  size = 0;
    char* buf = NULL;
      getline(&buf, &size, stdin);*/
    char * buf = "approx 0 carala";
    char* str = strdup(buf);
    char* delimiters = " \n";
    int dist = 0;
    char* token = strtok(str, delimiters);
    if (strcmp("approx", token))
        return 2;
        token = strtok(NULL, delimiters);
    //TODO error handling by using strtol
    dist = atoi(token);
    token = strtok(NULL, delimiters);
    search(trie, token, dist);
    //free(buf);
    free(str);
    (void) argv;
}
