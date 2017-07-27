#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#endif

#ifndef TRIE_H
#define TRIE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct TrieNode
{
  char letter;
  uint32_t freq;

  // Array of TrieNode
  uint8_t nb_children;
  struct TrieNode *children;
} TrieNode;

typedef struct Trie
{
  // General metadatas
  uint32_t nb_nodes;

  // Array of TrieNode
  uint8_t nb_children;
  struct TrieNode *children;
} Trie;

#pragma pack(push,1)

typedef struct TrieNodeCompact
{
  uint32_t freq;

  // Array of TrieNode
  uint8_t nb_children;
} TrieNodeCompact;

typedef struct TrieRadix
{
  // General metadatas
  uint32_t nb_nodes;

  // Array of TrieNode
  uint8_t nb_children;
  struct TrieNodeRadix *children;
} TrieRadix;

typedef struct TrieNodeRadix
{
  uint32_t freq;

  // Array of TrieNode
  uint8_t nb_children;
  struct TrieNodeRadix *children;
  char *letter;
} TrieNodeRadix;

#pragma pack(pop)

void add_word_node(TrieRadix *trie, TrieNodeRadix *node, char *word, uint32_t freq);
void add_word_trie(TrieRadix *trie, char *word, uint32_t freq);
void release_node(TrieNode *trie, int* a);
void release_trie(Trie *trie);

// Search for a word in a trie, return NULL if not found
TrieNodeRadix *search_trie(TrieRadix *trie, char *word);
TrieNodeRadix *search_node(TrieNodeRadix *node, char *word);

char *load_trie(char *path);
void binarize_trie(TrieRadix *trie, char *path);
TrieRadix *load_binarize_trie(char *path);

void compress_trie(TrieRadix* t);
int count_trie(TrieRadix* t);
void print_trie(TrieRadix* t);

#endif /* end of include guard: TRIE_H */
