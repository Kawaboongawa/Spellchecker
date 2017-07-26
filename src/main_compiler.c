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
        add_word_trie(t, tmp_tok, atoi(token2));
      }
      i++;
    }
    free(tofree2);
  }
  free(tofree);
  free(file);

  printf("nb nodes: %u\n", t->nb_nodes);

  TrieNode* n = search_trie(t, "gilles08");
  printf("freq: %d", n->freq);

  release_trie(t);

  return 0;
}
