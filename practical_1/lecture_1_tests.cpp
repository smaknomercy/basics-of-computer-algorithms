#include <gtest/gtest.h>

#define N 10

int sz[N];

bool connected__quick_find(const int* id, int p, int q) {
    return id[p] == id[q];
}

void union__quick_find(int* id, int p, int q) {
    int pid = id[p];
    int qid = id[q];
    for (int i = 0; i < N; i++) {
        if (id[i] == pid) id[i] = qid;
    }
}

int root__quick_union(int* id, int i) {
    while (i != id[i]) {
        i = id[i];
    }
    return i;
}

bool connected__quick_union(int* id, int p, int q) {
    return root__quick_union(id, p) == root__quick_union(id, q);
}

void union__quick_union(int* id, int p, int q) {
    int root_p = root__quick_union(id, p);
    int root_q = root__quick_union(id, q);
    id[root_p] = root_q;
}

int root__quick_union_path_compression(int* id, int i) {
    while (i != id[i]) {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}

class QuickUnionTest : public ::testing::Test {
protected:
    int id[N];

    void SetUp() override {
        for (int i = 0; i < N; ++i) {
            id[i] = i;
            sz[i] = 1;
        }
    }
};

TEST_F(QuickUnionTest, ConnectedQuickFind) {
    id[3] = id[4] = 1;
    EXPECT_TRUE(connected__quick_find(id, 3, 4));
    EXPECT_FALSE(connected__quick_find(id, 3, 5));
}

TEST_F(QuickUnionTest, UnionQuickFind) {
    union__quick_find(id, 2, 3);
    EXPECT_TRUE(connected__quick_find(id, 2, 3));
    EXPECT_FALSE(connected__quick_find(id, 2, 4));
}

TEST_F(QuickUnionTest, UnionQuickUnion) {
    union__quick_union(id, 2, 3);
    EXPECT_TRUE(connected__quick_union(id, 2, 3));
    EXPECT_FALSE(connected__quick_union(id, 2, 4));
}

TEST_F(QuickUnionTest, RootQuickUnion) {
    id[3] = 2;
    id[2] = 1;
    EXPECT_EQ(root__quick_union(id, 3), 1);
}

TEST_F(QuickUnionTest, ConnectedQuickUnion) {
    union__quick_union(id, 3, 4);
    EXPECT_TRUE(connected__quick_union(id, 3, 4));
    EXPECT_FALSE(connected__quick_union(id, 3, 5));
}

TEST_F(QuickUnionTest, RootQuickUnionPathCompression) {
    id[3] = 2;
    id[2] = 1;
    root__quick_union_path_compression(id, 3);
    EXPECT_EQ(id[3], 1);
}
