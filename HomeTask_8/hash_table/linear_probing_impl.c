// linear_probing_impl.c
#include "hash_table.h"
#include "../hash/item.h"
#include "../hash/hash_code.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    Key  *keys;
    int    size;
    int    capacity;
} KeyList;

typedef struct {
    Key   key;
    Item  value;
} Entry;

struct HashTable {
    Entry  *entries;
    int     capacity;
    int     size;

    bool         enable_prefix;
    HashTablePtr prefixIndex;  
};

static const int INITIAL_CAPACITY = 97;
static const int KEYLIST_INITIAL = 4;

static KeyList *KeyListCreate(void) {
    KeyList *kl = malloc(sizeof(*kl));
    if (!kl) return NULL;
    kl->size = 0;
    kl->capacity = KEYLIST_INITIAL;
    kl->keys = malloc(sizeof(Key) * kl->capacity);
    if (!kl->keys) { free(kl); return NULL; }
    return kl;
}

static bool KeyListAdd(KeyList *kl, Key k) {
    if (kl->size >= kl->capacity) {
        int nc = kl->capacity * 2;
        Key *tmp = realloc(kl->keys, sizeof(Key) * nc);
        if (!tmp) return false;
        kl->keys = tmp;
        kl->capacity = nc;
    }
    kl->keys[kl->size++] = k;
    return true;
}

static HashTablePtr HashTableCreate(bool with_prefix);

HashTablePtr HashTableInit() {
    return HashTableCreate(true);
}

static HashTablePtr HashTableCreate(bool with_prefix) {
    HashTablePtr ht = malloc(sizeof(*ht));
    if (!ht) return NULL;
    ht->capacity = INITIAL_CAPACITY;
    ht->size     = 0;
    ht->entries  = calloc(ht->capacity, sizeof(Entry));
    if (!ht->entries) { free(ht); return NULL; }

    ht->enable_prefix = with_prefix;
    if (with_prefix) {
        ht->prefixIndex = HashTableCreate(false);
        if (!ht->prefixIndex) {
            free(ht->entries);
            free(ht);
            return NULL;
        }
    } else {
        ht->prefixIndex = NULL;
    }
    return ht;
}

bool HashTablePut(HashTablePtr ht, Key key, Item value) {
    if (!ht || !key || !value) return false;

    if (ht->size + 1 > ht->capacity / 2) {
        int new_cap = ht->capacity * 2;
        Entry *old_arr = ht->entries;
        int   old_cap = ht->capacity;

        Entry *arr = calloc(new_cap, sizeof(Entry));
        if (!arr) { }
        else {
            ht->entries = arr;
            ht->capacity = new_cap;
            ht->size = 0;

            for (int i = 0; i < old_cap; i++) {
                if (old_arr[i].key) {

                    int idx = hash(old_arr[i].key, ht->capacity);
                    while (ht->entries[idx].key)
                        idx = (idx + 1) % ht->capacity;
                    ht->entries[idx].key   = old_arr[i].key;
                    ht->entries[idx].value = old_arr[i].value;
                    ht->size++;
                }
            }
            free(old_arr);
        }
    }

    int idx = hash(key, ht->capacity);
    while (ht->entries[idx].key) {
        if (equal(key, ht->entries[idx].key)) {
            ht->entries[idx].value = value;
            return true;
        }
        idx = (idx + 1) % ht->capacity;
    }

    Key copy = strdup(key);
    if (!copy) return false;
    ht->entries[idx].key   = copy;
    ht->entries[idx].value = value;
    ht->size++;

    if (ht->enable_prefix) {
        int L = strlen(copy);
        for (int plen = 1; plen <= L; plen++) {
            char *pref = strndup(copy, plen);
            if (!pref) continue;  

            KeyList *kl = (KeyList*)HashTableGet(ht->prefixIndex, pref);
            if (!kl) {
                kl = KeyListCreate();
                if (kl) {
                    HashTablePut(ht->prefixIndex, pref, (Item)kl);
                }
            }
            if (kl) {
                KeyListAdd(kl, ht->entries[idx].key);
            }
            free(pref);
        }
    }

    return true;
}

Item HashTableGet(HashTablePtr ht, Key key) {
    if (!ht || !key) return NULL;
    int idx = hash(key, ht->capacity);
    while (ht->entries[idx].key) {
        if (equal(key, ht->entries[idx].key))
            return ht->entries[idx].value;
        idx = (idx + 1) % ht->capacity;
    }
    return NULL;
}

Key **HashTablePrefixSearch(HashTablePtr ht,
                            const char *prefix,
                            int *result_size)
{
    if (!ht || !prefix || !result_size) return NULL;
    *result_size = 0;
    if (!ht->enable_prefix || !ht->prefixIndex) return NULL;

    KeyList *kl = (KeyList*)HashTableGet(ht->prefixIndex, prefix);
    if (!kl || kl->size == 0) return NULL;

    Key **out = malloc(sizeof(*out) * kl->size);
    if (!out) { *result_size = 0; return NULL; }

    for (int i = 0; i < kl->size; i++) {
        out[i] = strdup(kl->keys[i]);
        if (!out[i]) {

            for (int j = 0; j < i; j++) free(out[j]);
            free(out);
            *result_size = 0;
            return NULL;
        }
    }
    *result_size = kl->size;
    return out;
}

void HashTablePrint(const HashTablePtr ht,
                    const char *type,
                    bool print_empty)
{
    for (int i = 0; i < ht->capacity; i++) {
        if (!ht->entries[i].key) {
            if (print_empty) printf("%d: NULL\n", i);
        } else {
            printf("%d:", i);
            if (strcmp(type, "int") == 0) {
                printf("%d", (int)(intptr_t)ht->entries[i].value);
            } else if (strcmp(type, "char") == 0) {
                printf("'%c'", *(char *)ht->entries[i].value);
            } else if (strcmp(type, "string") == 0) {
                printf("\"%s\"", (char *)ht->entries[i].value);
            } else {
                printf("UNKNOWN_TYPE");
            }
            printf("\n");
        }
    }
}

void HashTableDestroy(HashTablePtr ht) {
    if (!ht) return;

    if (ht->enable_prefix && ht->prefixIndex) {
        HashTableDestroy(ht->prefixIndex);
    }

    for (int i = 0; i < ht->capacity; i++) {
        if (ht->entries[i].key) {
            free(ht->entries[i].key);
            if (!ht->enable_prefix) {
                KeyList *kl = (KeyList*)ht->entries[i].value;
                free(kl->keys);
                free(kl);
            }
        }
    }
    free(ht->entries);
    free(ht);
}
