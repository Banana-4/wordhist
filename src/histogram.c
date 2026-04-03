#include "../include/histogram.h"

void histogram(StrArray *words, int h) {
    printf("\n");
    while (h > 0) {
        for (int i = 0; i < words->len; ++i) {
            if (words->block[i]->len >= h)
                printf(" # ");
            else
                printf("   ");
        }
        printf("\n");
        h--;
    }
    printf("\n Words:\n");
    for (int i = 0; i < words->len; ++i) {
        printf(" %s : %zu\n", words->block[i]->block, words->block[i]->len);
    }
}
