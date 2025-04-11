#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "point.h"

PointPtr create_point(int x, int y) {
    PointPtr p = malloc(sizeof(Point));
    if (!p) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    p->x = x;
    p->y = y;
    return p;
}

void destroy_point(PointPtr p) {
    free(p);
}

int compare_points(const void* a, const void* b) {
    PointPtr p1 = *(PointPtr*)a;
    PointPtr p2 = *(PointPtr*)b;
    
    if (p1->y != p2->y)
        return p1->y - p2->y;
    else
        return p1->x - p2->x;
}

double slope_to(PointPtr p1, PointPtr p2) {
    if (p1->x == p2->x && p1->y == p2->y)
        return -DBL_MAX;
    if (p1->x == p2->x)
        return DBL_MAX;
    if (p1->y == p2->y)
        return 0.0;
    return ((double)(p2->y - p1->y)) / (p2->x - p1->x);
}