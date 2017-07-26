#include "trie.h"

void add_word_node(Trie *trie, TrieNode *node, char *word, uint32_t freq)
{
  if (!trie || !node || !word || *word == '\0')
  {
    return;
  }

  if (node->nb_children == 0)
  {
    assert(node->children == NULL);

    node->children = malloc(sizeof(TrieNode));
    if (!node->children)
    {
      fprintf(stderr, "Error could not malloc.\n");
      exit(1);
    }
    node->children->letter = *word;
    node->children->nb_children = 0;
    node->children->children = NULL;
    node->nb_children++;
    trie->nb_nodes++;
    if (*(word + 1) == '\0')
    {
      node->children->freq = freq;
    } else {
      add_word_node(trie, node->children, ++word, freq);
    }
    return;
  }

  for (uint16_t i = 0; i < node->nb_children; i++)
  {
    if (node->children[i].letter == *word)
    {
      if (*(word + 1) == '\0')
      {
        node->children[i].freq = freq;
      } else {
        add_word_node(trie, &node->children[i], ++word, freq);
      }
      return;
    }

    // Not found: let's realloc
    if (i == (node->nb_children - 1))
    {
      node->nb_children++;
      trie->nb_nodes++;
      node->children = realloc(node->children, node->nb_children * sizeof(TrieNode));
      if (!node->children)
      {
        fprintf(stderr, "Error could not realloc.\n");
        exit(1);
      }
      node->children[node->nb_children - 1].letter = *word;
      node->children[node->nb_children - 1].nb_children = 0;
      node->children[node->nb_children - 1].children = NULL;
      node->children[node->nb_children - 1].freq = 0;

      if (*(word + 1) == '\0')
      {
        node->children[node->nb_children - 1].freq = freq;
      } else {
        add_word_node(trie, &node->children[node->nb_children - 1], ++word, freq);
      }
      return;
    }
  }
}

void add_word_trie(Trie *trie, char *word, uint32_t freq)
{
  if (!trie || !word || *word == '\0')
  {
    return;
  }

  if (trie->nb_children == 0)
  {
    assert(trie->children == NULL);

    trie->children = malloc(sizeof(TrieNode));
    if (!trie->children)
    {
      fprintf(stderr, "Error could not malloc.\n");
      exit(1);
    }
    trie->children->letter = *word;
    trie->children->nb_children = 0;
    trie->children->children = NULL;
    trie->nb_children++;
    trie->nb_nodes++;
    if (*(word + 1) == '\0')
    {
      trie->children->freq = freq;
    } else {
      add_word_node(trie, trie->children, ++word, freq);
    }
    return;
  }

  for (uint16_t i = 0; i < trie->nb_children; i++)
  {
    if (trie->children[i].letter == *word)
    {
      if (*(word + 1) == '\0')
      {
        trie->children[i].freq = freq;
      } else {
        add_word_node(trie, &trie->children[i], ++word, freq);
      }
      return;
    }

    // Not found: let's realloc
    if (i == (trie->nb_children - 1))
    {
      trie->nb_children++;
      trie->nb_nodes++;
      trie->children = realloc(trie->children, trie->nb_children * sizeof(TrieNode));
      if (!trie->children)
      {
        fprintf(stderr, "Error could not realloc.\n");
        exit(1);
      }
      trie->children[trie->nb_children - 1].letter = *word;
      trie->children[trie->nb_children - 1].nb_children = 0;
      trie->children[trie->nb_children - 1].children = NULL;
      trie->children[trie->nb_children - 1].freq = 0;

      if (*(word + 1) == '\0')
      {
        trie->children[trie->nb_children - 1].freq = freq;
      } else {
        add_word_node(trie, &trie->children[trie->nb_children - 1], ++word, freq);
      }
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
  if (trie->nb_children > 0)
    free(trie->children);
}

void release_trie(Trie *trie)
{
  for (uint8_t i = 0; i < trie->nb_children; i++)
  {
    release_node(&trie->children[i]);
  }
  if (trie->nb_children > 0)
    free(trie->children);
  free(trie);
}

TrieNode *search_node(TrieNode *node, char *word)
{
  //printf("%c", *word);
  if (!node || !word || *word == '\0')
  {
    return NULL;
  }

  for (uint8_t i = 0; i < node->nb_children; i++)
  {
    if (node->children[i].letter == *word)
    {
      if (*(word + 1) != '\0')
        return search_node(&node->children[i], ++word);
      return &node->children[i];
    }
  }
  return NULL;
}

TrieNode *search_trie(Trie *trie, char *word)
{
  if (!trie || !word || *word == '\0')
  {
    return NULL;
  }

  for (uint8_t i = 0; i < trie->nb_children; i++)
  {
    if (trie->children[i].letter == *word)
    {
      if (*(word + 1) != '\0')
        return search_node(&trie->children[i], ++word);
      return &trie->children[i];
    }
  }
  return NULL;
}

char *load_trie(char *path)
{
  FILE *file;
  unsigned long len;
  file = fopen(path, "rb");
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

//    A
// B  C  D
//   E
//

void binarize_node(FILE *file, TrieNode *node)
{
  fwrite(node, sizeof(TrieNode), 1, file);
  fflush(file);

  for (uint8_t i = 0; i < node->nb_children; i++)
  {
    binarize_node(file, &node->children[i]);
  }
}

void binarize_trie(Trie *trie, char *path)
{
  FILE *file;
  file = fopen(path, "w");
  if (!file)
  {
    fprintf(stderr, "Error loading file %s\n", path);
    exit(1);
  }

  fwrite(trie, sizeof(Trie), 1, file);
  fflush(file);
  for (uint8_t i = 0; i < trie->nb_children; i++)
  {
    binarize_node(file, &trie->children[i]);
  }
  fclose(file);
}

// Return last children pointer to continue recursion
// Return NULL if no children
// tmp = pointer to mmap zone
// node = pointer to newly reconstruct node
TrieNode *load_binarize_node(TrieNode *tmp, TrieNode *node)
{
  node->letter = tmp->letter;
  node->freq = tmp->freq;
  node->nb_children = tmp->nb_children;
  //printf("Step2\n");

  if (node->nb_children > 0)
  {
    node->children = malloc(node->nb_children * sizeof(TrieNode));
    if (!node->children)
    {
      fprintf(stderr, "Error could not malloc.\n");
      exit(1);
    }
    TrieNode *last = tmp + 1;

    for (uint8_t i = 0; i < node->nb_children; i++)
    {
      //printf("Step%d-0\n", i);
      last = load_binarize_node(last, &node->children[i]);
      //printf("Step%d-1\n", i);

      // Update pointer only if there is children in the node
      if (i != node->nb_children - 1)
        last++;
    }
    return last;
  } else {
    //printf("No children\n");
    node->children = NULL;
    return tmp;
  }
}

Trie *load_binarize_trie(char *path)
{
  printf("size Trie: %lu\n", sizeof(Trie));
  printf("size TrieNode: %lu\n", sizeof(TrieNode));

  int file;
  file = open(path, O_RDONLY);
  if (!file)
  {
    fprintf(stderr, "Error loading file %s\n", path);
    exit(1);
  }

  struct stat s;
  fstat(file, &s);

  // mmap binary file
  Trie *tmp = mmap(0, s.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, file, 0);

  // pointer use to reconstruct the trie, copy informations from root node
  Trie *t = malloc(sizeof(Trie));
  if (!t)
  {
    fprintf(stderr, "Error could not malloc.\n");
    exit(1);
  }
  t->nb_nodes = tmp->nb_nodes;
  t->nb_children = tmp->nb_children;

  if (t->nb_children > 0)
  {
    t->children = malloc(t->nb_children * sizeof(TrieNode));
    if (!t->children)
    {
      fprintf(stderr, "Error could not malloc.\n");
      exit(1);
    }
    TrieNode *last = (TrieNode *)(tmp + 1);

    for (uint8_t i = 0; i < t->nb_children; i++)
    {
      TrieNode *tmp_child = load_binarize_node(last, &t->children[i]);

      if (tmp_child != NULL)
        last = (tmp_child + 1);
      else if (i != t->nb_children - 1)
        last++;
    }
  } else {
    t->children = NULL;
  }

  close(file);
  return t;
}
