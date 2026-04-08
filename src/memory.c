#include "../include/memory.h"
#include <stdlib.h>
#include <stdio.h>

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
    s->block = (char*)malloc(s->size);
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
    strs->block = (Str**)malloc(sizeof(Str*) * strs->size);
    if (!strs->block) {
        free(strs);
        return NULL;
    }
    return strs;
}

ERROR_CODES _grow_Array(Array *a) {
    if (!a)
        return NULL_ARGUMENT;
    size_t size = a->size * 2;
    int *new = realloc(a->block, sizeof(int) * size);
    if (!new) {
        return ALLOCATION_FAIL;
    }
    a->size = size;
    a->block = new;
    return ALL_GOOD;
}

ERROR_CODES _grow_Str(Str *s) {
    if (!s) {
        return NULL_ARGUMENT;
    }
    size_t size = s->size * 2;
    char *new = realloc(s->block, size);
    if (!new) {
        return ALLOCATION_FAIL;
    }
    s->size = size;
    s->block = new;
    return ALL_GOOD;
}

ERROR_CODES _grow_StrArray(StrArray *strs) {
    if (!strs) {
      return NULL_ARGUMENT;
    }
    size_t size = strs->size * 2;
    Str **new = realloc(strs->block, sizeof(Str*) * size);
    if (!new) {
        return ALLOCATION_FAIL;
    }
    strs->size = size;
    strs->block = new;
    return ALL_GOOD;
}

ERROR_CODES append_Array(Array *a, int n) {
    if (!a) {
        return NULL_ARGUMENT;
    }
    if (a->len + 1 > a->size) {
        if (_grow_Array(a) != ALL_GOOD) {
            return ALLOCATION_FAIL;
        }
    }
    a->block[a->len++] = n;
    return ALL_GOOD;
}

ERROR_CODES append_Str(Str *s, char c) {
    if (!s) {
        return NULL_ARGUMENT;
    }
    if (s->len + 1 >= s->size) {
        if (_grow_Str(s) != ALL_GOOD) {
            return ALLOCATION_FAIL;
        }
    }
    s->block[s->len++] = c;
    s->block[s->len] = '\0';
    return ALL_GOOD;
}

ERROR_CODES append_StrArray(StrArray *strs, Str *s) {
     if (!strs) {
        return NULL_ARGUMENT;
    }
    if (strs->len + 1 > strs->size) {
        if (_grow_StrArray(strs) != ALL_GOOD) {
            return ALLOCATION_FAIL;
        }
    }
    strs->block[strs->len++] = s;
    return ALL_GOOD;
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
    free(strs->block);
    free(strs);
}
