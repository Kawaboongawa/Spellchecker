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

void export_test(void)
{
  char *path_0 = "tests/testdir/dist0/test0.txt";
  char *path_1 = "tests/testdir/dist1/test0.txt";
  char *path_2 = "tests/testdir/dist2/test0.txt";

  FILE *file_0;
  FILE *file_1;
  FILE *file_2;
  file_0 = fopen(path_0, "w");
  file_1 = fopen(path_1, "w");
  file_2 = fopen(path_2, "w");
  if (!file_0 || !file_1 || !file_2)
  {
    fprintf(stderr, "Error loading test files\n");
    exit(1);
  }

  printf("==== EXPORT TEST ====\n");
  char *file_str = load_trie("misc/words.txt");

  char *token, *str, *tofree;
  tofree = str = strdup(file_str);
  if (!str)
  {
    fprintf(stderr, "Error could not strdup.\n");
    exit(1);
  }

  int w = 0;
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
        fprintf(file_0, "approx 0 %s\n", tmp_tok);
        if (w % 100 == 0)
          fprintf(file_1, "approx 1 %s\n", tmp_tok);
        if (w % 1000 == 0)
          fprintf(file_2, "approx 2 %s\n", tmp_tok);
      }
      i++;
    }
    free(tofree2);
    w++;
  }
  free(tofree);
  free(file_str);

  fflush(file_0);
  fflush(file_1);
  fflush(file_2);

  fclose(file_0);
  fclose(file_1);
  fclose(file_2);

  printf("==== OK ====\n");
}

void test(TrieRadix *t)
{
  printf("==== TEST ====\n");
  char *file = load_trie("misc/words.txt");

  char *token, *str, *tofree;
  tofree = str = strdup(file);
  if (!str)
  {
    fprintf(stderr, "Error could not strdup.\n");
    exit(1);
  }

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

        TrieNodeRadix* n = search_trie(t, tmp_tok);
        assert(n && n->freq == freq);
      }
      i++;
    }
    free(tofree2);
  }
  free(tofree);
  free(file);
  printf("==== OK ====\n");
}

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

  //TrieRadix* loaded = load_binarize_trie("tree.bin");

  //printf("nb nodes: %u\n", loaded->nb_nodes);

  //test(loaded);

  //print_trie(loaded);
  //release_trie(t);
  //release_trie(loaded);§

  return 0;
}
