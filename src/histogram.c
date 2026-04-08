#include "../include/histogram.h"

void print_line(int len) {
  while (len--) {
        printf(" _ ");
    }
    printf("\n\n");
}

void histogram(StrArray *words, int h) {
    printf(" Histogram:\n");
    print_line(words->len);
    while (h--) {
        for (int i = 0; i < words->len; ++i) {
            if (words->block[i]->len >= h)
                printf(" # ");
            else {
                printf("   ");
            }
        }
            printf("\n");
    }
    print_line(words->len);
    printf("\n Words List:\n");
    for (int i = 0; i < words->len; ++i) {
        printf(" %s : %zu\n", words->block[i]->block, words->block[i]->len);
    }
}
