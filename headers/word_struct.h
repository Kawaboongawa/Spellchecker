#pragma once

#include <stdlib.h>
#include <string.h>

#include "tools.h"

Words create_words(int size);
void  delete_words(Words* w);
void  append_word(Words* w, Word* word);

String create_string(int size);
void  delete_string(String* s);
void  append_letter(String* s, char letter);
void  dec_index(String* s);
char* get_word(String* s);
