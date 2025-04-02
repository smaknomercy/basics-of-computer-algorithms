#include "RandomizedQueue.h"
#include <stdlib.h>
#include <time.h>

struct RandomizedQueue {
    Item* array;        // Array to store items
    size_t size;        // Current number of elements
    size_t capacity;    // Capacity of the array
};

// Initialize an empty randomized queue
RandomizedQueuePtr RandomizedQueueInit() {
    RandomizedQueuePtr rq = (RandomizedQueuePtr)malloc(sizeof(RandomizedQueue));
    if (!rq) return NULL;

    rq->capacity = 2;
    rq->size = 0;
    rq->array = (Item*)malloc(rq->capacity * sizeof(Item));

    if (!rq->array) {
        free(rq);
        return NULL;
    }

    srand(time(NULL)); // Initialize random seed
    return rq;
}

// Check if the randomized queue is empty
bool RandomizedQueueEmpty(RandomizedQueuePtr rq) {
    return rq->size == 0;
}

// Return the number of items in the randomized queue
size_t RandomizedQueueSize(RandomizedQueuePtr rq) {
    return rq->size;
}

// Resize the array to a new capacity
void RandomizedQueueResize(RandomizedQueuePtr rq, size_t new_capacity) {
    Item* new_array = (Item*)malloc(new_capacity * sizeof(Item));
    if (!new_array) return;

    for (size_t i = 0; i < rq->size; i++) {
        new_array[i] = rq->array[i];
    }

    free(rq->array);
    rq->array = new_array;
    rq->capacity = new_capacity;
}

// Add an item to the randomized queue
void RandomizedQueueEnqueue(RandomizedQueuePtr rq, Item item) {
    if (rq->size == rq->capacity) {
        RandomizedQueueResize(rq, 2 * rq->capacity);
    }
    rq->array[rq->size++] = item;
}

// Remove and return a random item from the randomized queue
Item RandomizedQueueDequeue(RandomizedQueuePtr rq) {
    if (RandomizedQueueEmpty(rq)) {
        return NULL;
    }

    // Pick a random index
    size_t random_index = rand() % rq->size;

    // Get the random item
    Item item = rq->array[random_index];

    // Swap the random item with the last item
    rq->array[random_index] = rq->array[rq->size - 1];
    rq->size--;

    // Shrink the array if necessary
    if (rq->size > 0 && rq->size == rq->capacity / 4) {
        RandomizedQueueResize(rq, rq->capacity / 2);
    }

    return item;
}

// Destroy the randomized queue and free memory
void RandomizedQueueDestroy(RandomizedQueuePtr rq) {
    free(rq->array);
    free(rq);
}