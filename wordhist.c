#include "include/input.h"
#include "include/histogram.h"
#include <stdio.h>
#define MAX 100
#define MAX_WORD 40

int main() {
    int lengths[MAX];
    char *words[MAX];
    int h = 0;
    int len = input_loop(words, MAX_WORD, lengths, MAX, &h);
    if (len == -1) {
        fprintf(stderr, "Critical error exiting...\n");
        exit(1);
    }
    histogram(words, lengths, len, h);
    del_words(words, len);
    return 0;
}
