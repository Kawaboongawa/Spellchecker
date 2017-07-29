#include "search.h"

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

void search(TrieRadix* trie, char* word, uint cost, Words* res, String *str)
{
    size_t len = strlen(word);
    ushort currow[len + 1];

    for (size_t i = 0; i <= len; i++)
        currow[i] = i;

    for (size_t i = 0; i < trie->nb_children; i++)
        search_rec(&(trie->children[i]), word, str,
                   currow, NULL, res, cost, len, 0);

    //delete_string(&str);
    //printf("%d\n", cost);
    sort_word(res);
    print_json(res);
    //delete_words(&res);
}

void search_rec(TrieNodeRadix* tn, char* word, String* str, ushort prevrow[],
                ushort prevrow2[], Words* res, const uint cost, uint len,
                int index)
{
    ushort currow[len + 1];
    currow[0] = prevrow[0] + 1;
    append_letter(str, tn->letter[index]);

    for (uint i = 1; i <= len; i++)
    {
        ushort insert_cost = currow[i - 1] + 1;
        ushort delete_cost = prevrow[i] + 1;
        uchar  tmp = (word[i - 1] == tn->letter[index] ? 0 : 1);
        ushort replace_cost = prevrow[i - 1] + tmp;

        currow[i] = MIN3(insert_cost, delete_cost, replace_cost);
        if (i > 1 && prevrow2 != NULL
            && word[i - 1] == get_letter_index(str, str->index - 2)
            && word[i - 2] == get_letter_index(str, str->index - 1)
            && prevrow2[i - 2] + tmp < currow[i])
            currow[i] = prevrow2[i - 2] + tmp;
    }

    if (tn->letter[index + 1] == '\0' && currow[len] <= cost && tn->freq != 0)
    {
        char *currstr = get_word(str);
        Word currword = { .word = currstr, .freq = tn->freq,
                         .dist = currow[len] };
        append_word(res, &currword);
    }

    for (uint i = 0; i <= len; i++)
    {
        if (currow[i] <= cost)
        {
            if (tn->letter[++index] == '\0')
            {
              for (size_t i = 0; i < tn->nb_children; i++)
                  search_rec(&(tn->children[i]), word, str, currow, prevrow,
                             res, cost, len, 0);
            }
            else
            {
                search_rec(tn, word, str, currow, prevrow,
                           res, cost, len, index);
            }
            break;
        }
    }
    dec_index(str);
}
