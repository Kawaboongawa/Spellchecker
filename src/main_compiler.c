/**
 * \file main_compiler.c
 * \brief Entry point to generate the binary TextMiningCompiler.
 * \author lugand_j, cetre_c
 * \version 0.1
 * \date 29 juillet 2017
 */


#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "trie.h"
#include "tools.h"


int main(int argc, char *argv[])
{
  if (argc == 2 && strcmp(argv[1], "--export") == 0)
  {
    export_test();
    return 0;
  }

  if (argc < 3)
  {
    printf("Usage: ./ref/osx/TextMiningCompiler /path/to/word/freq.txt /path/to/output/dict.bin\n");
    exit(1);
  }

  char *dict = argv[1];
  char *bin = argv[2];

  TrieRadix *t = malloc(sizeof(TrieRadix));
  t->nb_children = 0;
  t->nb_nodes = 0;
  t->children = NULL;

  char *file = load_trie(dict);
  uint32_t max_freq = 0;

  char *token, *str, *tofree;
  tofree = str = strdup(file);
  if (!str)
  {
    fprintf(stderr, "Error could not strdup.\n");
    exit(1);
  }

  // Parsing the file
  while ((token = strsep(&str, "\n")) != NULL)
  {
    char *token2, *str2, *tofree2;
    tofree2 = str2 = strdup(token);
    if (!str2)
    {
      fprintf(stderr, "Error could not strdup.\n");
      exit(1);
    }

    int i = 0;
    char *tmp_tok = NULL;
    while ((token2 = strsep(&str2, "\t")) != NULL)
    {
      if (i % 2 == 0) {
        tmp_tok = token2;
      } else {
        char *ptr;
        unsigned long int freq = strtoul(token2, &ptr, 10);
        if (freq > max_freq) max_freq = (uint32_t)freq;
        add_word_trie(t, tmp_tok, (uint32_t)freq);
      }
      i++;
    }
    free(tofree2);
  }
  free(tofree);
  free(file);

  compress_trie(t);
  binarize_trie(t, bin);

  if (argc == 5 && strcmp(argv[3], "--graph") == 0)
  {
    print_trie(t, atoi(argv[4]));
  }
  else if (argc == 4 && strcmp(argv[3], "--test") == 0)
  {
    TrieRadix* loaded = load_binarize_trie(bin);
    test(loaded);
    release_trie(loaded);
  }

  release_trie(t);

  return 0;
}
