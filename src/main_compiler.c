#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "trie.h"

int main()
{
  Trie *t = malloc(sizeof(Trie));
  t->nb_children = 0;
  t->nb_nodes = 0;
  t->children = NULL;

  const char *file = load_trie("misc/words.txt");

  char *token, *str, *tofree;
  tofree = str = strdup(file);
  while ((token = strsep(&str, "\n")))
  {
    char *token2, *str2, *tofree2;
    tofree2 = str2 = strdup(token);

    int i = 0;
    while ((token2 = strsep(&str2, "\t")))
    {
      if (i % 2 == 0) {
        add_word_trie(t, token2);
        printf("nb nodes: %d\n", t->nb_nodes);
      }
      i++;
    }
    free(tofree2);
  }
  free(tofree);

  release_trie(t);
}
