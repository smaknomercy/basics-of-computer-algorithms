#include "dfs.h"
#include "paths_helper.h"

// recursive DFS does the work
void dfs_recursive(const GraphPtr g, PathsPtr p, vertex_t v) {
    p->marked[v] = true; // marked[v] = true if v connected to s
    int size = 0;
    const vertex_t *adj = GraphAdj(g, v, &size);
    for (int i = 0; i < size; ++i) {
        vertex_t w = adj[i];
        if (!p->marked[w]) {
            dfs_recursive(g, p, w);
            p->edge_to[w] = v; // edge_to[w] = previous vertex on path from s to w
        }
    }
}

PathsPtr dfs(const GraphPtr g, vertex_t s) {
    PathsPtr p = fromGraph(g, s); // initialize data structures

    dfs_recursive(g, p, s); // find vertices connected to s
    return p;
}

