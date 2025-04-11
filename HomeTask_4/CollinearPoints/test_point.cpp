#include <gtest/gtest.h>
extern "C" {
#include "point.h"
}

TEST(PointTest, CreateAndDestroy) {
    PointPtr p = create_point(10, 20);
    EXPECT_EQ(p->x, 10);
    EXPECT_EQ(p->y, 20);
    destroy_point(p);
}

TEST(PointTest, ComparePoints) {
    PointPtr p1 = create_point(5, 10);
    PointPtr p2 = create_point(5, 15);
    PointPtr p3 = create_point(7, 10);
    // p1 (5,10) < p2 (5,15) because 10 < 15.
    EXPECT_LT(compare_points(&p1, &p2), 0);
    // p1 (5,10) < p3 (7,10) because same y and 5 < 7.
    EXPECT_LT(compare_points(&p1, &p3), 0);
    // p2 should be greater than p3 because (5,15) > (7,10) in our ordering.
    EXPECT_GT(compare_points(&p2, &p3), 0);
    destroy_point(p1);
    destroy_point(p2);
    destroy_point(p3);
}

TEST(PointTest, SlopeTo) {
    PointPtr p1 = create_point(0, 0);
    PointPtr p2 = create_point(4, 4);
    PointPtr p3 = create_point(0, 5);
    PointPtr p4 = create_point(5, 0);
    // Slope between (0,0) and (4,4) should be 1.
    EXPECT_DOUBLE_EQ(slope_to(p1, p2), 1.0);
    // Vertical line: (0,0) and (0,5) should be DBL_MAX.
    EXPECT_DOUBLE_EQ(slope_to(p1, p3), DBL_MAX);
    // Horizontal line: (0,0) and (5,0) should be 0.0.
    EXPECT_DOUBLE_EQ(slope_to(p1, p4), 0.0);
    // Identical points: slope should be -DBL_MAX.
    EXPECT_DOUBLE_EQ(slope_to(p1, p1), -DBL_MAX);
    destroy_point(p1);
    destroy_point(p2);
    destroy_point(p3);
    destroy_point(p4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}