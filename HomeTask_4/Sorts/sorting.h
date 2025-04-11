#ifndef SORTING_H
#define SORTING_H

#include <stddef.h>

void insertion_sort(void *base, size_t nitems, size_t size,
                    int (*compar)(const void *, const void *));

void selection_sort(void *base, size_t nitems, size_t size,
                    int (*compar)(const void *, const void *));

void shell_sort(void *base, size_t nitems, size_t size,
                int (*compar)(const void *, const void *));

#endif // SORTING_H