#include "RandomizedQueue.h"
#include <gtest/gtest.h>
#include <set>

// Test initialization, empty check, and size retrieval.
TEST(RandomizedQueueTest, InitAndEmpty) {
    RandomizedQueuePtr rq = RandomizedQueueInit();
    ASSERT_NE(rq, nullptr);
    EXPECT_TRUE(RandomizedQueueEmpty(rq));
    EXPECT_EQ(RandomizedQueueSize(rq), 0);
    RandomizedQueueDestroy(rq);
}

// Test that enqueuing items increases the size and makes the queue non-empty.
TEST(RandomizedQueueTest, EnqueueAndSize) {
    RandomizedQueuePtr rq = RandomizedQueueInit();
    int a = 1, b = 2, c = 3;
    
    RandomizedQueueEnqueue(rq, &a);
    RandomizedQueueEnqueue(rq, &b);
    RandomizedQueueEnqueue(rq, &c);
    
    EXPECT_EQ(RandomizedQueueSize(rq), 3);
    EXPECT_FALSE(RandomizedQueueEmpty(rq));
    RandomizedQueueDestroy(rq);
}

// Test that dequeue returns one of the enqueued items and decreases the size.
TEST(RandomizedQueueTest, DequeueReturnsEnqueuedItem) {
    RandomizedQueuePtr rq = RandomizedQueueInit();
    int a = 1, b = 2, c = 3;
    
    RandomizedQueueEnqueue(rq, &a);
    RandomizedQueueEnqueue(rq, &b);
    RandomizedQueueEnqueue(rq, &c);
    
    // Create a set of expected items (addresses)
    std::set<Item> expected = { &a, &b, &c };

    // Remove one item and verify it belongs to the set.
    Item item = RandomizedQueueDequeue(rq);
    EXPECT_TRUE(expected.count(item) > 0);
    EXPECT_EQ(RandomizedQueueSize(rq), 2);
    
    // Dequeue remaining items.
    RandomizedQueueDequeue(rq);
    RandomizedQueueDequeue(rq);
    EXPECT_TRUE(RandomizedQueueEmpty(rq));
    EXPECT_EQ(RandomizedQueueSize(rq), 0);
    
    RandomizedQueueDestroy(rq);
}

// Test that dequeuing from an empty queue returns nullptr.
TEST(RandomizedQueueTest, DequeueFromEmptyReturnsNull) {
    RandomizedQueuePtr rq = RandomizedQueueInit();
    EXPECT_EQ(RandomizedQueueDequeue(rq), nullptr);
    RandomizedQueueDestroy(rq);
}

// Test enqueuing many items (to force resizing upward) and then dequeuing all items.
TEST(RandomizedQueueTest, EnqueueManyAndDequeueAll) {
    RandomizedQueuePtr rq = RandomizedQueueInit();
    const int numItems = 20;
    int items[numItems];
    
    // Enqueue items.
    for (int i = 0; i < numItems; i++) {
        items[i] = i;
        RandomizedQueueEnqueue(rq, &items[i]);
    }
    EXPECT_EQ(RandomizedQueueSize(rq), numItems);
    
    // Dequeue all items and store the returned addresses.
    std::set<Item> dequeued;
    while (!RandomizedQueueEmpty(rq)) {
        Item it = RandomizedQueueDequeue(rq);
        dequeued.insert(it);
    }
    EXPECT_EQ(dequeued.size(), numItems);
    for (int i = 0; i < numItems; i++) {
        EXPECT_TRUE(dequeued.count(&items[i]) > 0);
    }
    RandomizedQueueDestroy(rq);
}

// Test that repeated enqueues and dequeues work correctly,
// which indirectly tests the resizing (both upward and downward).
TEST(RandomizedQueueTest, ResizeDownTest) {
    RandomizedQueuePtr rq = RandomizedQueueInit();
    const int numItems = 16; // Sufficient to force multiple resizes.
    int items[numItems];
    
    // Enqueue items.
    for (int i = 0; i < numItems; i++) {
        items[i] = i;
        RandomizedQueueEnqueue(rq, &items[i]);
    }
    EXPECT_EQ(RandomizedQueueSize(rq), numItems);
    
    // Dequeue items one by one.
    while (!RandomizedQueueEmpty(rq)) {
        RandomizedQueueDequeue(rq);
    }
    EXPECT_EQ(RandomizedQueueSize(rq), 0);
    EXPECT_TRUE(RandomizedQueueEmpty(rq));
    
    RandomizedQueueDestroy(rq);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}