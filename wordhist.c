#include "include/input.h"
#include "include/histogram.h"
#include "include/memory.h"

#include <stdio.h>

int main() {
    StrArray *words = new_StrArray();
    if (!words) {
        return 1;
    }
    int h = 0;
    int signal = input_loop(&words, &h);
    if (signal == 1) {
        fprintf(stderr, "Critical error exiting...\n");
        del_StrArray(words);
        exit(signal);
    }
    histogram(words, h);
    del_StrArray(words);
    return 0;
}
