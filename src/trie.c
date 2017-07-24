#include "trie.h"

void add_word_node(TrieNode *trie, char *word)
{
  if (!trie || !word || *word == '\0')
  {
    return;
  }

  uint8_t letter = *word;

  if (trie->nb_children == 0)
  {
    trie->children = malloc(sizeof(TrieNode));
    if (!trie->children)
    {
      printf("Error could not malloc.\n");
      exit(1);
    }
    trie->children->letter = letter;
    trie->children->nb_children = 0;
    trie->children->children = NULL;
    trie->nb_children++;
    add_word_node(trie->children, ++word);
    return;
  }

  for (uint8_t i = 0; i < trie->nb_children; i++)
  {
    if (trie->children[i].letter == letter)
    {
      add_word_node(&trie->children[i], ++word);
      return;
    }

    // Not found: let's realloc
    if (i == trie->nb_children - 1)
    {
      trie->nb_children++;
      trie->children = realloc(trie->children, trie->nb_children * sizeof(TrieNode));
      if (!trie->children)
      {
        printf("Error could not realloc.\n");
        exit(1);
      }
      trie->children[trie->nb_children - 1].letter = letter;
      trie->children[trie->nb_children - 1].nb_children = 0;
      trie->children[trie->nb_children - 1].children = NULL;

      add_word_node(&trie->children[trie->nb_children - 1], ++word);
      return;
    }
  }
}

void add_word_trie(Trie *trie, char *word)
{
  if (!trie || !word || *word == '\0')
  {
    return;
  }

  uint8_t letter = *word;

  if (trie->nb_children == 0)
  {
    trie->children = malloc(sizeof(TrieNode));
    if (!trie->children)
    {
      printf("Error could not malloc.\n");
      exit(1);
    }
    trie->children->letter = letter;
    trie->children->nb_children = 0;
    trie->children->children = NULL;
    trie->nb_children++;
    add_word_node(trie->children, ++word);
    return;
  }

  for (uint8_t i = 0; i < trie->nb_children; i++)
  {
    if (trie->children[i].letter == letter)
    {
      add_word_node(&trie->children[i], ++word);
      return;
    }

    // Not found: let's realloc
    if (i == trie->nb_children - 1)
    {
      trie->nb_children++;
      trie->children = realloc(trie->children, trie->nb_children * sizeof(TrieNode));
      if (!trie->children)
      {
        printf("Error could not realloc.\n");
        exit(1);
      }
      trie->children[trie->nb_children - 1].letter = letter;
      trie->children[trie->nb_children - 1].nb_children = 0;
      trie->children[trie->nb_children - 1].children = NULL;

      add_word_node(&trie->children[trie->nb_children - 1], ++word);
      return;
    }
  }
}

void release_node(TrieNode *trie)
{
  for (uint8_t i = 0; i < trie->nb_children; i++)
  {
    release_node(&trie->children[i]);
  }
  free(trie->children);
}

void release_trie(Trie *trie)
{
  for (uint8_t i = 0; i < trie->nb_children; i++)
  {
    release_node(&trie->children[i]);
  }
  free(trie);
}
