#include "../include/input.h"

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
            if(insert_HashMap(m, buf)) {
                if (*h < buf->len) {
                    *h = buf->len;
                }
                buf = NULL;
            } else {
                del_Str(buf);
                buf = NULL;
            }
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
        if(insert_HashMap(m, buf)) {
            if (*h < buf->len) {
                    *h = buf->len;
            }
            buf = NULL;
            } else {
            del_Str(buf);
            buf = NULL;
        }
    }
    *words = transfer_data(m);
    del_HashMap(m);
    return 0;
}
