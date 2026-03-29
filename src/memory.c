#include "../include/memory.h"
#include <stdlib.h>
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

bool __grow_Array(Array *a) {
    a->size = a->size * 2;
    int *new = realloc(a->block, a->size);
    if (!new) {
        return false;
    }
    a->block = new;
    return true;
}

bool __grow_Str(Str *s) {
    s->size = s->size * 2;
    char *new = realloc(s->block, s->size);
    if (!new) {
        return false;
    }
    s->block = new;
    return true;
}

bool append_Array(Array *a, int n) {
    if (!a) {
        return false;
    }
    if (++a->len == a->size) {
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
    if (++s->len == s->size - 1) {
        if (!__grow_Str(s)) {
            return false;
        }
    }
    s->block[s->len++] = c;
    s->block[s->len] = '\0';
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
