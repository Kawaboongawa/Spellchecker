#pragma once

/**
 * \file search.h
 * \brief core of the TextMiningApp binary.
 * \author lugand_j, cetre_c
 * \version 0.1
 * \date 29 juillet 2017
 */

#include <string.h>
#include <stdint.h>

#include "tools.h"
#include "word_struct.h"
#include "trie.h"


/*! \brief Main function called to start depth-first search in radix tree.
**
** Very basic function that initialize structures, launch the recursion
** through the radix tree, free the data and finally print the result.
**
** \param trie The radix tree obtained by reading through the dictionary.
** \param word The word that we are looking for through the search.
** \param cost The maximum distance allowed during the search.
** \param res  The structure that contains the words that match the request
** \param str  Contains the current string while going through the radix tree
**/
void search(TrieRadix* trie, char* word, uint cost, Words *res, String *str);



/*! \brief Recursive function that iterates through the radix tree.
**
** Core function of the search that recursively iterate through the
** nodes of the radix tree.
** This implementation is using the optimized levenshtein implementation
** with a tree. Modifications were made to allow it to be able to handle
** a damerau Levenshtein by keeping a second row.
**
** \param trie The current radix tree node that we are going to precess.
** \param word The word that we are looking for through the search.
** \param str  Contains the current string while going through the radix tree
** \param prevrow contain the immediate upper row in the levenshtein matrix.
** \param prevrow2 contain the second upper row in the levenshtein matrix (y - 2)
** \param res  The structure that contains the words that match the request
** \param cost The maximum distance allowed during the search.
** \param len  The len of the string in the node
**  if the current node is not only one letter
** \param index The index of the current letter processed used
**  if the current node has more than one letter (radix tree)
**/
void search_rec(TrieNodeRadix* tn, char* word, String* str, ushort prevrow[],
                ushort prevrow2[], Words* res, const uint cost, uint len,
                int index, int cur_inf);
