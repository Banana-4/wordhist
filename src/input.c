#include "../include/input.h"

int input_loop(char **words, const size_t MAX_WORD, int *lens, const size_t MAX, int *h) {
    bool inword = false;
    int i = -1;
    *h = 0;
    char *buf = NULL;
    int c;
    int bp;

    while ((c = getchar()) != EOF) {
        if (inword && (!isalpha(c) && !isdigit(c) && c != '\'')) {
            inword = false;
            *h = *h < lens[i] ? lens[i] : *h;
            buf[bp] = '\0';
            words[i] = buf;
        }
        else if ( inword == false && isalpha(c) ) {
            inword = true;
            if (++i == MAX)
                break;
            bp = 0;
            buf = malloc(MAX_WORD);
            if (!buf) {
                return -1;
            }
        }
        if (inword) {
            lens[i]++;
            buf[bp++] = c;
            if (bp == MAX_WORD - 1) {
                del_words(words, i);
                free(buf);
                return -1;
            }
        }
    }
    if (inword) {
        buf[bp] = '\0';
        words[i] = buf;
        *h = *h < lens[i] ? lens[i] : *h;
    }
    return i;
}

void del_words(char **words, const size_t len) {
    for (int j = 0; j <= len; ++j)
        free(words[j]);
}
