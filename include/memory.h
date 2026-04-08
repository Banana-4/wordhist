#pragma once
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 4

typedef enum {
  NO_ERR,
  MEM_ERR,
  DUP_ERR,
} MEM_ERRORS;

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
    Array **idxs;
    StrArray *strs;
}StrArrayBuilder;

Array *new_Array();
Str *new_Str();
StrArray *new_StrArray();
StrArrayBuilder *new_StrArrayBuilder();

bool append_Array(Array *a, int n);
bool append_Str(Str *s, char c);
bool append_StrArray(StrArray *strs, const Str *s);

MEM_ERRORS insert_StrArrayBuilder(StrArrayBuilder *b, const Str *s);
StrArray *transfer_data(StrArrayBuilder *b);

void del_Array(Array *a);
void del_Str(Str *s);
void del_StrArray(StrArray *str);
void del_StrArrayBuilder(StrArrayBuilder *b);
