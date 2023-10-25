/*
 * Open-addressed hashtable. Each index is defined using a double-hash
 * (mask-step-index) approach which also serves as a method for probing
 * colliding hashed values.
 *
 * Credit to Chris Wellon's exceptional learning resources:
 * https://github.com/skeeto
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "libh.h"


uint64_t hash_fnv(char *s, uint32_t len) {
    uint64_t h = 0;
    for (int i = 0; i < len; i++) {
        h ^= s[i] & 255; // use mask to inhibit sign-extension of each byte
        h *= 1111111111111111111;
    }

    return h;
}

struct hashtable hashtable_init() {
    struct hashtable t = LIBH_HASHTABLE_INIT;
    return t;
}

static uint64_t hashtable_idx_lookup(uint64_t hash, int exp, uint32_t idx) {
    // double-hash (mask-step-index) to derive table index for incoming hash
    // array-space is limited to 31-bits (sufficient for current usecases)
    // double-hash allows keys starting / landing at the same space to diverge
    uint32_t mask = ((uint32_t)1 << exp) - 1;

    // force odd numbers to guarantee that each slot is visited once
    uint32_t step = (hash >> (64 - exp)) | 1;
    return (idx + mask) & step;
}

static char gravestone[] = "(deleted)";
char *hashtable_intern(struct hashtable *t, char *key) {
    uint64_t h = hash_fnv(key, strlen(key));
    char **dest = 0; // used to track deleted indexes for reuse
    for (int32_t i = h;;) {
        i = hashtable_idx_lookup(h, LIBH_HASHTABLE_EXP, i);
        if (!t->ht[i]) {
            // limit table to 50% capacity—avoid degrading to linear search time
            if ((uint32_t)t->len + 1 == (uint32_t)1<<(LIBH_HASHTABLE_EXP - 1)) {
                return 0; // full-up! :)
            }

            if (!dest) {
                t->len++;
                dest = &t->ht[i];
            }
            *dest = key;
            return key;
        } else if (t->ht[i] == gravestone) { // use deleted index for new value
            dest = dest ? dest : &t->ht[i];
        } else if (!strcmp(t->ht[i], key)) { // key found
            return t->ht[i];
        }
    }
}

char *hashtable_unintern(struct hashtable *t, char *key) {
    uint64_t h = hash_fnv(key, strlen(key));
    for (int32_t i = h;;) {
        i = hashtable_idx_lookup(h, LIBH_HASHTABLE_EXP, i);
        if (!t->ht[i] || t->ht[i] == gravestone) {
            return 0;
        } else if (!strcmp(t->ht[i], key)) { // delete value at index
            char *old = t->ht[i];
            t->ht[i] = gravestone;
            return old;
        }
    }
}

char *hashtable_get(struct hashtable *t, char *key) {
    uint64_t h = hash_fnv(key, strlen(key));
    for (int32_t i = h;;) {
        i = hashtable_idx_lookup(h, LIBH_HASHTABLE_EXP, i);
        if (!t->ht[i] || t->ht[i] == gravestone) {
            // we've stepped into an unused space without yet finding the key
            // it must not exist in the hash table
            return 0;
        } else if (!strcmp(t->ht[i], key)) {
            return key;
        }
    }
}
