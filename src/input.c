#include "../include/input.h"
#include <memory.h>

bool __process_string(HashMap *m, Str *str, int *h) {
    if(insert_HashMap(m, str)) {
                if (*h < str->len) {
                    *h = str->len;
                }
                str = NULL;
                return true;
            } else {
                del_Str(str);
                str = NULL;
                return false;
            }

}

int input_loop(StrArray **words, int *h) {
    bool inword = false;
    *h = 0;
    Str *buf = NULL;
    int c;
    HashMap *m = new_HashMap();
    if (!m) {
        return 1;
    }

    while ((c = getchar()) != EOF) {
        if (inword && (!isalpha(c) && !isdigit(c) && c != '\'')) {
            inword = false;
            __process_string(m, buf, h);
        }

        else if (inword == false && isalpha(c)) {
            inword = true;
            buf = new_Str();
            if (!buf) {
                del_HashMap(m);
                return 1;
            }
        }
        if (inword) {
            if (!append_Str(buf, c)) {
                del_HashMap(m);
                del_Str(buf);
                return 1;
            }
        }
    }

    if (inword) {
        __process_string(m, buf, h);
    }

    *words = transfer_data(m);
    del_HashMap(m);
    return 0;
}
