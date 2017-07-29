#pragma once

#include <string.h>
#include <stdint.h>

#include "tools.h"
#include "word_struct.h"
#include "trie.h"
#include "levenshtein.h"

void search(TrieRadix* trie, char* word, uint cost, Words *res, String *str);

void search_rec(TrieNodeRadix* tn, char* word, String* str, ushort prevrow[],
                ushort prevrow2[], Words* res, const uint cost, uint len,
                int index, int cur_inf);
