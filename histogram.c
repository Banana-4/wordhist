#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 100

int main() {
    bool inword = false;
    int c;
    int lengths[MAX];
    for (int i = 0; i < MAX; ++i) {
        lengths[i] = 0;
    }
    int i = -1;
    while ((c = getchar()) != EOF) {
        if (inword && (!isalpha(c) && !isdigit(c) && c != '\''))
            inword = false;
        else if ( inword == false && isalpha(c) ) {
            inword = true;
            if (++i == MAX)
                break;
        }
        if (inword) {
            lengths[i]++;
        }
    }
    printf("\n");
    int h = 0;

    for (int i = 0; (i < MAX) && (lengths[i] > 0); ++i) {
        h = h < lengths[i] ? lengths[i] : h;
    }

    while (h > 0) {
        for (int i = 0; (i < MAX) && (lengths[i] > 0); ++i) {
            if (lengths[i] >= h)
                printf(" # ");
            else
                printf("   ");
        }

        printf("\n");
        h--;
    }
}
