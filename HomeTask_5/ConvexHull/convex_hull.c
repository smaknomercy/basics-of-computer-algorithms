#include "convex_hull.h"

void swap(Point *a, Point *b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

int compare_points(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return p1->y - p2->y;
}

void quicksort(Point points[], int low, int high) {
    if (low < high) {
        int pivot = points[high].y;
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (points[j].y <= pivot) {
                i++;
                swap(&points[i], &points[j]);
            }
        }
        swap(&points[i + 1], &points[high]);
        int pi = i + 1;
        quicksort(points, low, pi - 1);
        quicksort(points, pi + 1, high);
    }
}

double getAngle(Point p0, Point p) {
    return atan2(p.y - p0.y, p.x - p0.x);
}

int compare_by_polar_angle(const void *a, const void *b, Point p0) {
    Point *pointA = (Point *)a;
    Point *pointB = (Point *)b;
    double angleA = getAngle(p0, *pointA);
    double angleB = getAngle(p0, *pointB);

    if (angleA < angleB) return -1;
    if (angleA > angleB) return 1;
    return 0;
}

void merge(Point points[], int left, int mid, int right, Point p0) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Point *L = (Point *)malloc(n1 * sizeof(Point));
    Point *R = (Point *)malloc(n2 * sizeof(Point));

    for (int i = 0; i < n1; i++) L[i] = points[left + i];
    for (int i = 0; i < n2; i++) R[i] = points[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compare_by_polar_angle(&L[i], &R[j], p0) <= 0) {
            points[k++] = L[i++];
        } else {
            points[k++] = R[j++];
        }
    }
    while (i < n1) points[k++] = L[i++];
    while (j < n2) points[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(Point points[], int left, int right, Point p0) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(points, left, mid, p0);
        mergeSort(points, mid + 1, right, p0);
        merge(points, left, mid, right, p0);
    }
}

int ccw(Point p, Point q, Point r) {
    int cross = (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
    if (cross > 0) return 1;
    if (cross < 0) return -1;
    return 0;
}

void convexHull(Point points[], int n, Point hull[], int *hull_size) {
    if (n < 3) {
        for (int i = 0; i < n; i++) {
            hull[i] = points[i];
        }
        *hull_size = n;
        return;
    }

    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if ((points[i].y < points[minIndex].y) ||
            (points[i].y == points[minIndex].y && points[i].x < points[minIndex].x))
            minIndex = i;
    }
    swap(&points[0], &points[minIndex]);
    Point p0 = points[0];

    mergeSort(points, 1, n - 1, p0);

    Point stack[n];
    int stackSize = 0;
    stack[stackSize++] = points[0];
    stack[stackSize++] = points[1];

    for (int i = 2; i < n; i++) {
        while (stackSize >= 2 && ccw(stack[stackSize - 2], stack[stackSize - 1], points[i]) <= 0)
            stackSize--;
        stack[stackSize++] = points[i];
    }

    for (int i = 0; i < stackSize; i++) {
        hull[i] = stack[i];
    }
    *hull_size = stackSize;
}

void convexHullMain() {
    Point points[] = {
        {0, 0}, {2, 0}, {1, 1}, {2, 2}, {1, 3}, {0, 2}
    };
    int n = sizeof(points) / sizeof(points[0]);

    printf("Points:\n");
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)\n", points[i].x, points[i].y);
    }

    Point hull[n];
    int hull_size = 0;
    convexHull(points, n, hull, &hull_size);

    printf("\nConvex Hull:\n");
    for (int i = 0; i < hull_size; i++) {
        printf("(%d, %d)\n", hull[i].x, hull[i].y);
    }
}