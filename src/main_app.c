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
    TrieRadix* trie = load_binarize_trie(argv[1]);

    size_t  size = 0;
    char* buf = NULL;
    getline(&buf, &size, stdin);

    char *str = strdup(buf);
    char *delimiters = " \n";
    int dist = 0;
    char *token = strtok(str, delimiters);

    if (strcmp("approx", token))
        return 2;
    token = strtok(NULL, delimiters);

    //TODO error handling by using strtol
    dist = atoi(token);
    token = strtok(NULL, delimiters);

    if (dist > 0)
    {
      search(trie, token, dist);
    }
    else
    {
      TrieNodeRadix *n = search_trie(trie, token);
      printf("[{\"word\":\"%s\",\"freq\":%d,""\"distance\":0}]\n", token,n->freq);
    }
    free(buf);
    free(str);
    return 0;
}
