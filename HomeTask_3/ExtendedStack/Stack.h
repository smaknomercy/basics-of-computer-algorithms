#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Stack* StackPtr;
StackPtr StackInit();
bool StackEmpty(StackPtr stack);
size_t StackSize(StackPtr stack);
void StackPush(StackPtr stack, int item);
int StackPop(StackPtr stack);
int StackMin(StackPtr stack);
void StackDestroy(StackPtr stack);

#ifdef __cplusplus
}
#endif
#endif // STACK_H