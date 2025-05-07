//hash_table.h
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "../hash/item.h"
#include <stdbool.h>

typedef struct HashTable *HashTablePtr;

HashTablePtr HashTableInit();
bool HashTablePut(HashTablePtr, Key, Item);
Item HashTableGet(HashTablePtr, Key);
void HashTablePrint(const HashTablePtr ht, const char *type, bool print_empty);
void HashTableDestroy(HashTablePtr);

// Function: HashTablePrefixSearch
// -------------------------------
// Searches the hash table for all keys that start with the given prefix.
//
// Parameters:
// ht: Pointer to the hash table.
// prefix: The prefix string to match (e.g., "bana").
// result_size: Output parameter. Will be set to the number of matched keys.
//
// Returns:
// A dynamically allocated array of Key (strings) that match the prefix.
// Each string in the array is also dynamically allocated and should be freed by the caller.
// If no matches are found or a memory allocation fails, returns NULL and sets *result_size to 0.
Key **HashTablePrefixSearch(HashTablePtr ht, const char *prefix, int *result_size);


#endif // #define HASH_TABLE_H