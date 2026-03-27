#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int input_loop(char **words, const size_t MAX_WORD, int *lens, const size_t MAX, int *h);
void del_words(char **words, const size_t len);
