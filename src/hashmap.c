#include "../include/memory.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

HashMap *new_HashMap() {
    HashMap *m = (HashMap *)malloc(sizeof(HashMap));
    if (!m) {
        return NULL;
    }
    m->size = SIZE;
    m->strs = (StrArray**)malloc(sizeof(StrArray*) * m->size);
    if (!m->strs) {
        free(m);
        return NULL;
    }
    for (int i = 0; i < m->size; ++i) {
        m->strs[i] = NULL;
    }
    m->len = 0;
    return m;
}



//AI generated hash function
unsigned long __hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
        // hash * 33 + c
    }
    return hash;
}

int __hash_Str(Str *s, size_t range) {
  return __hash(s->block) % range;
}

bool __grow_HashMap(HashMap *m) {
    if (!m)
        return false;
    StrArray **new = realloc(m->strs, sizeof(StrArray *) * m->size * 2);
    if (!new) {
        return false;
    }
    for (int i = 0; i < m->size * 2; ++i)
        new[i] = NULL;
    size_t oldSize = m->size;
    StrArray **oldStrs = m->strs;
    size_t oldLen = m->len;
    m->size = m->size * 2;
    m->strs = new;
    m->len = 0;
    for (int i = 0; i < oldSize; ++i) {
        StrArray *bucket = oldStrs[i];

        if (bucket != NULL) {
            printf("Buck: %zu \n", bucket->size);
            printf("Buck len: %zu", bucket->block[0]->size);
            for (int j = 0; j < bucket->len; ++j) {
              if (!insert_HashMap(m, bucket->block[j])) {
                  m->strs = oldStrs;
                  m->size = oldSize;
                  return false;
            }
          }

        }
    }
    return true;
}

bool insert_HashMap(HashMap *m, Str *s) {
    if (!m) {
        return false;
    }
    double load = (double)m->len / m->size;

    if (load >= 0) {
        __grow_HashMap(m);
    }
    int idx = __hash_Str(s, m->size);
    StrArray *bucket = m->strs[idx];

    if (bucket == NULL) {
        bucket = new_StrArray();
        if (!bucket)
            return false;
        m->strs[idx] = bucket;
    }
    for (int i = 0; i < bucket->len; ++i) {
        if (strcmp(s->block, bucket->block[i]->block) == 0) {
            return false;
        }

    }
    if (!append_StrArray(bucket, s)) {
            return false;
    }
    m->len++;
    return true;
}

bool has_HashMap(HashMap *m, Str *s) {
    int idx = __hash_Str(s, m->size);
    StrArray *bucket = m->strs[idx];
    if (bucket == NULL) {
        return false;
    }
    for (int i = 0; i < bucket->len; ++i) {
        if (strcmp(s->block, bucket->block[i]->block) == 0) {
            return true;
        }
    }
    return false;
}

void del_HashMap(HashMap *m) {
    if (!m)
        return;
    for(int i = 0; i < m->size; ++i)
        del_StrArray(m->strs[i]);
    free(m);
}
