#pragma once

#include <string.h>
#include <stdint.h>

#include "tools.h"
#include "word_struct.h"
#include "trie.h"

void search(Trie* trie, char* word, uint cost);

void search_rec(TrieNode tn, char* word, String str,
                ushort prevrow[], Words* res, uint cost, uint len);

