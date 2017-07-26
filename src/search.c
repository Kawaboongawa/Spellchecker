#include "search.h"

void search(Trie* trie, char* word, uint cost)
{
    size_t len = strlen(word);
    ushort currow[len + 1];
    for (size_t i = 0; i <= len; i++)
        currow[i] = i;
    Words res = create_words(512);
    String str = create_string(512);
    printf("wut\n");
    for (size_t i = 0; i < trie->nb_children; i++)
        search_rec(trie->children[i], word, str, currow, &res, cost, len);
    printf("wat\n");
    delete_string(&str);
    printf("%d %d\n", res.index, res.size);
    print_json(&res);
}


void search_rec(TrieNode tn, char* word, String str,
                ushort prevrow[], Words* res, uint cost, uint len)
{
    ushort currow[len + 1];
    currow[0] = prevrow[0] + 1;
    append_letter(&str, tn.letter);
    for (uint i = 1; i < len; i++)
    {
        ushort insert_cost = currow[i - 1] + 1;
        ushort delete_cost = prevrow[i] + 1;
        uchar  tmp = (word[i - 1] == tn.letter ? 0 : 1);
        ushort replace_cost = prevrow[i - 1] + tmp;
        currow[i] = min3(insert_cost, delete_cost, replace_cost);
    }
    
    if (currow[len] <= cost) // && check tn.word != null ???
    {
        char * currstr = get_word(&str);
        Word currword = {.word = currstr, .freq = 0, .dist = currow[len]};
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
        for (size_t i = 0; i < tn.nb_children; i++)
            search_rec(tn.children[i], word, str,currow, res, cost, len);
    }
    dec_index(&str);
}
