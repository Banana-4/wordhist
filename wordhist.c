#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100
#define MAX_WORD 40
int main() {
    bool inword = false;
    int c;
    int lengths[MAX];
    char *words[MAX];
    char *buffer = NULL;
    int bp;

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
            buffer[bp] = '\0';
            words[i] = buffer;
        }
        else if ( inword == false && isalpha(c) ) {
            inword = true;
            if (++i == MAX)
                break;
            bp = 0;
            buffer = malloc(MAX_WORD);
            if (!buffer) {
                fprintf(stderr, "Can not create string buffer exiting.\n");
                exit(1);
            }
        }
        if (inword) {
            lengths[i]++;
            buffer[bp++] = c;
            if (bp == MAX_WORD - 1) {
                fprintf(stderr, "Word too long, exiting.\n");
                exit(1);
            }
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
    printf("\n Words:\n");
    for (int j = 0; j <= i; ++j) {
        printf(" %s : %d\n", words[j], lengths[j]);

    }
}
