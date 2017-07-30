/**
 * \file trie.h
 * \brief Patricia Trie implementation.
 * \author lugand_j, cetre_c
 * \version 0.1
 * \date 29 juillet 2017
 */

#ifndef TRIE_H
# define TRIE_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <assert.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

# pragma pack(push,1)

/*! \brief a compact stucture containing a node of the Trie.
**
** We need a compact representation of a Trie node for saving it
** in a binary file. This representation only keep informations about
** frequency of the word and number of children of the node.
** The letters will be saved after the structure in the binary file.
**
** \param freq the frequence of the word given in the radix tree.
** \param nb_children number of children of the node.
**/
typedef struct TrieNodeCompact
{
  uint32_t freq;
  uint8_t nb_children;
} TrieNodeCompact;

/*! \brief the root node of the Trie.
**
** This structure is the root node of the Trie.
**
** \param nb_nodes number of nodes in the tree (to avoid recomputation).
** \param nb_children number of children of the node.
** \param children array of TrieNodeRadix (1 slot for each child).
**/
typedef struct TrieRadix
{
  uint32_t nb_nodes;
  uint8_t nb_children;
  struct TrieNodeRadix *children;
} TrieRadix;

/*! \brief the node of the Trie.
**
** This structure is the node of the Trie.
**
** \param freq the frequence of the word given in the radix tree
**        (= 0 if not a word node).
** \param nb_children number of children of the node.
** \param children array of TrieNodeRadix (1 slot for each child).
** \param letter pointer to the string contained in the node.
**/
typedef struct TrieNodeRadix
{
  uint32_t freq;
  uint8_t nb_children;
  struct TrieNodeRadix *children;
  char *letter;
} TrieNodeRadix;

# pragma pack(pop)

/*! \brief Add a word in the Trie.
**
** This function walk recursively through the Trie to add the word.
** We keep a pointer to the root of the Trie to increment nb_nodes.
** The function add a word by adding a node for each letter, to get a Radix Trie
** from it you have to call the compress_trie function.
**/
void add_word_node(TrieRadix *trie, TrieNodeRadix *node, char *word, uint32_t freq);
/*!
**  \brief Root version of add_word_node.
**/
void add_word_trie(TrieRadix *trie, char *word, uint32_t freq);

/*!
** \brief Free the memory occupied by the node after freeing the children
**        nodes' memory.
**/
void release_node(TrieNodeRadix *trie);
/*!
**  \brief Root version of release_node.
**/
void release_trie(TrieRadix *trie);

/*!
**  \brief Search for a word in a node, return NULL if not found.
**/
TrieNodeRadix *search_node(TrieNodeRadix *node, char *word);
/*!
**  \brief Root version of search_node.
**/
TrieNodeRadix *search_trie(TrieRadix *trie, char *word);

/*!
**  \brief Load the content of the file at path and return the pointer to the
**         allocated memory space.
**/
char *load_trie(char *path);

/*!
**  \brief Write the content of a node in a binary file.
**
**  This function write the content fo the node in a compact way:
**  freq + nb_children followed by the string and a \0.
**  Then call the children recursively.
**/
void binarize_node(FILE *file, TrieNodeRadix *node);
/*!
**  \brief Root version of binarize_node.
**/
void binarize_trie(TrieRadix *trie, char *path);

/*!
**  \brief Load the content of a node in a binary file.
**/
TrieNodeCompact *load_binarize_node(TrieNodeCompact *tmp, TrieNodeRadix *node);
/*!
**  \brief Load the content of the root node of the Trie in a binary file.
**
**  This function load the content of the binary file, read informations
**  about the root node and then call recursively the load function on children.
**/
TrieRadix *load_binarize_trie(char *path);

/*!
**  \brief Compress a Trie into a Radix Trie.
**
**  This function search for non terminal nodes (freq=0) with only one child
**  to compress it to an only node with the concatenation of letters.
**  The memory from the old child node is free by the function.
**/
void compress_node(TrieRadix* r, TrieNodeRadix* t);
/*!
**  \brief Root version of compress_node.
**/
void compress_trie(TrieRadix* t);

/*!
**  \brief Count the number of nodes in a Trie.
**
**  The root node contains the number of nodes but can be useful for Testing
**  purpose.
**/
void count_node(TrieNodeRadix* t, int* a);
/*!
**  \brief Root version of count_node.
**/
int count_trie(TrieRadix* t);

/*!
**  \brief Print the content of a node in standard output.
**
**  Display informations about the nodes that are less then depth deep in the
**  Trie.
**/
void print_node(TrieNodeRadix* t, int* nb, int depth, int cur_depth);
/*!
**  \brief Root version of print_node.
**/
void print_trie(TrieRadix* t, int depth);

#endif /* end of include guard: TRIE_H */
