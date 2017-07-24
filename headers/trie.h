#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct TrieNode
{
  uint8_t letter;
  uint32_t freq;
  uint8_t nb_children;
  // Array of TrieNode
  struct TrieNode *children;
} TrieNode;

typedef struct Trie
{
  uint32_t nb_children;
  // Array of TrieNode
  struct TrieNode *children;
} Trie;

void add_word_node(TrieNode *trie, char *word);
void add_word_trie(Trie *trie, char *word);
void release_node(TrieNode *trie);
void release_trie(Trie *trie);

#endif /* end of include guard: TRIE_H */
