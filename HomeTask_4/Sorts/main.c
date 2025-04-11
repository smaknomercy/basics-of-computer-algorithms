#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sorting.h"

int compare_int(const void *a, const void *b)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return ia - ib;
}

typedef void (*sort_func_t)(void *, size_t, size_t, int (*)(const void *, const void *));

typedef struct
{
    const char *name;
    sort_func_t func;
} sort_algo;

#define NUM_ALGOS 3

int main(void)
{
    srand((unsigned)time(NULL));

    sort_algo algorithms[NUM_ALGOS] = {
        {"Insertion Sort", insertion_sort},
        {"Selection Sort", selection_sort},
        {"Shell Sort", shell_sort}};

    /* Array sizes to test */
    size_t sizes[] = {100, 1000, 10000, 100000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    /* Print table header */
    printf("%-10s %-20s %-20s %-20s\n", "Size", "Algorithm", "Random (ms)", "Sorted (ms)");
    printf("--------------------------------------------------------------------------\n");

    for (int s = 0; s < num_sizes; s++)
    {
        size_t n = sizes[s];
        int *master = malloc(n * sizeof(int));
        if (!master)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < n; i++)
        {
            master[i] = rand();
        }

        int *sorted_master = malloc(n * sizeof(int));
        if (!sorted_master)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        memcpy(sorted_master, master, n * sizeof(int));
        qsort(sorted_master, n, sizeof(int), compare_int);

        for (int a = 0; a < NUM_ALGOS; a++)
        {
            int *array_random = malloc(n * sizeof(int));
            if (!array_random)
            {
                fprintf(stderr, "Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            memcpy(array_random, master, n * sizeof(int));
            clock_t start = clock();
            algorithms[a].func(array_random, n, sizeof(int), compare_int);
            clock_t end = clock();
            double time_random = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
            free(array_random);

            int *array_sorted = malloc(n * sizeof(int));
            if (!array_sorted)
            {
                fprintf(stderr, "Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            memcpy(array_sorted, sorted_master, n * sizeof(int));
            start = clock();
            algorithms[a].func(array_sorted, n, sizeof(int), compare_int);
            end = clock();
            double time_sorted = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
            free(array_sorted);

            printf("%-10zu %-20s %-20.3f %-20.3f\n", n, algorithms[a].name, time_random, time_sorted);
        }

        free(master);
        free(sorted_master);
    }

    return 0;
}