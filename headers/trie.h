#ifndef TRIE_H
#define TRIE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

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

void add_word_node(Trie *trie, TrieNode *node, char *word, uint32_t freq);
void add_word_trie(Trie *trie, char *word, uint32_t freq);
void release_node(TrieNode *trie);
void release_trie(Trie *trie);

// Search for a word in a trie, return NULL if not found
TrieNode *search_trie(Trie *trie, char *word);
TrieNode *search_node(TrieNode *node, char *word);

char *load_trie(char *path);

#endif /* end of include guard: TRIE_H */
