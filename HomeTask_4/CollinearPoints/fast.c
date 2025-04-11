#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "point.h"

static PointPtr current_base = NULL;

int compare_by_slope(const void *a, const void *b) {
    PointPtr pa = *(PointPtr*)a;
    PointPtr pb = *(PointPtr*)b;
    double slopeA = slope_to(current_base, pa);
    double slopeB = slope_to(current_base, pb);
    if (slopeA < slopeB) return -1;
    if (slopeA > slopeB) return 1;
    return 0;
}


static void swap(void *a, void *b, size_t size) {
    char *p = (char*)a, *q = (char*)b;
    for (size_t i = 0; i < size; i++) {
        char tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;
    }
}

static int partition(char *base, int low, int high, size_t size,
                     int (*compar)(const void*, const void*)) {
    char *pivot = base + high * size;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (compar(base + j * size, pivot) <= 0) {
            i++;
            swap(base + i * size, base + j * size, size);
        }
    }
    swap(base + (i + 1) * size, base + high * size, size);
    return i + 1;
}

static void quicksort(char *base, int low, int high, size_t size,
                      int (*compar)(const void*, const void*)) {
    if (low < high) {
        int p = partition(base, low, high, size, compar);
        quicksort(base, low, p - 1, size, compar);
        quicksort(base, p + 1, high, size, compar);
    }
}

void my_qsort(void *base, size_t nitems, size_t size,
              int (*compar)(const void*, const void*)) {
    if (nitems > 0)
        quicksort((char*)base, 0, nitems - 1, size, compar);
}

int main(void) {
    int N;
    
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open input.txt\n");
        return EXIT_FAILURE;
    }
    
    fscanf(fp, "%d", &N);
    PointPtr *points = malloc(N * sizeof(PointPtr));
    if (points == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(fp);
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < N; i++) {
        int x, y;
        fscanf(fp, "%d %d", &x, &y);
        points[i] = create_point(x, y);
    }
    fclose(fp);
    
    for (int i = 0; i < N; i++) {
        PointPtr base = points[i];
        int others_count = N - 1;
        PointPtr *others = malloc(others_count * sizeof(PointPtr));
        if (!others) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        
        int idx = 0;
        for (int j = 0; j < N; j++) {
            if (j == i) continue;
            others[idx++] = points[j];
        }
        
        current_base = base;
        my_qsort(others, others_count, sizeof(PointPtr), compare_by_slope);
        
        int start = 0;
        while (start < others_count) {
            int count = 1;
            double slope = slope_to(base, others[start]);
            int k = start + 1;
            while (k < others_count && slope_to(base, others[k]) == slope) {
                count++;
                k++;
            }
            
            if (count >= 3) {
                int segment_size = count + 1;
                PointPtr *segment = malloc(segment_size * sizeof(PointPtr));
                if (!segment) {
                    fprintf(stderr, "Memory allocation failed.\n");
                    exit(EXIT_FAILURE);
                }
                segment[0] = base;
                for (int m = 0; m < count; m++) {
                    segment[m + 1] = others[start + m];
                }
                
                my_qsort(segment, segment_size, sizeof(PointPtr), compare_points);
                
                if (segment[0] == base) {
                    for (int n = 0; n < segment_size; n++) {
                        printf("(%d, %d)", segment[n]->x, segment[n]->y);
                        if (n < segment_size - 1)
                            printf(" -> ");
                    }
                    printf("\n");
                }
                free(segment);
            }
            start = k;
        }
        free(others);
    }
    
    for (int i = 0; i < N; i++) {
        destroy_point(points[i]);
    }
    free(points);
    
    return 0;
}