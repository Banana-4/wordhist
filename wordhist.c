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
    int h = 0;
    // read loop
    while ((c = getchar()) != EOF) {
        if (inword && (!isalpha(c) && !isdigit(c) && c != '\'')) {
            inword = false;
            h = h < lengths[i] ? lengths[i] : h;
        }
        else if ( inword == false && isalpha(c) ) {
            inword = true;
            if (++i == MAX)
                break;
        }
        if (inword) {
            lengths[i]++;
        }
    }
    //separate the output from input with a new line
    printf("\n");

    // Output histogram
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
