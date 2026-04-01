#pragma once
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 8

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


typedef struct {
    size_t len;
    size_t size;
    StrArray **strs;
}HashMap;

Array *new_Array();
Str *new_Str();
StrArray *new_StrArray();
HashMap *new_HashMap();

bool append_Array(Array *a, int n);
bool append_Str(Str *s, char c);
bool append_StrArray(StrArray *strs, Str *s);

bool insert_HashMap(HashMap *m, Str *s);

void del_Array(Array *a);
void del_Str(Str *s);
void del_StrArray(StrArray *str);
void del_HashMap(HashMap *m);
