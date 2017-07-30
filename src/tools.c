#include "tools.h"

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

void sort_word(Words* words)
{
    qsort(words->word, words->index, sizeof(Word), compare_word);
}

int compare_word(const void* w1, const void* w2)
{
    if ((((Word*) w1)->dist > ((Word*) w2)->dist)
        || (((Word*) w1)->dist == ((Word*) w2)->dist
            && ((Word*) w1)->freq < ((Word*) w2)->freq)
        || (((Word*) w1)->dist == ((Word*) w2)->dist
            && ((Word*) w1)->freq == ((Word*) w2)->freq
            && strcmp(((Word*) w1)->word, ((Word*) w2)->word) > 0))
        return 1;
    return -1;
}

void print_json(Words* words)
{
    printf("[");
    for (uint i = 0; i < words->index; i++)
    {
        printf("{\"word\":\"%s\",\"freq\":%d,"
               "\"distance\":%d}", words->word[i].word,
               words->word[i].freq, words->word[i].dist);
        if (i < words->index - 1)
            printf(",");
    }
    printf("]\n");
}

inline int min3 (int a, int b, int c)
{
  __asm__ (
           "cmp     %0, %1\n\t"
           "cmovle  %1, %0\n\t"
           "cmp     %0, %2\n\t"
           "cmovle  %2, %0\n\t"
          : "+r"(a) :
            "%r"(b), "r"(c)
          );
  return a;
}
