#include "../include/input.h"
#include <memory.h>

bool __process_string(StrArrayBuilder *builder, Str *str, int *h) {
    MEM_ERRORS err = insert_StrArrayBuilder(builder, str);
    if(err == NO_ERR) {
                if (*h < str->len) {
                    *h = str->len;
                }
                str = NULL;
                return true;
            } else if (err == MEM_ERR){
                del_Str(str);
                str = NULL;
                return false;
    }
    return true;
}

int input_loop(StrArray **words, int *h) {
    bool inword = false;
    *h = 0;
    Str *buf = NULL;
    int c;
    StrArrayBuilder *builder = new_StrArrayBuilder();
    if (!builder) {
        return 1;
    }

    while ((c = getchar()) != EOF) {
        if (inword && (!isalpha(c) && !isdigit(c) && c != '\'')) {
            inword = false;
            __process_string(builder, buf, h);
        }

        else if (inword == false && isalpha(c)) {
            inword = true;
            buf = new_Str();
            if (!buf) {
                del_StrArrayBuilder(builder);
                return 1;
            }
        }
        if (inword) {
            if (!append_Str(buf, c)) {
                del_StrArrayBuilder(builder);
                del_Str(buf);
                return 1;
            }
        }
    }

    if (inword) {
        __process_string(builder, buf, h);
    }

    *words = transfer_data(builder);
    del_StrArrayBuilder(builder);
    return 0;
}
