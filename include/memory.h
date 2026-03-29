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

typedef struct {
    size_t len;
    size_t size;
    Str **block;
} StrArray;

Array *new_Array();
Str *new_Str();
StrArray *new_StrArray();

bool append_Array(Array *a, int n);
bool append_Str(Str *s, char c);
bool append_StrArray(StrArray *strs, Str *s);
void del_Array(Array *a);
void del_Str(Str *s);
void del_StrArray(StrArray *str);
