#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    size_t len;
    size_t size;
    int *block;
}Array;

typedef struct {
    size_t len;
    size_t size;
    char *block;
}Str;

Array *new_Array();
Str *new_Str();

bool append_Array(Array *a, int n);
bool append_Str(Str *s, char c);
void del_Array(Array *a);
void del_Str(Str *s);
