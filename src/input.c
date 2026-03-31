#include "../include/input.h"
#include <memory.h>
#define COUNT 0

int input_loop(StrArray *words, Array *lens, int *h) {
    bool inword = false;
    int i = -1;
    *h = 0;
    Str *buf = NULL;
    int c;

    while ((c = getchar()) != EOF) {
        if (inword && (!isalpha(c) && !isdigit(c) && c != '\'')) {
            inword = false;
            *h = *h < lens->block[i] ? lens->block[i] : *h;
            if (!append_StrArray(words, buf)) {
                del_Str(buf);
                return 1;
            }
        }
        else if (inword == false && isalpha(c)) {
            inword = true;
            buf = new_Str();
            if (!buf) {
                return 1;
            }
            if (!append_Array(lens, COUNT)) {
                del_Str(buf);
                return 1;
            }
            ++i;
        }
        if (inword) {
            lens->block[i]++;
            if (!append_Str(buf, c)) {
                del_Str(buf);
                return 1;
            }
        }
    }

    if (inword) {
        if(!append_StrArray(words, buf))
        *h = *h < lens->block[i] ? lens->block[i] : *h;
    }
    return 0;
}
