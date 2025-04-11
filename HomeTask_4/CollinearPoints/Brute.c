#include <stdio.h>
#include <stdlib.h>
#include "point.h"

int main(void) {
    int N;
    
    FILE* fp = fopen("input.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open input.txt\n");
        return EXIT_FAILURE;
    }
    
    fscanf(fp, "%d", &N);
    
    PointPtr* points = malloc(N * sizeof(PointPtr));
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
        for (int j = i + 1; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                for (int l = k + 1; l < N; l++) {
                    double s1 = slope_to(points[i], points[j]);
                    double s2 = slope_to(points[i], points[k]);
                    double s3 = slope_to(points[i], points[l]);
                    
                    if (s1 == s2 && s1 == s3) {
                        PointPtr collinear[4] = {points[i], points[j], points[k], points[l]};
                        qsort(collinear, 4, sizeof(PointPtr), compare_points);
                        printf("(%d, %d) -> (%d, %d) -> (%d, %d) -> (%d, %d)\n",
                               collinear[0]->x, collinear[0]->y,
                               collinear[1]->x, collinear[1]->y,
                               collinear[2]->x, collinear[2]->y,
                               collinear[3]->x, collinear[3]->y);
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < N; i++) {
        destroy_point(points[i]);
    }
    free(points);
    
    return 0;
}