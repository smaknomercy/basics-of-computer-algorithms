#include "Stack.h"
#include <stdlib.h>
#include <limits.h>

struct Stack {
    int *array;       // Array to store the stack elements
    int *minArray;    // Auxiliary array to store the minimum values
    size_t size;      // Current size of the stack
    size_t capacity;  // Capacity of the stack
};

StackPtr StackInit() {
    StackPtr stack = (StackPtr)malloc(sizeof(struct Stack));
    if (!stack) return NULL;

    stack->capacity = 2;
    stack->size = 0;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    stack->minArray = (int*)malloc(stack->capacity * sizeof(int));

    if (!stack->array || !stack->minArray) {
        free(stack->array);
        free(stack->minArray);
        free(stack);
        return NULL;
    }

    return stack;
}

bool StackEmpty(StackPtr stack) {
    return stack->size == 0;
}

size_t StackSize(StackPtr stack) {
    return stack->size;
}

void StackResize(StackPtr stack, size_t new_capacity) {
    int* new_array = (int*)realloc(stack->array, new_capacity * sizeof(int));
    int* new_minArray = (int*)realloc(stack->minArray, new_capacity * sizeof(int));

    if (!new_array || !new_minArray) {
        return;
    }

    stack->array = new_array;
    stack->minArray = new_minArray;
    stack->capacity = new_capacity;
}

void StackPush(StackPtr stack, int item) {
    if (stack->size == stack->capacity) {
        StackResize(stack, 2 * stack->capacity);
    }

    stack->array[stack->size] = item;

    if (stack->size == 0) {
        stack->minArray[stack->size] = item;
    } else {
        stack->minArray[stack->size] = (item < stack->minArray[stack->size - 1]) ? item : stack->minArray[stack->size - 1];
    }

    stack->size++;
}

int StackPop(StackPtr stack) {
    if (StackEmpty(stack)) {
        return INT_MIN;
    }

    stack->size--;
    return stack->array[stack->size];
}

int StackMin(StackPtr stack) {
    if (StackEmpty(stack)) {
        return INT_MIN;
    }

    return stack->minArray[stack->size - 1];
}

void StackDestroy(StackPtr stack) {
    free(stack->array);
    free(stack->minArray);
    free(stack);
}