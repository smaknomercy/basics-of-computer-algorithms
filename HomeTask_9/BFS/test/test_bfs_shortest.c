#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../graph.h"

static void test_linear_graph() {
    // 0–1–2–3–4
    GraphPtr g = GraphInit(5);
    GraphAddEdge(g, 0, 1);
    GraphAddEdge(g, 1, 2);
    GraphAddEdge(g, 2, 3);
    GraphAddEdge(g, 3, 4);

    int path_len = 0;
    vertex_t *path = GraphShortestBFS(g, 0, 4, &path_len);
    assert(path != NULL);
    assert(path_len == 5);
    for (int i = 0; i < path_len; i++) {
        assert(path[i] == i);
    }
    free(path);
    GraphDestroy(g);
}

static void test_cycle_graph() {
    // 0–1–2–0 and 2–3
    GraphPtr g = GraphInit(4);
    GraphAddEdge(g, 0, 1);
    GraphAddEdge(g, 1, 2);
    GraphAddEdge(g, 2, 0);
    GraphAddEdge(g, 2, 3);

    // Shortest from 0 to 3 is 0→2→3
    int path_len = 0;
    vertex_t *path = GraphShortestBFS(g, 0, 3, &path_len);
    assert(path != NULL);
    assert(path_len == 3);
    assert(path[0] == 0);
    assert(path[1] == 2);
    assert(path[2] == 3);
    free(path);
    GraphDestroy(g);
}

static void test_no_path() {
    GraphPtr g = GraphInit(3);

    int path_len = -1;
    vertex_t *path = GraphShortestBFS(g, 0, 2, &path_len);
    assert(path == NULL);
    assert(path_len == 0);

    GraphDestroy(g);
}

int main(void) {
    test_linear_graph();
    test_cycle_graph();
    test_no_path();
    printf("All BFS-shortest-path tests passed.\n");
    return 0;
}
