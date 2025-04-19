#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../hash_table.h"

void test_HashTablePutGet() {
    HashTablePtr ht = HashTableInit();
    assert(ht != NULL);

    HashTablePut(ht, "key", (Item)(intptr_t)42);
    Item value = HashTableGet(ht, "key");

    assert((int)(intptr_t)value == 42);

    HashTableDestroy(ht);
}


void test_HashTableOverwriteValue() {
    HashTablePtr ht = HashTableInit();
    assert(ht != NULL);

    HashTablePut(ht, "same_key", (Item)(intptr_t)10);
    HashTablePut(ht, "same_key", (Item)(intptr_t)99); // Overwrite

    Item value = HashTableGet(ht, "same_key");
    assert((int)(intptr_t)value == 99);

    HashTableDestroy(ht);
}


void test_HashTableManyKeys() {
    HashTablePtr ht = HashTableInit();
    assert(ht != NULL);

    for (int i = 0; i < 50; i++) {
        char key[10];
        sprintf(key, "k%d", i);
        HashTablePut(ht, key, (Item)(intptr_t)(i * 2));
    }

    for (int i = 0; i < 50; i++) {
        char key[10];
        sprintf(key, "k%d", i);
        Item value = HashTableGet(ht, key);
        assert((int)(intptr_t)value == i * 2);
    }

    HashTableDestroy(ht);
}


void test_HashTableCaseSensitivity() {
    HashTablePtr ht = HashTableInit();
    assert(ht != NULL);

    HashTablePut(ht, "Key", (Item)(intptr_t)1);
    HashTablePut(ht, "key", (Item)(intptr_t)2);

    Item val1 = HashTableGet(ht, "Key");
    Item val2 = HashTableGet(ht, "key");

    assert((int)(intptr_t)val1 == 1);
    assert((int)(intptr_t)val2 == 2);

    HashTableDestroy(ht);
}


void test_HashTableStressMemory() {
    HashTablePtr ht = HashTableInit();
    assert(ht != NULL);

    const int COUNT = 1000;
    for (int i = 0; i < COUNT; i++) {
        char key[20];
        sprintf(key, "item_%d", i);
        HashTablePut(ht, key, (Item)(intptr_t)(i + 1000));
    }

    for (int i = 0; i < COUNT; i++) {
        char key[20];
        sprintf(key, "item_%d", i);
        Item value = HashTableGet(ht, key);
        assert((int)(intptr_t)value == i + 1000);
    }

    HashTableDestroy(ht);
}


void run_all_tests() {
    printf("Running tests...\n");

    // Test inserting and retrieving a single key-value pair
    test_HashTablePutGet();

    // Test inserting the same key twice with different values (should overwrite)
    test_HashTableOverwriteValue();

    // Test inserting many different keys and retrieving them
    test_HashTableManyKeys();

    // Test how the table handles case differences in keys
    test_HashTableCaseSensitivity();

    // Stress test: insert many entries and check memory and correctness
    test_HashTableStressMemory();

    printf("All tests passed!\n");
}

int main(int , char *[]) {
    run_all_tests();
    return 0;
}
