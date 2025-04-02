#include "Deque.h"
#include <gtest/gtest.h>

// Test initialization, empty check, and size retrieval
TEST(DequeTest, InitAndEmpty) {
    DequePtr deque = DequeInit();
    ASSERT_NE(deque, nullptr);
    EXPECT_TRUE(DequeEmpty(deque));
    EXPECT_EQ(DequeSize(deque), 0);
    DequeDestroy(deque);
}

// Test adding to the front and removing from the front
TEST(DequeTest, AddFirstAndRemoveFirst) {
    DequePtr deque = DequeInit();
    int value1 = 1;
    int value2 = 2;
    Item a = &value1;
    Item b = &value2;

    DequeAddFirst(deque, a);
    DequeAddFirst(deque, b);
    EXPECT_EQ(DequeSize(deque), 2);

    EXPECT_EQ(DequeRemoveFirst(deque), b);
    EXPECT_EQ(DequeRemoveFirst(deque), a);
    EXPECT_TRUE(DequeEmpty(deque));

    EXPECT_EQ(DequeRemoveFirst(deque), nullptr);

    DequeDestroy(deque);
}

// Test adding to the back and removing from the back
TEST(DequeTest, AddLastAndRemoveLast) {
    DequePtr deque = DequeInit();
    int value1 = 1;
    int value2 = 2;
    Item a = &value1;
    Item b = &value2;

    DequeAddLast(deque, a);
    DequeAddLast(deque, b);
    EXPECT_EQ(DequeSize(deque), 2);

    EXPECT_EQ(DequeRemoveLast(deque), b);
    EXPECT_EQ(DequeRemoveLast(deque), a);
    EXPECT_TRUE(DequeEmpty(deque));
    EXPECT_EQ(DequeRemoveLast(deque), nullptr);

    DequeDestroy(deque);
}

// Test a combination of adding at both ends and removing sequentially
TEST(DequeTest, AddFirstAndAddLastAndRemovals) {
    DequePtr deque = DequeInit();
    int value1 = 1;
    int value2 = 2;
    int value3 = 3;
    int value4 = 4;
    Item a = &value1;
    Item b = &value2;
    Item c = &value3;
    Item d = &value4;

    DequeAddFirst(deque, a);
    DequeAddLast(deque, b);
    DequeAddFirst(deque, c);
    DequeAddLast(deque, d);
    EXPECT_EQ(DequeSize(deque), 4);

    EXPECT_EQ(DequeRemoveFirst(deque), c);
    EXPECT_EQ(DequeRemoveFirst(deque), a);
    EXPECT_EQ(DequeRemoveFirst(deque), b);
    EXPECT_EQ(DequeRemoveFirst(deque), d);
    EXPECT_TRUE(DequeEmpty(deque));

    DequeDestroy(deque);
}

// Test resizing downward by triggering the condition for reducing capacity
TEST(DequeTest, ResizeDown) {
    DequePtr deque = DequeInit();
    int value1 = 1;
    int value2 = 2;
    int value3 = 3;
    int value4 = 4;
    Item a = &value1;
    Item b = &value2;
    Item c = &value3;
    Item d = &value4;

    DequeAddLast(deque, a);
    DequeAddLast(deque, b);
    DequeAddLast(deque, c);
    DequeAddLast(deque, d);
    EXPECT_EQ(DequeSize(deque), 4);

    EXPECT_EQ(DequeRemoveFirst(deque), a);
    EXPECT_EQ(DequeRemoveFirst(deque), b);
    EXPECT_EQ(DequeRemoveFirst(deque), c);
    EXPECT_EQ(DequeRemoveFirst(deque), d);
    EXPECT_TRUE(DequeEmpty(deque));

    DequeDestroy(deque);
}

// Test removal functions when the deque is empty
TEST(DequeTest, RemoveFromEmpty) {
    DequePtr deque = DequeInit();
    EXPECT_EQ(DequeRemoveFirst(deque), nullptr);
    EXPECT_EQ(DequeRemoveLast(deque), nullptr);
    DequeDestroy(deque);
}

// Main function to run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}