#pragma once

#include <string.h>
#include <stdint.h>

#include "tools.h"
#include "word_struct.h"

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

Words search(Trie trie, char* word, uint cost);

void search_rec(TrieNode tn, char* word, String str,
                ushort prevrow[], Words res, uint cost, uint len);

