#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "trie.h"

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

  if (argc == 4 && strcmp(argv[3], "--graph") == 0)
  {
    print_trie(t);
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
