#include "search.h"

void search(Trie* trie, char* word, uint cost)
{
    size_t len = strlen(word);
    ushort currow[len + 1];
    for (size_t i = 0; i <= len; i++)
        currow[i] = i;
    Words res = create_words(512);
    String str = create_string(512);
    for (size_t i = 0; i < trie->nb_children; i++)
        search_rec(&(trie->children[i]), word, &str,
                   currow, NULL, &res, cost, len, 1);
    delete_string(&str);
    //printf("%d\n", cost);
    sort_word(&res);
    print_json(&res);
    delete_words(&res);
}

/*
void search_rec(TrieNode* tn, char* word, String* str,
                Words* res, uint cost, uint len)
{
    append_letter(str, tn->letter);
    uint len2 = str->index;
    uint matrix[len2 + 1][len + 1];
    levenshtein(word, str->str, len, len2, matrix);
    printf("%d %d %d\n ", len, len2, matrix[len2][len]);
    if (matrix[len2][len] <= cost  && tn->freq != 0 )
    {
        char * currstr = get_word(str);
        Word currword = {.word = currstr, .freq = tn->freq,
                         .dist = matrix[len2][len]};
        append_word(res, &currword);
    }
    uchar b = 0;
    for (uint i = 0; i <= len; i++)
        if (matrix[len2][i] <= cost)
        {
            b = 1;
            break;
        }
    
    if (b)
    {
        for (size_t i = 0; i < tn->nb_children; i++)
            search_rec(&(tn->children[i]), word, str,
                       res, cost, len);
    }
    dec_index(str);
}
*/

void search_rec(TrieNode* tn, char* word, String* str, ushort prevrow[],
                ushort prevrow2[], Words* res, uint cost, uint len, uint y)
{
    ushort currow[len + 1];
    currow[0] = prevrow[0] + 1;
    append_letter(str, tn->letter);
    for (uint i = 1; i <= len; i++)
    {
        ushort insert_cost = currow[i - 1] + 1;
        ushort delete_cost = prevrow[i] + 1;
        uchar  tmp = (word[i - 1] == tn->letter ? 0 : 1);
        ushort replace_cost = prevrow[i - 1] + tmp;
        
        currow[i] = min3(insert_cost, delete_cost, replace_cost);
        if (i > 1 && prevrow2 != NULL
            && word[i - 1] == get_letter_index(str, y - 2)
            && word[i - 2] == get_letter_index(str, y - 1)
            && prevrow2[i - 2] + tmp < currow[i])
            currow[i] = prevrow2[i- 2] + tmp;
    }
    
    if (currow[len] <= cost  && tn->freq != 0 )
    {
        char * currstr = get_word(str);
        Word currword = {.word = currstr, .freq = tn->freq, .dist = currow[len]};
        append_word(res, &currword);
    }
    uchar b = 0;
    for (uint i = 0; i <= len; i++)
        if (currow[i] <= cost)
        {
            b = 1;
            break;
        }
    
    if (b)
    {
        for (size_t i = 0; i < tn->nb_children; i++)
            search_rec(&(tn->children[i]), word, str, currow, prevrow,
                       res, cost, len, y + 1);
    }
    dec_index(str);
}
