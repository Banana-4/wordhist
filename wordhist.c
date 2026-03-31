#include "include/input.h"
#include "include/histogram.h"
#include "include/memory.h"

#include <stdio.h>

int main() {
    Array *lengths = new_Array();
    if (!lengths) {
        return 1;
    }
    StrArray *words = new_StrArray();
    if (!words) {
        del_Array(lengths);
        return 1;
    }

    int h = 0;
    int signal = input_loop(words, lengths, &h);
    if (signal == 1) {
        fprintf(stderr, "Critical error exiting...\n");
        del_Array(lengths);
        del_StrArray(words);
        exit(signal);
    }
    histogram(words, lengths, h);
    del_Array(lengths);
    del_StrArray(words);
    return 0;
}
