#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

void swap(Point *a, Point *b);
int compare_points(const void *a, const void *b);
void quicksort(Point points[], int low, int high);
double getAngle(Point p0, Point p);
int compare_by_polar_angle(const void *a, const void *b, Point p0);
void merge(Point points[], int left, int mid, int right, Point p0);
void mergeSort(Point points[], int left, int right, Point p0);
void convexHullMain();

#endif