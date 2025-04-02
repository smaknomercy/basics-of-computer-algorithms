#include "Deque.h"
#include <stdlib.h>

struct Deque {
    Item *array;
    size_t size;
    size_t capacity;
    size_t front;
    size_t back;
};

// Initialize a new deque
DequePtr DequeInit() {
    DequePtr deque = (DequePtr)malloc(sizeof(struct Deque));
    if (deque == NULL) return NULL;

    deque->capacity = 2;
    deque->size = 0;
    deque->front = 0;
    deque->back = 0;
    deque->array = (Item*)malloc(deque->capacity * sizeof(Item));
    
    if (deque->array == NULL) {
        free(deque);
        return NULL;
    }
    return deque;
}

// Check if the deque is empty
int DequeEmpty(DequePtr deque) {
    return deque->size == 0;
}

// Get the size of the deque
size_t DequeSize(DequePtr deque) {
    return deque->size;
}

// Resize the internal array
void DequeResize(DequePtr deque, size_t new_capacity) {
    Item* new_array = (Item*)malloc(new_capacity * sizeof(Item));
    if (new_array == NULL) return;

    for (size_t i = 0; i < deque->size; i++) {
        new_array[i] = deque->array[(deque->front + i) % deque->capacity];
    }

    free(deque->array);
    deque->array = new_array;
    deque->front = 0;
    deque->back = deque->size;
    deque->capacity = new_capacity;
}

// Add item to the front
void DequeAddFirst(DequePtr deque, Item item) {
    if (deque->size == deque->capacity) {
        DequeResize(deque, 2 * deque->capacity);
    }
    
    deque->front = (deque->front - 1 + deque->capacity) % deque->capacity;
    deque->array[deque->front] = item;
    deque->size++;
}

// Add item to the back
void DequeAddLast(DequePtr deque, Item item) {
    if (deque->size == deque->capacity) {
        DequeResize(deque, 2 * deque->capacity);
    }

    deque->array[deque->back] = item;
    deque->back = (deque->back + 1) % deque->capacity;
    deque->size++;
}

// Remove item from the front
Item DequeRemoveFirst(DequePtr deque) {
    if (DequeEmpty(deque)) return NULL;

    Item item = deque->array[deque->front];
    deque->front = (deque->front + 1) % deque->capacity;
    deque->size--;

    if (deque->size > 0 && deque->size == deque->capacity / 4) {
        DequeResize(deque, deque->capacity / 2);
    }

    return item;
}

// Remove item from the back
Item DequeRemoveLast(DequePtr deque) {
    if (DequeEmpty(deque)) return NULL;

    deque->back = (deque->back - 1 + deque->capacity) % deque->capacity;
    Item item = deque->array[deque->back];
    deque->size--;

    if (deque->size > 0 && deque->size == deque->capacity / 4) {
        DequeResize(deque, deque->capacity / 2);
    }

    return item;
}

// Destroy the deque and free memory
void DequeDestroy(DequePtr deque) {
    free(deque->array);
    free(deque);
}