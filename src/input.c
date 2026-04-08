#include "../include/input.h"
#include <memory.h>

bool _sab_process_string(StrArrayBuilder *builder, Str **str, int *h) {
    MEM_ERRORS err = insert_StrArrayBuilder(builder, *str);
    if(err == NO_ERR) {
        if (*h < (*str)->len) {
            *h = (*str)->len;
        }
        str = NULL;
        return true;
    } else if (err == MEM_ERR){
        del_Str(*str);
        *str = NULL;
        return false;
    } else if (err == DUP_ERR) {
        del_Str(*str);
        *str = NULL;
    }
    return true;
}

INP_ERR input_loop(StrArray **words, int *h) {
    bool inword = false;
    *h = 0;
    Str *buf = NULL;
    int c;
    StrArrayBuilder *builder = new_StrArrayBuilder();
    if (!builder) {
        return INP_MEM_FAIL;
    }

    while ((c = getchar()) != EOF) {
        if (inword && (!isalpha(c) && !isdigit(c) && c != '\'')) {
            inword = false;
            if (!_sab_process_string(builder, &buf, h)) {
                del_StrArrayBuilder(builder);
                return INP_MEM_FAIL;
            }
        }

        else if (inword == false && isalpha(c)) {
            inword = true;
            buf = new_Str();
            if (!buf) {
                del_StrArrayBuilder(builder);
                return INP_MEM_FAIL;
            }
        }
        if (inword) {
            if (!append_Str(buf, c)) {
                del_StrArrayBuilder(builder);
                del_Str(buf);
                return INP_MEM_FAIL;
            }
        }
    }

    if (inword) {
        if (!_sab_process_string(builder, &buf, h)) {
            del_StrArrayBuilder(builder);
            return INP_MEM_FAIL;
      }
    }

    *words = transfer_data(builder);
    del_StrArrayBuilder(builder);
    return INP_NO_ERR;
}
