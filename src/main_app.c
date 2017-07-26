#include <stdio.h>
#include <stdlib.h>

#include "levenshtein.h"
#include "tools.h"
#include "word_struct.h"
#define BUF_SIZE 128



int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;
    String s = create_string(3);
    append_letter(&s, 'I');
    append_letter(&s, 'L');
    append_letter(&s, 'O');
    append_letter(&s, 'O');
    append_letter(&s, 'p');
    append_letter(&s, 'I');
    dec_index(&s);
    append_letter(&s, 'p');
    char* str = get_word(&s);
    printf("%s\n%d\n", str, s.index);
    free(str);
    delete_string(&s);
    /*Word l[3] = {{.word = "blu", .freq = 52, .dist = 12},
      {.word = "bleu", .freq = 40, .dist = 42},
      {.word = "ble", .freq = 1, .dist = 3}};
      print_json(l, 3);*/
    /*argv = argv;
    //printf("%c\n", fgetc(stdin));
    if (argc < 2)
    {
        printf("Usage: ./TextMiningApp /path/to/compiled/dict.bin\n");
        printf("Aborted (core dumped)\n");
        return 134;
    }

    size_t  size = 0;
    char* buf = NULL;
    getline(&buf, &size, stdin);
    printf("%s", buf);
    free(buf);
    */
}
