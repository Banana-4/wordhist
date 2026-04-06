#include "../include/memory.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define LOAD 0.6

HashMap *new_HashMap() {
    HashMap *m = (HashMap *)malloc(sizeof(HashMap));
    if (!m) {
        return NULL;
    }
    m->size = SIZE;
    m->strs = new_StrArray();

    if (!m->strs) {
        free(m);
        return NULL;
    }

    m->idxs = (Array **)malloc(sizeof(Array *) * m->size);
    if (!m->idxs) {
        del_StrArray(m->strs);
        return NULL;
    }
    for (int i = 0; i < m->size; ++i) {
        m->idxs[i] = NULL;
    }
    m->len = 0;
    return m;
}


//////////////////////////////
// AI generated hash function
/////////////////////////////

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
    size_t new_size = m->size * 2;
    Array **new_idxs = (Array**)malloc(sizeof(Array *) * new_size);
    if (!new_idxs) {
        return false;
    }
    for (int i = 0; i < new_size; ++i)
        new_idxs[i] = NULL;

    //////////////////////////
    // Rehashing
    //////////////////////////

    for (int i = 0; i < m->len; ++i) {
        int idx = __hash_Str(m->strs->block[i], new_size);
        if (!new_idxs[idx]) {
            Array *bucket = new_Array();
            if (!bucket) {
               goto grow_cleanup;
            }
            new_idxs[idx] = bucket;
        }

        if (!append_Array(new_idxs[idx], i)) {
            goto grow_cleanup;
        }
    }

    //////////////////////////
    // Old memory cleanup
    /////////////////////////

    for (int i = 0; i < m->size; ++i) {
        del_Array(m->idxs[i]);
    }
    free(m->idxs);
    m->idxs = new_idxs;
    m->size = new_size;
    return true;

    //////////////////////////
    // Error Handling
    /////////////////////////

    grow_cleanup:
        for (int i = 0; i < new_size; ++i)
            del_Array(new_idxs[i]);
        free(new_idxs);
        return false;
}


bool insert_HashMap(HashMap *m, Str *s) {
    if (!m) {
        return false;
    }
    double load = (double)m->len / m->size;

    if (load >= LOAD) {
        if (!__grow_HashMap(m))
            return false;
    }

    int idx = __hash_Str(s, m->size);
    Array *bucket = m->idxs[idx];

    if (bucket == NULL) {
        bucket = new_Array();
        if (!bucket)
            return false;
        m->idxs[idx] = bucket;
    }
    for (int i = 0; i < bucket->len; ++i) {
        int idx = bucket->block[i];
        if (strcmp(s->block, m->strs->block[idx]->block) == 0) {
            return false;
        }

    }
    if (!append_StrArray(m->strs, s)) {
            return false;
    }

    if (!append_Array(bucket, m->strs->len - 1)) {
        --m->strs->len;
        del_Str(m->strs->block[m->len]);
        return false;
    }
    m->len++;
    return true;
}

StrArray *transfer_data(HashMap *m) {
    if (!m) {
        return NULL;
    }
    StrArray *data = m->strs;
    m->strs = NULL;
    return data;
}

void del_HashMap(HashMap *m) {
    if (!m)
        return;
    for (int i = 0; i < m->size; ++i) {
        del_Array(m->idxs[i]);
    }
    del_StrArray(m->strs);
    free(m->idxs);
    free(m);
}
