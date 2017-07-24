#include <stdio.h>
#include "trie.h"

int main()
{
  Trie *t = malloc(sizeof(Trie));
  t->nb_children = 0;
  t->children = NULL;

  add_word_trie(t, "coucou");
  add_word_trie(t, "coukou");
  add_word_trie(t, "couqou");

  printf("nb nodes: %d\n", t->nb_nodes);

  release_trie(t);

  printf("%s\n", "Code me, Jeremy!");
}
