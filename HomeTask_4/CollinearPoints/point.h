#ifndef POINT_H
#define POINT_H

#include <float.h> // for DBL_MAX

typedef struct Point {
    int x, y;
} Point;

typedef Point* PointPtr;

/**
 * Creates a new point with coordinates (x, y).
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 * @return Pointer to the created Point.
 */
PointPtr create_point(int x, int y);

/**
 * Destroys a point and frees its memory.
 * @param p Pointer to the Point to be destroyed.
 */
void destroy_point(PointPtr p);

/**
 * Compares two points based on their y-coordinates, and then x-coordinates.
 * @param a Pointer to the first PointPtr.
 * @param b Pointer to the second PointPtr.
 * @return Negative if a < b, 0 if equal, positive if a > b.
 */
int compare_points(const void* a, const void* b);

/**
 * Computes the slope between two points.
 * Special cases:
 *  - Identical points: returns -DBL_MAX.
 *  - Vertical line: returns DBL_MAX.
 *  - Horizontal line: returns 0.0.
 * @param p1 The first point.
 * @param p2 The second point.
 * @return The slope as a double.
 */
double slope_to(PointPtr p1, PointPtr p2);

#endif // POINT_H