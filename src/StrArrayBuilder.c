#include "../include/memory.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define LOAD 0.6

StrArrayBuilder *new_StrArrayBuilder() {
    StrArrayBuilder *b = (StrArrayBuilder*) malloc(sizeof(StrArrayBuilder));
    if (!b) {
        return NULL;
    }
    b->size = SIZE;
    b->strs = new_StrArray();

    if (!b->strs) {
        free(b);
        return NULL;
    }

    b->idxs = (Array **)malloc(sizeof(Array *) * b->size);
    if (!b->idxs) {
        del_StrArray(b->strs);
        return NULL;
    }
    for (int i = 0; i < b->size; ++i) {
        b->idxs[i] = NULL;
    }
    b->len = 0;
    return b;
}


//////////////////////////////
// AI generated hash function
/////////////////////////////

unsigned long _hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
        // hash * 33 + c
    }
    return hash;
}

int _hash_Str(const Str *s, size_t range) {
  return _hash(s->block) % range;
}

ERROR_CODES _grow_HashMap(StrArrayBuilder *b) {
    if (!b)
        return NULL_ARGUMENT;
    size_t new_size = b->size * 2;
    Array **new_idxs = (Array**)malloc(sizeof(Array *) * new_size);
    if (!new_idxs) {
        return ALLOCATION_FAIL;
    }
    for (int i = 0; i < new_size; ++i)
        new_idxs[i] = NULL;

    //////////////////////////
    // Rehashing
    //////////////////////////

    for (int i = 0; i < b->len; ++i) {
        int idx = _hash_Str(b->strs->block[i], new_size);
        if (!new_idxs[idx]) {
            Array *bucket = new_Array();
            if (!bucket) {
               goto grow_cleanup;
            }
            new_idxs[idx] = bucket;
        }

        if (append_Array(new_idxs[idx], i) != ALL_GOOD) {
            goto grow_cleanup;
        }
    }

    //////////////////////////
    // Old memory cleanup
    /////////////////////////

    for (int i = 0; i < b->size; ++i) {
        del_Array(b->idxs[i]);
    }
    free(b->idxs);
    b->idxs = new_idxs;
    b->size = new_size;
    return ALL_GOOD;

    //////////////////////////
    // Error Handling
    /////////////////////////

    grow_cleanup:
        for (int i = 0; i < new_size; ++i)
            del_Array(new_idxs[i]);
        free(new_idxs);
        return ALLOCATION_FAIL;
}


ERROR_CODES insert_StrArrayBuilder(StrArrayBuilder *b, Str *s) {

    ////////////////////////////
    // If inserted s is owned by StrArrayBuilder, until than it is owned by the calling function
    ////////////////////////////

    if (!b) {
        return NULL_ARGUMENT;
    }

    double load = (double)b->len / b->size;

    if (load >= LOAD) {
        if (_grow_HashMap(b) != ALL_GOOD)
            return ALLOCATION_FAIL;
    }

    int idx = _hash_Str(s, b->size);
    Array *bucket = b->idxs[idx];

    //////////////////////
    // create new bucket if needed
    /////////////////////

    if (bucket == NULL) {
        bucket = new_Array();
        if (!bucket)
            return ALLOCATION_FAIL;
        b->idxs[idx] = bucket;
    }

    /////////////////////////
    // Enforce unique strings
    /////////////////////////

    for (int i = 0; i < bucket->len; ++i) {
        int idx = bucket->block[i];
        if (strcmp(s->block, b->strs->block[idx]->block) == 0) {
            return DUPLICATE_STRING;
        }
    }

    if (append_StrArray(b->strs, s) != ALL_GOOD) {
            return ALLOCATION_FAIL;
    }

    if (append_Array(bucket, b->strs->len - 1) != ALL_GOOD) {
        --b->strs->len;
        b->strs->block[b->strs->len] = NULL;
        return ALLOCATION_FAIL;
    }
    b->len++;
    return ALL_GOOD;
}

StrArray *transfer_data(StrArrayBuilder *b) {
    if (!b) {
        return NULL;
    }
    StrArray *data = b->strs;

    //////////////////////////////////////
    // Ensure safe destruction of builder
    //////////////////////////////////////

    b->strs = NULL;
    return data;
}

void del_StrArrayBuilder(StrArrayBuilder *b) {
    if (!b)
        return;
    for (int i = 0; i < b->size; ++i) {
        del_Array(b->idxs[i]);
    }
    del_StrArray(b->strs);
    free(b->idxs);
    free(b);
}
