#include "search.h"

void search(TrieRadix* trie, char* word, uint cost)
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

void search_rec(TrieNodeRadix* tn, char* word, String* str, ushort prevrow[],
                ushort prevrow2[], Words* res, uint cost, uint len, uint y)
{
  ushort currow[len + 1];

  // Need array in case of prevrow2 is NULL (cannot initalize it because it is an array)
  // Maybe a pointer is better to malloc if necessary
  ushort prevrow2tmp[len + 1];

  // Matrix computation with rotation of rows
  // take care by this loop
  unsigned long nb_letters = strlen(tn->letter);
  for (unsigned long j = 0; j < nb_letters; j++)
  {
    // Init first slot of currow at each iterations
    // (rows have been roll so no problem to erase first slot here)
    currow[0] = prevrow[0] + 1;

    append_letter(str, tn->letter[j]);

    for (uint i = 1; i <= len; i++)
    {
        ushort insert_cost = currow[i - 1] + 1;
        ushort delete_cost = prevrow[i] + 1;
        uchar  tmp = (word[i - 1] == tn->letter[j] ? 0 : 1);
        ushort replace_cost = prevrow[i - 1] + tmp;

        currow[i] = min3(insert_cost, delete_cost, replace_cost);

        // if prevrow2 is not null then use it
        if (prevrow2 != NULL)
        {
          if (i > 1 // <--- Remove check of prevrow because I did it before
              && word[i - 1] == get_letter_index(str, y - 2)
              && word[i - 2] == get_letter_index(str, y - 1)
              && prevrow2[i - 2] + tmp < currow[i])
              currow[i] = prevrow2[i - 2] + tmp;
        }
        // else use prevrow2tmp (if not the first letter because prevrow2tmp
        // have no values before the second one)
        else
        {

          if (i > 1 && j > 0 // <--- if not the first later (j > 0)
              && word[i - 1] == get_letter_index(str, y - 2)
              && word[i - 2] == get_letter_index(str, y - 1)
              && prevrow2tmp[i - 2] + tmp < currow[i])
              currow[i] = prevrow2tmp[i - 2] + tmp;
        }
    }

    if (j != (nb_letters - 1))
    {
      // Roll rows for each loop except the last one because
      // the recursive call take care of moving currow and prevrow
      // tmp      <- prevrow
      // prevrow  <- currow
      // prevrow2 <- tmp
      ushort tmp[len + 1];
      for (unsigned int k = 0; k < len + 1; k++)
        tmp[k] = prevrow[k];
      for (unsigned int k = 0; k < len + 1; k++)
        prevrow[k] = currow[k];

      // if prevrow2 is not null then use it
      if (prevrow2 != NULL)
      {
        for (unsigned int k = 0; k < len + 1; k++)
          prevrow2[k] = tmp[k];
      }
      // else use prevrow2tmp
      else
      {
        for (unsigned int k = 0; k < len + 1; k++)
          prevrow2tmp[k] = tmp[k];
      }
      // Increment y at each turn except for last one because
      // recursive call with y + 1 later
      y++;
    }
  }

  // Not in the loop because:
  // Only check for a word cost at the end of the loop
  if (currow[len] <= cost && tn->freq != 0)
  {
      char *currstr = get_word(str);
      Word currword = { .word = currstr, .freq = tn->freq, .dist = currow[len] };
      append_word(res, &currword);
  }

  // Merge the two conditions here to avoid useless tmp variable no big deal
  for (uint i = 0; i <= len; i++)
  {
    if (currow[i] <= cost)
    {
      for (size_t i = 0; i < tn->nb_children; i++)
      {
          search_rec(&(tn->children[i]), word, str, currow, prevrow,
                     res, cost, len, y + 1);
      }
      break;
    }
  }

  // Dec index can now decrease by a number the index
  // (faster than loop so I changed it)
  dec_index(str, nb_letters);
}
