#include "../include/input.h"
#include <memory.h>

ERROR_CODES _sab_process_string(StrArrayBuilder *builder, Str **str, int *h) {
    ERROR_CODES signal = insert_StrArrayBuilder(builder, *str);
    if(signal == ALL_GOOD) {
        if (*h < (*str)->len) {
            *h = (*str)->len;
        }
        str = NULL;
    } else if (signal == ALLOCATION_FAIL){
        del_Str(*str);
        *str = NULL;
        return ALLOCATION_FAIL;
    } else if (signal == DUPLICATE_STRING) {
        del_Str(*str);
        *str = NULL;
    }
    return ALL_GOOD;
}

ERROR_CODES input_loop(StrArray **words, int *h) {
    bool inword = false;
    *h = 0;
    Str *buf = NULL;
    int c;
    StrArrayBuilder *builder = new_StrArrayBuilder();
    if (!builder) {
        return ALLOCATION_FAIL;
    }

    while ((c = getchar()) != EOF) {
        if (inword && (!isalpha(c) && !isdigit(c) && c != '\'')) {
            inword = false;
            if (_sab_process_string(builder, &buf, h) != ALL_GOOD) {
                del_StrArrayBuilder(builder);
                return ALLOCATION_FAIL;
            }
        }

        else if (inword == false && isalpha(c)) {
            inword = true;
            buf = new_Str();
            if (!buf) {
                del_StrArrayBuilder(builder);
                return ALLOCATION_FAIL;
            }
        }
        if (inword) {
            if (append_Str(buf, c) != ALL_GOOD) {
                del_StrArrayBuilder(builder);
                del_Str(buf);
                return ALLOCATION_FAIL;
            }
        }
    }

    if (inword) {
        if (_sab_process_string(builder, &buf, h) != ALL_GOOD) {
            del_StrArrayBuilder(builder);
            return ALLOCATION_FAIL;
      }
    }

    *words = transfer_data(builder);
    del_StrArrayBuilder(builder);
    return ALL_GOOD;
}
