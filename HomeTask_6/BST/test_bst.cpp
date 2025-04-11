#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <iostream>

extern "C" {
#include "BST.h"
#include "node.h"
#include "item.h"
#include <stdlib.h>
}

// Helper function to build a BST from an array of keys.
NodePtr buildBST(const char* keys[], int count) {
    if (count <= 0)
        return NULL;
    NodePtr root = create_node(keys[0], NULL);
    for (int i = 1; i < count; i++) {
        BSTPut(root, keys[i], NULL);
    }
    return root;
}

// BSTFloor tests
TEST(BSTTest, Floor_EmptyTree) {
    NodePtr head = NULL;
    EXPECT_EQ(BSTFloor(head, "A"), nullptr);
}

TEST(BSTTest, Floor_SingleElement) {
    NodePtr head = create_node("M", NULL);
    ASSERT_NE(BSTFloor(head, "M"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "M")->key, "M"));
    EXPECT_EQ(BSTFloor(head, "L"), nullptr);
    ASSERT_NE(BSTFloor(head, "N"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "N")->key, "M"));
    BSTDestroy(head);
}

TEST(BSTTest, Floor_OneLeftElement) {
    NodePtr head = create_node("M", NULL);
    BSTPut(head, "G", NULL);
    ASSERT_NE(BSTFloor(head, "G"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "G")->key, "G"));
    EXPECT_EQ(BSTFloor(head, "F"), nullptr);
    ASSERT_NE(BSTFloor(head, "H"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "H")->key, "G"));
    BSTDestroy(head);
}

TEST(BSTTest, Floor_OneRightElement) {
    NodePtr head = create_node("M", NULL);
    BSTPut(head, "T", NULL);
    ASSERT_NE(BSTFloor(head, "M"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "M")->key, "M"));
    NodePtr res = BSTFloor(head, "N");
    ASSERT_NE(res, nullptr);
    EXPECT_TRUE(equal(res->key, "M"));
    ASSERT_NE(BSTFloor(head, "T"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "T")->key, "T"));
    ASSERT_NE(BSTFloor(head, "U"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "U")->key, "T"));
    BSTDestroy(head);
}

TEST(BSTTest, Floor_MultipleLeftElements) {
    NodePtr head = create_node("M", NULL);
    BSTPut(head, "K", NULL);
    BSTPut(head, "G", NULL);
    ASSERT_NE(BSTFloor(head, "H"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "H")->key, "G"));
    ASSERT_NE(BSTFloor(head, "K"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "K")->key, "K"));
    EXPECT_EQ(BSTFloor(head, "E"), nullptr);
    BSTDestroy(head);
}

TEST(BSTTest, Floor_MultipleRightElements) {
    NodePtr head = create_node("M", NULL);
    BSTPut(head, "P", NULL);
    BSTPut(head, "T", NULL);
    BSTPut(head, "W", NULL);
    ASSERT_NE(BSTFloor(head, "Q"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "Q")->key, "P"));
    ASSERT_NE(BSTFloor(head, "T"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "T")->key, "T"));
    ASSERT_NE(BSTFloor(head, "X"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "X")->key, "W"));
    EXPECT_EQ(BSTFloor(head, "L"), nullptr);
    BSTDestroy(head);
}

TEST(BSTTest, Floor_LeftAndRightElements) {
    NodePtr head = create_node("M", NULL);
    BSTPut(head, "G", NULL);
    BSTPut(head, "T", NULL);
    ASSERT_NE(BSTFloor(head, "H"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "H")->key, "G"));
    ASSERT_NE(BSTFloor(head, "M"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "M")->key, "M"));
    ASSERT_NE(BSTFloor(head, "S"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "S")->key, "M"));
    ASSERT_NE(BSTFloor(head, "T"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "T")->key, "T"));
    ASSERT_NE(BSTFloor(head, "U"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "U")->key, "T"));
    BSTDestroy(head);
}

TEST(BSTTest, Floor_RightMultipleTimes) {
    NodePtr head = create_node("A", NULL);
    BSTPut(head, "C", NULL);
    BSTPut(head, "E", NULL);
    BSTPut(head, "G", NULL);
    ASSERT_NE(BSTFloor(head, "F"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "F")->key, "E"));
    ASSERT_NE(BSTFloor(head, "B"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "B")->key, "A"));
    ASSERT_NE(BSTFloor(head, "H"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "H")->key, "G"));
    BSTDestroy(head);
}

TEST(BSTTest, Floor_LeftMultipleTimes) {
    NodePtr head = create_node("M", NULL);
    BSTPut(head, "K", NULL);
    BSTPut(head, "I", NULL);
    BSTPut(head, "G", NULL);
    ASSERT_NE(BSTFloor(head, "H"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "H")->key, "G"));
    ASSERT_NE(BSTFloor(head, "J"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "J")->key, "I"));
    ASSERT_NE(BSTFloor(head, "L"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "L")->key, "K"));
    ASSERT_NE(BSTFloor(head, "M"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "M")->key, "M"));
    EXPECT_EQ(BSTFloor(head, "F"), nullptr);
    BSTDestroy(head);
}

TEST(BSTTest, Floor_LeftAndRightMultiple) {
    NodePtr head = create_node("M", NULL);
    BSTPut(head, "G", NULL);
    BSTPut(head, "T", NULL);
    BSTPut(head, "D", NULL);
    BSTPut(head, "I", NULL);
    BSTPut(head, "W", NULL);
    BSTPut(head, "H", NULL);
    ASSERT_NE(BSTFloor(head, "E"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "E")->key, "D"));
    ASSERT_NE(BSTFloor(head, "F"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "F")->key, "D"));
    ASSERT_NE(BSTFloor(head, "H"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "H")->key, "H"));
    ASSERT_NE(BSTFloor(head, "J"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "J")->key, "I"));
    NodePtr res = BSTFloor(head, "S");
    ASSERT_NE(res, nullptr);
    EXPECT_TRUE(equal(res->key, "M"));
    BSTDestroy(head);
}

TEST(BSTTest, Floor_ComplexTree) {
    NodePtr head = create_node("S", NULL);
    BSTPut(head, "S", NULL);
    BSTPut(head, "E", NULL);
    BSTPut(head, "X", NULL);
    BSTPut(head, "A", NULL);
    BSTPut(head, "P", NULL);
    BSTPut(head, "R", NULL);
    BSTPut(head, "C", NULL);
    BSTPut(head, "H", NULL);
    ASSERT_NE(BSTFloor(head, "Q"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "Q")->key, "P"));
    ASSERT_NE(BSTFloor(head, "H"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "H")->key, "H"));
    ASSERT_NE(BSTFloor(head, "K"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "K")->key, "H"));
    ASSERT_NE(BSTFloor(head, "Y"), nullptr);
    EXPECT_TRUE(equal(BSTFloor(head, "Y")->key, "X"));
    BSTDestroy(head);
}

TEST(BSTTest, Floor_TwoNodeTree) {
    NodePtr head = create_node("D", NULL);
    BSTPut(head, "C", NULL);
    BSTPut(head, "B", NULL);
    EXPECT_EQ(BSTFloor(head, "A"), nullptr);
    BSTDestroy(head);
}

// BSTDeleteMin tests
TEST(BSTTest, DeleteMin_EmptyTree) {
    NodePtr head = NULL;
    EXPECT_EQ(BSTDeleteMin(head), nullptr);
    BSTDestroy(head);
}

TEST(BSTTest, DeleteMin_OnlyNode) {
    NodePtr head = create_node("D", NULL);
    NodePtr newHead = BSTDeleteMin(head);
    EXPECT_EQ(newHead, nullptr);
    BSTDestroy(newHead);
}

TEST(BSTTest, DeleteMin_LeftSkewed) {
    NodePtr head = create_node("D", NULL);
    BSTPut(head, "C", NULL);
    BSTPut(head, "B", NULL);
    NodePtr newHead = BSTDeleteMin(head);
    EXPECT_EQ(newHead, head);
    EXPECT_EQ(BSTSize(newHead), 2);
    BSTDestroy(newHead);
}

TEST(BSTTest, DeleteMin_RootIsMin) {
    NodePtr head = create_node("A", NULL);
    BSTPut(head, "B", NULL);
    BSTPut(head, "C", NULL);
    NodePtr newHead = BSTDeleteMin(head);
    ASSERT_NE(newHead, nullptr);
    EXPECT_TRUE(equal(newHead->key, "B"));
    EXPECT_EQ(BSTSize(newHead), 2);
    ASSERT_NE(newHead->right, nullptr);
    EXPECT_TRUE(equal(newHead->right->key, "C"));
    EXPECT_EQ(newHead->left, nullptr);
    BSTDestroy(newHead);
}

TEST(BSTTest, DeleteMin_BothSubtrees) {
    NodePtr head = create_node("D", NULL);
    BSTPut(head, "B", NULL);
    BSTPut(head, "C", NULL);
    BSTPut(head, "F", NULL);
    NodePtr newHead = BSTDeleteMin(head);
    ASSERT_NE(newHead, nullptr);
    EXPECT_TRUE(equal(newHead->key, "D"));
    EXPECT_EQ(BSTSize(newHead), 3);
    ASSERT_NE(newHead->left, nullptr);
    EXPECT_TRUE(equal(newHead->left->key, "C"));
    ASSERT_NE(newHead->right, nullptr);
    EXPECT_TRUE(equal(newHead->right->key, "F"));
    BSTDestroy(newHead);
}

TEST(BSTTest, DeleteMin_BalancedTree) {
    NodePtr head = create_node("D", NULL);
    BSTPut(head, "C", NULL);
    BSTPut(head, "B", NULL);
    BSTPut(head, "F", NULL);
    NodePtr newHead = BSTDeleteMin(head);
    ASSERT_NE(newHead, nullptr);
    EXPECT_TRUE(equal(newHead->key, "D"));
    EXPECT_EQ(BSTSize(newHead), 3);
    ASSERT_NE(newHead->left, nullptr);
    EXPECT_TRUE(equal(newHead->left->key, "C"));
    ASSERT_NE(newHead->right, nullptr);
    EXPECT_TRUE(equal(newHead->right->key, "F"));
    BSTDestroy(newHead);
}


// BSTCeiling
TEST(BSTTest, Ceiling_EmptyTree) {
    EXPECT_EQ(BSTCeiling(NULL, "M"), nullptr);
}

TEST(BSTTest, Ceiling_SingleElement) {
    NodePtr head = create_node("M", NULL);
    ASSERT_NE(BSTCeiling(head, "M"), nullptr);
    EXPECT_TRUE(equal(BSTCeiling(head, "M")->key, "M"));
    ASSERT_NE(BSTCeiling(head, "L"), nullptr);
    EXPECT_TRUE(equal(BSTCeiling(head, "L")->key, "M"));
    EXPECT_EQ(BSTCeiling(head, "N"), nullptr);
    BSTDestroy(head);
}

TEST(BSTTest, Ceiling_MultipleNodes) {
    const char* keys[] = {"J", "D", "P", "F", "L"};
    NodePtr head = buildBST(keys, 5);
    ASSERT_NE(BSTCeiling(head, "E"), nullptr);
    EXPECT_TRUE(equal(BSTCeiling(head, "E")->key, "F"));
    ASSERT_NE(BSTCeiling(head, "L"), nullptr);
    EXPECT_TRUE(equal(BSTCeiling(head, "L")->key, "L"));
    EXPECT_EQ(BSTCeiling(head, "Q"), nullptr);
    BSTDestroy(head);
}

// BSTRank
TEST(BSTTest, Rank_Test) {
    NodePtr head = create_node("C", NULL);
    BSTPut(head, "A", NULL);
    BSTPut(head, "E", NULL);
    BSTPut(head, "B", NULL);
    BSTPut(head, "D", NULL);
    EXPECT_EQ(BSTRank(head, "A"), 0);
    EXPECT_EQ(BSTRank(head, "B"), 1);
    EXPECT_EQ(BSTRank(head, "C"), 2);
    EXPECT_EQ(BSTRank(head, "D"), 3);
    EXPECT_EQ(BSTRank(head, "E"), 4);
    EXPECT_EQ(BSTRank(head, "F"), 5);
    BSTDestroy(head);
}

// BSTSelect
TEST(BSTTest, Select_Test) {
    NodePtr head = create_node("C", NULL);
    BSTPut(head, "A", NULL);
    BSTPut(head, "E", NULL);
    BSTPut(head, "B", NULL);
    BSTPut(head, "D", NULL);
    NodePtr node = BSTSelect(head, 0);
    ASSERT_NE(node, nullptr);
    EXPECT_TRUE(equal(node->key, "A"));
    node = BSTSelect(head, 2);
    ASSERT_NE(node, nullptr);
    EXPECT_TRUE(equal(node->key, "C"));
    node = BSTSelect(head, 4);
    ASSERT_NE(node, nullptr);
    EXPECT_TRUE(equal(node->key, "E"));
    EXPECT_EQ(BSTSelect(head, 5), nullptr);
    BSTDestroy(head);
}

// BSTMin and BSTMax
TEST(BSTTest, MinMax_Test) {
    const char* keys[] = {"M", "C", "R", "A", "Z", "K"};
    NodePtr head = buildBST(keys, 6);
    ASSERT_NE(BSTMin(head), nullptr);
    EXPECT_TRUE(equal(BSTMin(head), "A"));
    ASSERT_NE(BSTMax(head), nullptr);
    EXPECT_TRUE(equal(BSTMax(head), "Z"));
    BSTDestroy(head);
}

// BSTDeleteMax
TEST(BSTTest, DeleteMax_Test) {
    const char* keys[] = {"F", "C", "H", "A", "E", "I"};
    NodePtr head = buildBST(keys, 6);
    ASSERT_NE(BSTMax(head), nullptr);
    EXPECT_TRUE(equal(BSTMax(head), "I"));
    head = BSTDeleteMax(head);
    ASSERT_NE(BSTMax(head), nullptr);
    EXPECT_TRUE(equal(BSTMax(head), "H"));
    BSTDestroy(head);
}

// isBalanced
// Test for a balanced tree.
TEST(BSTTest, IsBalanced_BalancedTree) {
    NodePtr root = create_node("B", NULL);
    BSTPut(root, "A", NULL);
    BSTPut(root, "C", NULL);
    EXPECT_TRUE(isBalanced(root));
    BSTDestroy(root);
}

// Test for an unbalanced tree.
TEST(BSTTest, IsBalanced_UnbalancedTree) {
    NodePtr root = create_node("A", NULL);
    BSTPut(root, "B", NULL);
    BSTPut(root, "C", NULL);
    EXPECT_FALSE(isBalanced(root));
    BSTDestroy(root);
}

// Main
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}