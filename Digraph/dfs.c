#include "dfs.h"
#include "paths_helper.h"

// recursive DFS does the work
void dfs_recursive(const DigraphPtr g, PathsPtr p, vertex_t v)
{
    p->marked[v] = true; // marked[v] = true if v connected to s
    int size = 0;
    const vertex_t *adj = DigraphAdj(g, v, &size);
    for (int i = 0; i < size; ++i)
    {
        vertex_t w = adj[i];
        if (!p->marked[w])
        {
            dfs_recursive(g, p, w);
            p->edge_to[w] = v; // edge_to[w] = previous vertex on path from s to w
        }
    }
}

PathsPtr dfs(const DigraphPtr g, vertex_t s)
{
    PathsPtr p = fromDigraph(g, s); // initialize data structures

    dfs_recursive(g, p, s); // find vertices connected to s
    return p;
}

static void topo_dfs(const DigraphPtr g, vertex_t v, bool *visited, vertex_t *order, int *idx)
{
    visited[v] = true;
    int adj_count = 0;
    const vertex_t *adj = DigraphAdj(g, v, &adj_count);
    for (int i = 0; i < adj_count; ++i)
    {
        vertex_t w = adj[i];
        if (!visited[w])
        {
            topo_dfs(g, w, visited, order, idx);
        }
    }
    order[(*idx)--] = v;
}

vertex_t *topological_sort(const DigraphPtr g)
{
    int V = DigraphV(g);
    bool *visited = calloc(V, sizeof(bool));
    vertex_t *order = malloc(V * sizeof(vertex_t));
    if (!visited || !order)
    {
        free(visited);
        free(order);
        return NULL;
    }

    int idx = V - 1;
    for (vertex_t v = 0; v < V; ++v)
    {
        if (!visited[v])
        {
            topo_dfs(g, v, visited, order, &idx);
        }
    }

    free(visited);
    return order;
}