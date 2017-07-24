#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct TrieNode
{
  uint8_t letter;
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
  uint32_t nb_children;
  struct TrieNode *children;
} Trie;

void add_word_node(Trie *trie, TrieNode *node, char *word);
void add_word_trie(Trie *trie, char *word);
void release_node(TrieNode *trie);
void release_trie(Trie *trie);

#endif /* end of include guard: TRIE_H */
