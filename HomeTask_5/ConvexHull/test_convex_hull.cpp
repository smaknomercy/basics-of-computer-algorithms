#include <gtest/gtest.h>
extern "C" {
#include "convex_hull.h"
}

void runConvexHullTest(Point input[], int n, Point expected[], int expected_size) {
    Point points[100];
    for (int i = 0; i < n; i++) {
        points[i] = input[i];
    }
    Point hull[100];
    int hull_size = 0;
    convexHull(points, n, hull, &hull_size);
    EXPECT_EQ(hull_size, expected_size);
    for (int i = 0; i < hull_size && i < expected_size; i++) {
        EXPECT_EQ(hull[i].x, expected[i].x) << "Mismatch at index " << i;
        EXPECT_EQ(hull[i].y, expected[i].y) << "Mismatch at index " << i;
    }
}

TEST(ConvexHullTest, BasicConvexHull) {
    Point input[] = { {0, 0}, {1, 1}, {2, 2}, {1, 3}, {0, 2}, {2, 0} };
    int n = sizeof(input)/sizeof(input[0]);

    Point expected[] = { {0, 0}, {2, 0}, {2, 2}, {1, 3}, {0, 2} };
    int expected_size = sizeof(expected)/sizeof(expected[0]);
    runConvexHullTest(input, n, expected, expected_size);
}

// Not Enough Points
TEST(ConvexHullTest, NotEnoughPoints) {
    Point input[] = { {0, 0}, {1, 1} };
    int n = 2;
    Point expected[] = { {0, 0}, {1, 1} };
    int expected_size = 2;
    runConvexHullTest(input, n, expected, expected_size);
}

// Single Point
TEST(ConvexHullTest, SinglePoint) {
    Point input[] = { {1, 1} };
    int n = 1;
    Point expected[] = { {1, 1} };
    int expected_size = 1;
    runConvexHullTest(input, n, expected, expected_size);
}

// Collinear Points
TEST(ConvexHullTest, CollinearPoints) {
    Point input[] = { {0, 0}, {1, 1}, {2, 2}, {3, 3} };
    int n = 4;
    Point expected[] = { {0, 0}, {3, 3} };
    int expected_size = 2;
    runConvexHullTest(input, n, expected, expected_size);
}

// Collinear Points with Extra Point
TEST(ConvexHullTest, CollinearWithExtraPoint) {
    Point input[] = { {0, 0}, {1, 1}, {2, 2}, {3, 3}, {0, 3} };
    int n = 5;
    Point expected[] = { {0, 0}, {3, 3}, {0, 3} };
    int expected_size = 3;
    runConvexHullTest(input, n, expected, expected_size);
}

// Random Points
TEST(ConvexHullTest, RandomPoints) {
    Point input[] = { {0, 0}, {2, 0}, {3, 1}, {3, 3}, {2, 3}, {1, 2} };
    int n = 6;
    Point expected[] = { {0, 0}, {2, 0}, {3, 1}, {3, 3}, {2, 3}, {1, 2} };
    int expected_size = 6;
    runConvexHullTest(input, n, expected, expected_size);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}