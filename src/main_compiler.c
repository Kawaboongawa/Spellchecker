#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "trie.h"

int main(void)
{
  Trie *t = malloc(sizeof(Trie));
  t->nb_children = 0;
  t->nb_nodes = 0;
  t->children = NULL;

  char *file = load_trie("misc/words.txt");
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
        if ((uint32_t)atoi(token2) > max_freq) max_freq = (uint32_t)atoi(token2);
        add_word_trie(t, tmp_tok, (uint32_t)atoi(token2));
      }
      i++;
    }
    free(tofree2);
  }
  free(tofree);
  free(file);

  printf("nb nodes: %u\n", t->nb_nodes);
  printf("Max freq: %d\n", max_freq);

  TrieNode* n = search_trie(t, "gilles08");
  printf("freq: %d\n", n->freq);

  binarize_trie(t, "tree.bin");
  printf("\n\n");
  Trie* loaded = load_binarize_trie("tree.bin");

  printf("nb nodes: %u\n", loaded->nb_nodes);
  n = search_trie(loaded, "gilles08");
  printf("freq: %d\n", n->freq);

  release_trie(t);

  return 0;
}
