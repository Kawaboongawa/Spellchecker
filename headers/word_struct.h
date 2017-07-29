#pragma once

/**
 * \file word_struct.h
 * \brief Functions used to manage data structures.
 * \author lugand_j, cetre_c
 * \version 0.1
 * \date 29 juillet 2017
 */


#include <stdlib.h>
#include <string.h>

#include "tools.h"


/*! \brief Instanciate a Words structure.
**
** \param size initial size of the word structure containing results.
**/

Words create_words(int size);


/*! \brief free a Words structure.
**
** \param w the structure to free.
**/

void  delete_words(Words* w);

/*! \brief append a Word to a Words structure.
**
** If the initial size is reached, realloc will be called
** to increase the size allocated
** \param w the structure that will append the word.
** \param word the word to append
**/

void  append_word(Words* w, Word* word);


/*! \brief Instanciate a String structure.
**
** \param size initial size of the word structure containing results.
**/
String create_string(int size);



/*! \brief free a String structure.
**
** \param s the structure to free.
**/

void  delete_string(String* s);


/*! \brief append a char to a String structure.
**
** If the initial size is reached, realloc will be called
** to increase the size allocated. The index will be
** increased automatically.

** \param letter the letter that will append the string.
** \param s  The structure that will append the letter
**/
void  append_letter(String* s, char letter);


/*! \brief Decrement the structure inside the structure.
**
** \param s the structure to decrement index.
**/

void  dec_index(String* s);


/*! \brief  return the word of the structure.
**
** Return a whole new string allocated with strdup.
**
** \param s the structure to get the string.
**/

char* get_word(String* s);

/*! \brief  return the letter of the structure at a specified index.
**
** \param s the structure to get the letter.
** \param index the index to get the letter
**/

char  get_letter_index(String* s, int index);
