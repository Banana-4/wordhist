#include "../include/histogram.h"

void print_line(int len) {
  while (len--) {
        printf(" _ ");
    }
    printf("\n\n");
}

void vertical_histogram(StrArray *words, int h)
{
	int height = h;
	print_line(words->len);
    while (height--) {
        for (int i = 0; i < words->len; ++i) {
            if (words->block[i]->len >= height)
                printf(" # ");
            else {
                printf("   ");
            }
        }
            printf("\n");
    }
    print_line(words->len);
    for(int i = 0; i < h; ++i)
    {
        for(int j = 0; j < words->len; ++j)
        {
            if(words->block[j]->len > i)
                printf(" %c ", words->block[j]->block[i]);
            else
            	printf("   ");
        }
        printf("\n");
    }
}

void horizontal_histogram(StrArray *words, int h) {
	for( int i = 0; i < words->len; ++i) {
		printf(" %s  ", words->block[i]->block);
		int blanks = h - words->block[i]->len - 1;
		if (blanks > 0) {
			for(int i = 0; i < blanks; ++i)
				printf(" ");
		}
		printf("| ");
		for (int j = 0; j < words->block[i]->len; ++j)
			printf("#");
		printf("\n");
	}
}

void histogram(StrArray *words, int h, bool horizontal) {
    printf("Histogram:\n");
    if (horizontal)
    	horizontal_histogram(words, h);
    else
    	vertical_histogram(words, h);
}
