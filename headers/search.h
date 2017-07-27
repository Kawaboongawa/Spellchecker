#pragma once

#include <string.h>
#include <stdint.h>

#include "tools.h"
#include "word_struct.h"
#include "trie.h"
#include "levenshtein.h"

void search(Trie* trie, char* word, uint cost);
/*
void search_rec(TrieNode* tn, char* word, String* str,
                Words* res, uint cost, uint len);
*/

void search_rec(TrieNode* tn, char* word, String* str, ushort prevrow[],
                ushort prevrow2[], Words* res, uint cost, uint len, uint y);


