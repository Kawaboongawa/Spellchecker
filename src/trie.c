#include "trie.h"

void add_word_node(TrieRadix *trie, TrieNodeRadix *node, char *word, uint32_t freq)
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
    node->children->letter = malloc(2 * sizeof(char));
    node->children->letter[0] = *word;
    node->children->letter[1] = '\0';

    node->children->nb_children = 0;
    node->children->freq = 0;
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

  for (uint8_t i = 0; i < node->nb_children; i++)
  {
    if (node->children[i].letter[0] == *word)
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
      node->children[node->nb_children - 1].letter = malloc(2 * sizeof(char));
      node->children[node->nb_children - 1].letter[0] = *word;
      node->children[node->nb_children - 1].letter[1] = '\0';

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

void add_word_trie(TrieRadix *trie, char *word, uint32_t freq)
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
    trie->children->letter = malloc(2 * sizeof(char));
    trie->children->letter[0] = *word;
    trie->children->letter[1] = '\0';

    trie->children->nb_children = 0;
    trie->children->freq = 0;
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

  for (uint8_t i = 0; i < trie->nb_children; i++)
  {
    if (trie->children[i].letter[0] == *word)
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
      trie->children[trie->nb_children - 1].letter = malloc(2 * sizeof(char));
      trie->children[trie->nb_children - 1].letter[0] = *word;
      trie->children[trie->nb_children - 1].letter[1] = '\0';

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

void release_node(TrieNode *trie, int* a)
{
  if (trie->nb_children == 1 && trie->freq == 0)
  {
    (*a)++;
  }
  for (uint8_t i = 0; i < trie->nb_children; i++)
  {
    release_node(&trie->children[i], a);
  }
  if (trie->nb_children > 0)
    free(trie->children);
}

void release_trie(Trie *trie)
{
  int a = 0;
  for (uint8_t i = 0; i < trie->nb_children; i++)
  {
    release_node(&trie->children[i], &a);
  }
  if (trie->nb_children > 0)
    free(trie->children);
  free(trie);
  printf("\n%d nodes with 1 son.\n", a);
}

TrieNodeRadix *search_node(TrieNodeRadix *node, char *word)
{
  if (!node || !word || *word == '\0')
  {
    return NULL;
  }

  for (uint8_t i = 0; i < node->nb_children; i++)
  {
    unsigned long len = strlen(node->children[i].letter);
    char * tmp = word;
    for (unsigned long j = 0; j < len; j++)
    {
      if (node->children[i].letter[j] != *word && j == 0)
        break;
      if (node->children[i].letter[j] != *word && j > 0)
        return NULL;
      if (node->children[i].letter[j] == *word && j == len - 1l)
      {
        if (*(word + 1) != '\0')
        {
          return search_node(&node->children[i], ++word);
        }
        return &node->children[i];
      }
      word++;
    }
    word = tmp;
  }
  return NULL;
}

TrieNodeRadix *search_trie(TrieRadix *trie, char *word)
{
  if (!trie || !word || *word == '\0')
  {
    return NULL;
  }

  for (uint8_t i = 0; i < trie->nb_children; i++)
  {
    unsigned long len = strlen(trie->children[i].letter);
    char * tmp = word;
    for (unsigned long j = 0; j < len; j++)
    {
      if (trie->children[i].letter[j] != *word && j == 0)
        break;
      if (trie->children[i].letter[j] != *word && j > 0)
        return NULL;
      if (trie->children[i].letter[j] == *word && j == len - 1l)
      {
        if (*(word + 1) != '\0')
        {
          return search_node(&trie->children[i], ++word);
        }
        return &trie->children[i];
      }
      word++;
    }
    word = tmp;
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

void binarize_node(FILE *file, TrieNodeRadix *node)
{
  TrieNodeCompact c;
  c.freq = node->freq;
  c.nb_children = node->nb_children;

  fwrite(&c, sizeof(TrieNodeCompact), 1, file);
  fflush(file);
  fwrite(node->letter, strlen(node->letter), 1, file);
  fflush(file);
  putc('\0', file);
  fflush(file);

  for (uint8_t i = 0; i < node->nb_children; i++)
  {
    assert(i != 255);
    binarize_node(file, &node->children[i]);
  }
}

void binarize_trie(TrieRadix *trie, char *path)
{
  FILE *file;
  file = fopen(path, "w");
  if (!file)
  {
    fprintf(stderr, "Error loading file %s\n", path);
    exit(1);
  }

  fwrite(trie, sizeof(TrieRadix), 1, file);
  fflush(file);

  for (uint8_t i = 0; i < trie->nb_children; i++)
  {
    assert(i != 255);
    binarize_node(file, &trie->children[i]);
  }

  fclose(file);
}

// Return last children pointer to continue recursion
// Return NULL if no children
// tmp = pointer to mmap zone
// node = pointer to newly reconstruct node
TrieNodeCompact *load_binarize_node(TrieNodeCompact *tmp, TrieNodeRadix *node)
{
  node->freq = tmp->freq;
  node->nb_children = tmp->nb_children;

  // chars of letters are after struct in binary format
  char *ptr = (char *)(tmp + 1);
  //printf("%c\n", *ptr);
  unsigned long len = strlen(ptr) + 1;
  node->letter = malloc(len * sizeof(char));
  strncpy(node->letter, ptr, len);
  tmp = (TrieNodeCompact *)(ptr + len);

  if (node->nb_children > 0)
  {
    node->children = malloc(node->nb_children * sizeof(TrieNodeRadix));

    if (!node->children)
    {
      fprintf(stderr, "Error could not malloc.\n");
      exit(1);
    }
    TrieNodeCompact *last = tmp;

    for (uint8_t i = 0; i < node->nb_children; i++)
    {
      assert(i != 255);
      last = load_binarize_node(last, &node->children[i]);
      if (i != node->nb_children - 1)
      {
        // chars of letters are after struct in binary format
        //char *ptr2 = (char *)(last + 1);
        //printf("%c\n", *ptr2);
        //last = (TrieNodeCompact *)(ptr2 + strlen(ptr2) + 1);
      }
    }
    return last;
  }
  else
  {
    node->children = NULL;
    return tmp;
  }
}

TrieRadix *load_binarize_trie(char *path)
{
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
  TrieRadix *tmp = mmap(0, (size_t)s.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, file, 0);
  //printf("%p\n", (void *)tmp);

  // pointer use to reconstruct the trie, copy informations from root node
  TrieRadix *t = malloc(sizeof(TrieRadix));
  if (!t)
  {
    fprintf(stderr, "Error could not malloc.\n");
    exit(1);
  }
  t->nb_nodes = tmp->nb_nodes;
  t->nb_children = tmp->nb_children;
  //printf("nb: %u\n", tmp->nb_children);

  if (t->nb_children > 0)
  {
    t->children = malloc(t->nb_children * sizeof(TrieNodeRadix));
    if (!t->children)
    {
      fprintf(stderr, "Error could not malloc.\n");
      exit(1);
    }
    TrieNodeCompact *last = (TrieNodeCompact *)(tmp + 1);
    //printf("%p\n", (void *)last);

    for (uint8_t i = 0; i < t->nb_children; i++)
    {
      assert(i != 255);
      last = load_binarize_node(last, &t->children[i]);
      if (i != t->nb_children - 1)
      {
        // chars of letters are after struct in binary format
        //char *ptr = (char *)(last + 1);
        //unsigned long len = strlen(ptr) + 1;
        //last = (TrieNodeCompact *)(ptr + len);
        //printf("%p\n", (void *)last);
      }
    }
  } else {
    t->children = NULL;
  }

  close(file);
  return t;
}

void print_node(TrieNodeRadix* t, int* nb)
{
  printf("%d [label=\"%s,%u\"];\n", *nb, t->letter, t->freq);
  int my_nb = *nb;

  for (uint8_t i = 0; i < t->nb_children; i++)
  {
    assert(i != 255);
    (*nb)++;
    printf("%d -> %d;\n", my_nb, *nb);
    print_node(&t->children[i], nb);
  }
  fflush(stdout);
}

void print_trie(TrieRadix* t)
{
  int nb = 0;
  printf("digraph G {\n");
  for (uint8_t i = 0; i < t->nb_children; i++)
  {
    assert(i != 255);
    print_node(&t->children[i], &nb);
  }
  printf("}\n");
}

void count_node(TrieNodeRadix* t, int* a)
{
  (*a)++;
  for (uint8_t i = 0; i < t->nb_children; i++)
  {
    assert(i != 255);
    count_node(&t->children[i], a);
  }
}

int count_trie(TrieRadix* t)
{
  int a = 0;
  for (uint8_t i = 0; i < t->nb_children; i++)
  {
    assert(i != 255);
    count_node(&t->children[i], &a);
  }
  return a;
}

void compress_node(TrieRadix* r, TrieNodeRadix* t)
{
  // if a single child and (I am not a terminal node)
  while (t->nb_children == 1 && t->freq == (uint32_t)0)
  {
    assert(t->children);
    t->freq = t->children->freq;
    // printf("%u\n", t->children->freq);

    unsigned long len = strlen(t->letter);
    t->letter = realloc(t->letter, (len + 2) * sizeof(char));
    t->letter[len] = t->children->letter[0];
    t->letter[len + 1] = '\0';
    r->nb_nodes = r->nb_nodes - 1;

    TrieNodeRadix* tmp = t->children;
    t->nb_children = t->children->nb_children;
    t->children = t->children->children;
    if (!t->children)
      assert(t->nb_children == 0);
    free(tmp);
  }

  for (uint8_t i = 0; i < t->nb_children; i++)
  {
    assert(i != 255);
    compress_node(r, &t->children[i]);
  }
}

// Optimize trie to radix trie
void compress_trie(TrieRadix* t)
{
  for (uint8_t i = 0; i < t->nb_children; i++)
  {
    assert(i != 255);
    compress_node(t, &t->children[i]);
  }
}
