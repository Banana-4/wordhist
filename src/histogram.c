#include "../include/histogram.h"

void histogram(StrArray *words, Array *lens, int h) {
    printf("\n");
    while (h > 0) {
        for (int i = 0; i < words->len; ++i) {
            if (lens->block[i] >= h)
                printf(" # ");
            else
                printf("   ");
        }
        printf("\n");
        h--;
    }
    printf("\n Words:\n");
    for (int i = 0; i < words->len; ++i) {
        printf(" %s : %d\n", words->block[i]->block, lens->block[i]);
    }
}
