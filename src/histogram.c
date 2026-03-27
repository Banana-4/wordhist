#include "../include/histogram.h"

void histogram(char **words, const int *lens, const size_t MAX, int h) {
    printf("\n");
    while (h > 0) {
        for (int i = 0; (i < MAX) && (lens[i] > 0); ++i) {
            if (lens[i] >= h)
                printf(" # ");
            else
                printf("   ");
        }
        printf("\n");
        h--;
    }
    printf("\n Words:\n");
    for (int j = 0; j <= MAX; ++j) {
        printf(" %s : %d\n", words[j], lens[j]);
    }
}
