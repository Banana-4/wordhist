#include "../include/memory.h"
#include <stdlib.h>
#include <stdio.h>
#define SIZE 8

Array *new_Array() {
    Array *a = (Array *)malloc(sizeof(Array));
    if (!a) {
        return NULL;
    }
    a->size = SIZE;
    a->len = 0;
    a->block = (int*)malloc(sizeof(int) * a->size);
    if (!a->block) {
        free(a);
        return NULL;
    }
    return a;
}

Str *new_Str() {
    Str *s = (Str*)malloc(sizeof(Str));
    if (!s) {
        return NULL;
    }
    s->size = SIZE;
    s->len = 0;
    s->block = (char*)malloc(sizeof(int) * s->size);
    if (!s->block) {
        free(s);
        return NULL;
    }
    return s;
}

StrArray *new_StrArray() {
    StrArray *strs = (StrArray*)malloc(sizeof(StrArray));
    if (!strs) {
        return NULL;
    }
    strs->size = SIZE;
    strs->len = 0;
    strs->block = (Str**)malloc(sizeof(Str) * strs->size);
    if (!strs->block) {
        free(strs);
        return NULL;
    }
    return strs;
}

bool __grow_Array(Array *a) {
    size_t size = a->size * 2;
    int *new = realloc(a->block, sizeof(int) * size);
    if (!new) {
        return false;
    }
    a->size = size;
    a->block = new;
    return true;
}

bool __grow_Str(Str *s) {
    size_t size = s->size * 2;
    char *new = realloc(s->block, size);
    if (!new) {
        return false;
    }
    s->size = size;
    s->block = new;
    return true;
}

bool __grow_StrArray(StrArray *strs) {
    size_t size = strs->size * 2;
    Str **new = realloc(strs->block, sizeof(Str) * size);
    if (!new) {
        return false;
    }
    strs->size = size;
    strs->block = new;
    return true;
}

bool append_Array(Array *a, int n) {
    if (!a) {
        return false;
    }
    if (a->len + 1 > a->size) {
        if (!__grow_Array(a)) {
            return false;
        }
    }
    a->block[a->len++] = n;
    return true;
}

bool append_Str(Str *s, char c) {
    if (!s) {
        return false;
    }
    if (s->len + 1 >= s->size) {
        if (!__grow_Str(s)) {
            return false;
        }
    }
    s->block[s->len++] = c;
    s->block[s->len] = '\0';
    return true;
}

bool append_StrArray(StrArray *strs, Str *s) {
     if (!strs) {
        return false;
    }
    if (strs->len + 1 > strs->size) {
        if (!__grow_StrArray(strs)) {
            return false;
        }
    }
    strs->block[strs->len++] = s;
    return true;
}

void del_Array(Array *a) {
    if (!a) {
      return;
    }
    free(a->block);
    free(a);
    a = NULL;
}

void del_Str(Str *s) {
    if (!s) {
        return;
    }
    free(s->block);
    free(s);
}

void del_StrArray(StrArray *strs) {
    if (!strs) {
        return;
    }
    for (int i = 0; i < strs->len; ++i) {
        del_Str(strs->block[i]);
    }
    free(strs);
}
