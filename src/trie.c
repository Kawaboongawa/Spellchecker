#include "trie.h"

void add_word_node(Trie *trie, TrieNode *node, char *word)
{
  if (!trie || !node || !word || *word == '\0')
  {
    return;
  }

  char letter = *word;

  if (node->nb_children == 0)
  {
    node->children = malloc(sizeof(TrieNode));
    if (!node->children)
    {
      printf("Error could not malloc.\n");
      exit(1);
    }
    node->children->letter = letter;
    node->children->nb_children = 0;
    node->children->children = NULL;
    node->nb_children++;
    trie->nb_nodes++;
    add_word_node(trie, node->children, ++word);
    return;
  }

  for (uint8_t i = 0; i < node->nb_children; i++)
  {
    if (node->children[i].letter == letter)
    {
      add_word_node(trie, &node->children[i], ++word);
      return;
    }

    // Not found: let's realloc
    if (i == trie->nb_children - 1)
    {
      node->nb_children++;
      trie->nb_nodes++;
      node->children = realloc(node->children, node->nb_children * sizeof(TrieNode));
      if (!node->children)
      {
        printf("Error could not realloc.\n");
        exit(1);
      }
      node->children[node->nb_children - 1].letter = letter;
      node->children[node->nb_children - 1].nb_children = 0;
      node->children[node->nb_children - 1].children = NULL;

      add_word_node(trie, &node->children[node->nb_children - 1], ++word);
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

  char letter = *word;

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
    trie->nb_nodes++;
    add_word_node(trie, trie->children, ++word);
    return;
  }

  for (uint8_t i = 0; i < trie->nb_children; i++)
  {
    if (trie->children[i].letter == letter)
    {
      add_word_node(trie, &trie->children[i], ++word);
      return;
    }

    // Not found: let's realloc
    if (i == trie->nb_children - 1)
    {
      trie->nb_children++;
      trie->nb_nodes++;
      trie->children = realloc(trie->children, trie->nb_children * sizeof(TrieNode));
      if (!trie->children)
      {
        printf("Error could not realloc.\n");
        exit(1);
      }
      trie->children[trie->nb_children - 1].letter = letter;
      trie->children[trie->nb_children - 1].nb_children = 0;
      trie->children[trie->nb_children - 1].children = NULL;

      add_word_node(trie, &trie->children[trie->nb_children - 1], ++word);
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

char *load_trie(char *path)
{
  FILE *file;
  unsigned long len;
  file = fopen(path, "r");
  if (!file)
  {
    fprintf(stderr, "Error loading file %s\n", path);
    exit(1);
  }
  fseek(file, 0, SEEK_END);
  len = (unsigned long) ftell(file);
  rewind(file);

  char *m = calloc(len + 1, sizeof(char));
  if (!m)
  {
    fprintf(stderr, "Error could not malloc.\n");
    exit(1);
  }

  fread(m, len, 1, file);
  fclose(file);
  return m;
}
