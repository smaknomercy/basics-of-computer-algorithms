#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Deque* DequePtr;
typedef void* Item;

DequePtr DequeInit();                           // Initialize the deque
int DequeEmpty(DequePtr deque);                 // Check if the deque is empty
size_t DequeSize(DequePtr deque);               // Get the size of the deque
void DequeAddFirst(DequePtr deque, Item item);  // Add item to the front
void DequeAddLast(DequePtr deque, Item item);   // Add item to the back
Item DequeRemoveFirst(DequePtr deque);          // Remove item from the front
Item DequeRemoveLast(DequePtr deque);           // Remove item from the back
void DequeDestroy(DequePtr deque);              // Destroy the deque and free memory

#ifdef __cplusplus
}
#endif

#endif