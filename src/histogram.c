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
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < words->len; ++j) {
            if(words->block[j]->len > i)
                printf(" %c ", words->block[j]->block[i]);
            else
            	printf("   ");
        }
        printf("\n");
    }
}
