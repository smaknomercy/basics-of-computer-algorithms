#include "sorting.h"
#include <stdlib.h>
#include <string.h>

static void swap(void *a, void *b, size_t size)
{
    unsigned char *pa = a, *pb = b, tmp;
    for (size_t i = 0; i < size; i++)
    {
        tmp = pa[i];
        pa[i] = pb[i];
        pb[i] = tmp;
    }
}

void insertion_sort(void *base, size_t nitems, size_t size,
                    int (*compar)(const void *, const void *))
{
    unsigned char *arr = base;
    for (size_t i = 1; i < nitems; i++)
    {
        unsigned char *key = malloc(size);
        if (!key)
            exit(EXIT_FAILURE);
        memcpy(key, arr + i * size, size);
        size_t j = i;
        while (j > 0 && compar(arr + (j - 1) * size, key) > 0)
        {
            memcpy(arr + j * size, arr + (j - 1) * size, size);
            j--;
        }
        memcpy(arr + j * size, key, size);
        free(key);
    }
}

void selection_sort(void *base, size_t nitems, size_t size,
                    int (*compar)(const void *, const void *))
{
    unsigned char *arr = base;
    for (size_t i = 0; i < nitems - 1; i++)
    {
        size_t min_idx = i;
        for (size_t j = i + 1; j < nitems; j++)
        {
            if (compar(arr + j * size, arr + min_idx * size) < 0)
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            swap(arr + i * size, arr + min_idx * size, size);
        }
    }
}

void shell_sort(void *base, size_t nitems, size_t size,
                int (*compar)(const void *, const void *))
{
    unsigned char *arr = base;
    for (size_t gap = nitems / 2; gap > 0; gap /= 2)
    {
        for (size_t i = gap; i < nitems; i++)
        {
            unsigned char *temp = malloc(size);
            if (!temp)
                exit(EXIT_FAILURE);
            memcpy(temp, arr + i * size, size);
            size_t j = i;
            while (j >= gap && compar(arr + (j - gap) * size, temp) > 0)
            {
                memcpy(arr + j * size, arr + (j - gap) * size, size);
                j -= gap;
            }
            memcpy(arr + j * size, temp, size);
            free(temp);
        }
    }
}