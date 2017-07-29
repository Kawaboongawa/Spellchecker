#include "word_struct.h"
#include <assert.h>

Words create_words(int size)
{
    Word* w = malloc(size * sizeof (Words));
    assert(w);
    Words new_struct = {.word = w, .index = 0, .size = size};
    return new_struct;
}
void  delete_words(Words* w)
{
    free(w->word);
}

void append_word(Words* w, Word* word)
{
    if (w->index == w->size - 1)
    {
        w->size += 512;
        w->word = realloc(w->word, w->size * sizeof (Word));
        assert(w->word);
    }
    w->word[w->index] = *word;
    w->index++;
}

String create_string(int size)
{
    char* str = malloc(size * sizeof (String));
    assert(str);
    String new_struct = { .str = str, .index = 0, .size = size };
    return new_struct;
}

void delete_string(String* s)
{
    free(s->str);
}

void append_letter(String* s, char letter)
{
    if (s->index == s->size - 1)
    {
        s->size += 512;
        s->str = realloc(s->str, s->size * sizeof (char));
        assert(s->str);
    }
    s->str[s->index++] = letter;
}

void dec_index(String* s)
{
    s->index--;
}

char* get_word(String* s)
{
    char* str = malloc(s->index + 1);
    assert(str);
    str = strncpy(str, s->str, s->index);
    str[s->index] = '\0';
    return str;
}

char get_letter_index(String* s, int index)
{
    return s->str[index];
}
