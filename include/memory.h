#pragma once
#include "error_codes.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define SIZE 4

typedef struct {
    size_t len;
    size_t size;
    int *block;
}Array;

typedef struct {
    size_t len;
    size_t size;
    char *c_str;
}Str;

typedef struct {
    size_t len;
    size_t size;
    Str **strs;
} StrArray;


typedef struct {
    size_t len;
    size_t size;
    Array **idxs;
    StrArray *strs;
}StrArrayBuilder;

Array *new_Array();
Str *new_Str();
StrArray *new_StrArray();
StrArrayBuilder *new_StrArrayBuilder();

ERROR_CODES append_Array(Array *a, int n);
ERROR_CODES append_Str(Str *s, char c);
ERROR_CODES append_StrArray(StrArray *strs, Str *s);

ERROR_CODES insert_StrArrayBuilder(StrArrayBuilder *b, Str *s);
StrArray *transfer_data(StrArrayBuilder *b);

Str* at_StrArray(const StrArray *strs, size_t i);
const char* c_str(const Str* str);

void del_Array(Array *a);
void del_Str(Str *s);
void del_StrArray(StrArray *str);
void del_StrArrayBuilder(StrArrayBuilder *b);
