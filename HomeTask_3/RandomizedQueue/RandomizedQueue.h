#ifndef RANDOMIZEDQUEUE_H
#define RANDOMIZEDQUEUE_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* Item;

typedef struct RandomizedQueue RandomizedQueue;
typedef RandomizedQueue* RandomizedQueuePtr;

RandomizedQueuePtr RandomizedQueueInit(void);
bool RandomizedQueueEmpty(RandomizedQueuePtr rq);
size_t RandomizedQueueSize(RandomizedQueuePtr rq);
void RandomizedQueueResize(RandomizedQueuePtr rq, size_t new_capacity);
void RandomizedQueueEnqueue(RandomizedQueuePtr rq, Item item);
Item RandomizedQueueDequeue(RandomizedQueuePtr rq);
void RandomizedQueueDestroy(RandomizedQueuePtr rq);

#ifdef __cplusplus
}
#endif

#endif