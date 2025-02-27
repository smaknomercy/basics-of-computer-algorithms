#include "percolation.h"
#include <gtest/gtest.h>

// Fixture for Percolation tests
class PercolationTest : public ::testing::Test {
protected:
    static const int percolation_size = 5;
    Percolation* pc;

    void SetUp() override {
        pc = create_percolation(percolation_size);
    }

    // Clean up after each test
    void TearDown() override {
        destroy_percolation(pc);
    }
};

TEST_F(PercolationTest, Initialization) {
    EXPECT_EQ(get_opened_count(pc), 0);
    for (int i = 0; i < percolation_size; ++i) {
        for (int j = 0; j < percolation_size; ++j) {
            EXPECT_FALSE(is_opened(pc, i, j));
        }
    }
    EXPECT_FALSE(percolates(pc));
}

TEST_F(PercolationTest, OpenCoordinate) {
    open_coordinate(pc, 0, 0);
    EXPECT_TRUE(is_opened(pc, 0, 0));
    EXPECT_EQ(get_opened_count(pc), 1);
    EXPECT_FALSE(percolates(pc));

    // Open another site and check
    open_coordinate(pc, 1, 0);
    EXPECT_TRUE(is_opened(pc, 1, 0));
    EXPECT_EQ(get_opened_count(pc), 2);
}

TEST_F(PercolationTest, VerticalPercolation) {
    for (int i = 0; i < percolation_size; ++i) {
        open_coordinate(pc, i, 0); // Open a vertical line from (i, 0)
    }
    EXPECT_TRUE(percolates(pc));
}

TEST_F(PercolationTest, HorizontalPercolation) {
    for (int j = 0; j < percolation_size; ++j) {
        open_coordinate(pc, 0, j); // Open a horizontal line from (0, j)
    }
    EXPECT_FALSE(percolates(pc));
}

TEST_F(PercolationTest, NoDiagonalPercolation) {
    open_coordinate(pc, 0, 0);
    open_coordinate(pc, 1, 1);
    open_coordinate(pc, 2, 2);
    open_coordinate(pc, 3, 3);
    open_coordinate(pc, 4, 4); // Open diagonal sites
    EXPECT_FALSE(percolates(pc)); // No diagonal percolation
}

TEST_F(PercolationTest, ComplexPercolation) {
    // Open sites in a specific pattern to test complex percolation
    open_coordinate(pc, 0, 0);
    open_coordinate(pc, 1, 0);
    open_coordinate(pc, 1, 1);
    open_coordinate(pc, 2, 1);
    open_coordinate(pc, 3, 1);
    open_coordinate(pc, 3, 2);
    open_coordinate(pc, 4, 2);
    open_coordinate(pc, 4, 3); // This should result in percolation
    EXPECT_TRUE(percolates(pc));
}

TEST_F(PercolationTest, OpenCount) {
    EXPECT_EQ(get_opened_count(pc), 0);
    open_coordinate(pc, 0, 0);
    EXPECT_EQ(get_opened_count(pc), 1);
    open_coordinate(pc, 1, 1);
    EXPECT_EQ(get_opened_count(pc), 2);
    open_coordinate(pc, 4, 4);
    EXPECT_EQ(get_opened_count(pc), 3);
}

// Main function for running tests
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}