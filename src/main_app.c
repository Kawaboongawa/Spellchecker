/**
 * \file main_compiler.c
 * \brief Entry point to generate the binary TextMiningApp.
 * \author lugand_j, cetre_c
 * \version 0.1
 * \date 29 juillet 2017
 */

#include <stdio.h>
#include <stdlib.h>

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

    Words res = create_words(512);
    String str = create_string(512);

    while (getline(&buf, &size, stdin) != -1)
    {
      char *str2 = strdup(buf);
      char *delimiters = " \n";
      int dist = 0;
      char *token = strtok(str2, delimiters);

      if (strcmp("approx", token))
          return 2;
      token = strtok(NULL, delimiters);

      //TODO error handling by using strtol
      dist = atoi(token);
      token = strtok(NULL, delimiters);

      if (dist > 0)
      {
        search(trie, token, dist, &res, &str);
        res.index = 0;
        str.index = 0;
      }
      else
      {
        TrieNodeRadix *n = search_trie(trie, token);
        printf("[{\"word\":\"%s\",\"freq\":%d,""\"distance\":0}]\n", token, n->freq);
      }
      free(buf);
      free(str2);
      buf = NULL;
    }
    return 0;
}
