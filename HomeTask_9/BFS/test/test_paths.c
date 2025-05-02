#include "../bfs.h"
#include "../dfs.h"
#include "../graph.h"
#include "../paths.h"
#include "../paths_helper.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_dfs_1() {
    // DFS demo example from lecture
    GraphPtr g = GraphInit(7);

    GraphAddEdge(g, 0, 1);
    GraphAddEdge(g, 0, 2);
    GraphAddEdge(g, 0, 6);
    GraphAddEdge(g, 0, 5);
    GraphAddEdge(g, 6, 4);
    GraphAddEdge(g, 4, 5);
    GraphAddEdge(g, 4, 3);
    GraphAddEdge(g, 5, 3);

    // Run DFS from vertex 0
    PathsPtr p = dfs(g, 0);
    assert(p != NULL);
    assert(p->vertices == 7);
    assert(p->source == 0);
    assert(p->marked[0] == true); // source must be marked

    // Vertices 1-5 should be reachable (marked = true)
    for (vertex_t v = 1; v < 7; ++v) {
        assert(p->marked[v]);
        assert(p->edge_to[v] >= 0 && p->edge_to[v] < p->vertices);
        printf("dfs: %d - %d\n", v, p->edge_to[v]);
    }
    printf("\n");

    // Clean up
    PathsDestroy(p);
    GraphDestroy(g);
}

void test_dfs_2() {
    GraphPtr g = GraphInit(7);

    // see slide from the lecture
    GraphAddEdge(g, 0, 1);
    GraphAddEdge(g, 0, 2);
    GraphAddEdge(g, 0, 3);
    
    GraphAddEdge(g, 1, 2);
    GraphAddEdge(g, 2, 3);
    
    GraphAddEdge(g, 4, 1);
    GraphAddEdge(g, 4, 2);
    GraphAddEdge(g, 4, 6);
    
    GraphAddEdge(g, 5, 2);
    GraphAddEdge(g, 5, 6);

    // Run DFS from vertex 0
    PathsPtr p = dfs(g, 0);
    assert(p != NULL);
    assert(p->vertices == 7);
    assert(p->source == 0);
    assert(p->marked[0] == true); // source must be marked

    // Vertices 1-5 should be reachable (marked = true)
    for (vertex_t v = 1; v < 7; ++v) {
        assert(p->marked[v]);
        assert(p->edge_to[v] >= 0 && p->edge_to[v] < p->vertices);
        printf("dfs: %d - %d\n", v, p->edge_to[v]);
    }
    printf("\n");

    // Clean up
    PathsDestroy(p);
    GraphDestroy(g);
}

void test_bfs_1() {
    GraphPtr g = GraphInit(7);

    // see slide from the lecture
    GraphAddEdge(g, 0, 1);
    GraphAddEdge(g, 0, 2);
    GraphAddEdge(g, 0, 6);
    GraphAddEdge(g, 0, 5);
    GraphAddEdge(g, 6, 4);
    GraphAddEdge(g, 4, 5);
    GraphAddEdge(g, 4, 3);
    GraphAddEdge(g, 5, 3);

    // Run DFS from vertex 0
    PathsPtr p = bfs(g, 0);
    assert(p != NULL);
    assert(p->vertices == 7);
    assert(p->source == 0);
    assert(p->marked[0] == true); // source must be marked

    // Vertices 1-5 should be reachable (marked = true)
    for (vertex_t v = 1; v < 7; ++v) {
        assert(p->marked[v]);
        assert(p->edge_to[v] >= 0 && p->edge_to[v] < p->vertices);
        printf("dfs: %d - %d\n", v, p->edge_to[v]);
    }
    printf("\n");

    // Clean up
    PathsDestroy(p);
    GraphDestroy(g);
}

void test_bfs_2() {
    GraphPtr g = GraphInit(7);

    // Same graph as in DFS test
    GraphAddEdge(g, 0, 1);
    GraphAddEdge(g, 0, 2);
    GraphAddEdge(g, 0, 3);

    GraphAddEdge(g, 1, 2);
    GraphAddEdge(g, 2, 3);

    GraphAddEdge(g, 4, 1);
    GraphAddEdge(g, 4, 2);
    GraphAddEdge(g, 4, 6);

    GraphAddEdge(g, 5, 2);
    GraphAddEdge(g, 5, 6);

    // Run BFS from vertex 0
    PathsPtr p = bfs(g, 0);
    assert(p != NULL);
    assert(p->vertices == 7);
    assert(p->source == 0);
    assert(p->marked[0] == true); // source must be marked

    for (vertex_t v = 1; v < 7; ++v) {
        assert(p->marked[v]);
        assert(p->edge_to[v] >= 0 && p->edge_to[v] < p->vertices);
        printf("bfs: %d <- %d\n", v, p->edge_to[v]);
    }
    printf("\n");

    // Clean up
    PathsDestroy(p);
    GraphDestroy(g);
}

void test_dfs_disconnected() {
    // Create graph with 6 vertices (0 to 5)
    GraphPtr g = GraphInit(6);

    // Add only a few edges, some vertices remain disconnected
    // Graph:
    // 0-1
    // 2  3  4  5   (disconnected)
    GraphAddEdge(g, 0, 1);

    // Run DFS from vertex 0
    PathsPtr p = dfs(g, 0);
    assert(p != NULL);
    assert(p->vertices == 6);
    assert(p->source == 0);
    assert(p->marked[0] == true); // source must be marked
    assert(p->marked[1] == true); // connected to source

    // Vertices 2, 3, 4, 5 are disconnected
    for (vertex_t v = 2; v < 6; ++v) {
        assert(!p->marked[v]);       // Must not be marked
        assert(p->edge_to[v] == -1); // Must remain -1 (unreachable)
    }

    PathsDestroy(p);
    GraphDestroy(g);
}

void test_paths_basic() {
    GraphPtr g = GraphInit(6);
    /*
        Graph:
        0-1
        |
        2
        / \    
        3  4
        |
        5
    */
    GraphAddEdge(g, 0, 1);
    GraphAddEdge(g, 0, 2);
    GraphAddEdge(g, 2, 3);
    GraphAddEdge(g, 2, 4);
    GraphAddEdge(g, 3, 5);

    PathsPtr p = PathsInit(g, 0, DFS);
    assert(p != NULL);

    // All vertices should be reachable from 0
    for (vertex_t v = 0; v < 6; ++v) {
        assert(PathsHasPathTo(p, v));

        int size = 0;
        vertex_t *path = PathsPathTo(p, v, &size);

        assert(path != NULL);
        assert(size > 0);
        assert(path[0] == 0);        // Path must start from source
        assert(path[size - 1] == v); // Path must end at v

        free(path);
    }

    PathsDestroy(p);
    GraphDestroy(g);
}

void test_PathsHasPathTo() {
    GraphPtr g = GraphInit(4);
    GraphAddEdge(g, 0, 1);

    PathsPtr p = PathsInit(g, 0, DFS);
    assert(p != NULL);

    assert(PathsHasPathTo(p, 0));
    assert(PathsHasPathTo(p, 1));
    assert(!PathsHasPathTo(p, 2));
    assert(!PathsHasPathTo(p, 3));

    int size = 0;
    vertex_t *path = PathsPathTo(p, 2, &size);
    assert(path == NULL);
    assert(size == 0);

    PathsDestroy(p);
    GraphDestroy(g);
}

void test_PathsPathTo() {
    GraphPtr g = GraphInit(7);

    GraphAddEdge(g, 0, 1);
    GraphAddEdge(g, 0, 2);
    GraphAddEdge(g, 0, 3);
    GraphAddEdge(g, 1, 2);
    GraphAddEdge(g, 2, 3);
    GraphAddEdge(g, 4, 1);
    GraphAddEdge(g, 4, 2);
    GraphAddEdge(g, 4, 6);
    GraphAddEdge(g, 5, 2);
    GraphAddEdge(g, 5, 6);

    PathsPtr dfs_paths = PathsInit(g, 0, DFS);
    PathsPtr bfs_paths = PathsInit(g, 0, BFS);
    assert(dfs_paths && bfs_paths);

    // === Path to self (vertex 0) ===
    {
        int dfs_size = 0, bfs_size = 0;
        vertex_t *dfs_path = PathsPathTo(dfs_paths, 0, &dfs_size);
        vertex_t *bfs_path = PathsPathTo(bfs_paths, 0, &bfs_size);
        assert(dfs_path && bfs_path);

        assert(dfs_size == 1 && bfs_size == 1);
        assert(dfs_path[0] == 0 && bfs_path[0] == 0);

        free(dfs_path);
        free(bfs_path);
    }

    // === Path to unreachable vertex (e.g., 10) ===
    {
        int size = 0;
        vertex_t *dfs_path = PathsPathTo(dfs_paths, 10, &size);
        assert(dfs_path == NULL);
        vertex_t *bfs_path = PathsPathTo(bfs_paths, 10, &size);
        assert(bfs_path == NULL);
    }

    // === Path to vertex 3 ===
    {
        int dfs_size = 0, bfs_size = 0;
        vertex_t *dfs_path = PathsPathTo(dfs_paths, 3, &dfs_size);
        vertex_t *bfs_path = PathsPathTo(bfs_paths, 3, &bfs_size);
        assert(dfs_path && bfs_path);

        // DFS might take: 0 -> 1 -> 2 -> 3
        vertex_t expected_dfs[] = {0, 1, 2, 3};
        assert(dfs_size == sizeof(expected_dfs) / sizeof(expected_dfs[0]));
        for (int i = 0; i < dfs_size; ++i)
            assert(dfs_path[i] == expected_dfs[i]);

        // BFS gives shortest path: 0 -> 3
        vertex_t expected_bfs[] = {0, 3};
        assert(bfs_size == sizeof(expected_bfs) / sizeof(expected_bfs[0]));
        for (int i = 0; i < bfs_size; ++i)
            assert(bfs_path[i] == expected_bfs[i]);

        free(dfs_path);
        free(bfs_path);
    }

    // === Path to vertex 6 ===
    {
        int dfs_size = 0, bfs_size = 0;
        vertex_t *dfs_path = PathsPathTo(dfs_paths, 6, &dfs_size);
        vertex_t *bfs_path = PathsPathTo(bfs_paths, 6, &bfs_size);
        assert(dfs_path && bfs_path);

        // Note: DFS path can vary depending on edge traversal order.
        // For this graph, assume DFS goes: 0 -> 1 -> 2 -> 4 -> 6
        vertex_t expected_dfs[] = {0, 1, 2, 4, 6};
        assert(dfs_size == sizeof(expected_dfs) / sizeof(expected_dfs[0]));

        printf("Path from 0 to 6:\n");
        for (int i = 0; i < dfs_size; ++i)
            printf("%d -> ", dfs_path[i]);
        printf("\n");

        for (int i = 0; i < dfs_size; ++i)
            assert(dfs_path[i] == expected_dfs[i]);

        // BFS gives shortest path: 0 -> 1 -> 4 -> 6
        vertex_t expected_bfs[] = {0, 1, 4, 6};
        assert(bfs_size == sizeof(expected_bfs) / sizeof(expected_bfs[0]));

        for (int i = 0; i < bfs_size; ++i)
            assert(bfs_path[i] == expected_bfs[i]);

        free(dfs_path);
        free(bfs_path);
    }

    PathsDestroy(dfs_paths);
    PathsDestroy(bfs_paths);
    GraphDestroy(g);
}

int main() {
    printf("Running Paths tests...\n");

    // test_dfs_1();
    test_dfs_1();
    test_dfs_2();
    test_dfs_disconnected();
    
    test_bfs_1();
    test_bfs_2();

    // test_paths_basic();
    test_PathsHasPathTo();
    test_PathsPathTo();
    printf("All Paths tests passed!\n");
    return 0;
}
