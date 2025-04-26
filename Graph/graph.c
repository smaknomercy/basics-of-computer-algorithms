#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    vertex_t *neighbors;
    int size;
    int capacity;
} Vector;

#define INITIAL_CAPACITY 4

static int add_adjacent_vertex(Vector *list, vertex_t v)
{
    if (list->size >= list->capacity)
    {
        int new_capacity = list->capacity == 0 ? INITIAL_CAPACITY : list->capacity * 2;
        vertex_t *new_data = realloc(list->neighbors, new_capacity * sizeof(vertex_t));
        if (!new_data)
            return 0;
        list->neighbors = new_data;
        list->capacity = new_capacity;
    }
    list->neighbors[list->size++] = v;
    return 1;
}

struct Graph
{
    vertex_t V;
    edge_t E;
    Vector *adj;
};

GraphPtr GraphInit(int num_vertices)
{
    GraphPtr g = malloc(sizeof(*g));
    if (!g)
        return NULL;
    g->V = num_vertices;
    g->E = 0;
    g->adj = calloc(num_vertices, sizeof(Vector));
    if (!g->adj)
    {
        free(g);
        return NULL;
    }
    return g;
}

GraphPtr GraphInitFromFile(FILE *in)
{
    if (!in)
        return NULL;
    int V, E;
    if (fscanf(in, "%d", &V) != 1)
        return NULL;
    if (fscanf(in, "%d", &E) != 1)
        return NULL;
    GraphPtr g = GraphInit(V);
    if (!g)
        return NULL;
    for (int i = 0; i < E; ++i)
    {
        int v, w;
        if (fscanf(in, "%d %d", &v, &w) != 2)
        {
            GraphDestroy(g);
            return NULL;
        }
        GraphAddEdge(g, v, w);
    }
    return g;
}

void GraphAddEdge(GraphPtr g, vertex_t v, vertex_t w)
{
    if (!g || v < 0 || v >= g->V || w < 0 || w >= g->V)
        return;
    if (!add_adjacent_vertex(&g->adj[v], w))
        return;
    if (!add_adjacent_vertex(&g->adj[w], v))
        return;
    g->E++;
}

vertex_t GraphV(const GraphPtr g)
{
    return g ? g->V : 0;
}

edge_t GraphE(const GraphPtr g)
{
    return g ? g->E : 0;
}

const vertex_t *GraphAdj(const GraphPtr g, vertex_t v, int *size)
{
    if (!g || v < 0 || v >= g->V || !size)
        return NULL;
    *size = g->adj[v].size;
    return g->adj[v].neighbors;
}

void GraphPrint(const GraphPtr g)
{
    if (!g)
        return;
    for (vertex_t v = 0; v < g->V; ++v)
    {
        printf("%d:", v);
        for (int i = 0; i < g->adj[v].size; ++i)
            printf(" %d", g->adj[v].neighbors[i]);
        printf("\n");
    }
}

void GraphDestroy(GraphPtr g)
{
    if (!g)
        return;
    for (vertex_t v = 0; v < g->V; ++v)
        free(g->adj[v].neighbors);
    free(g->adj);
    free(g);
}

static void ShortestDFS(const GraphPtr g,
                        vertex_t current,
                        vertex_t end,
                        vertex_t *path,
                        int path_len,
                        vertex_t *shortest,
                        int *shortest_len,
                        char *visited)
{
    visited[current] = 1;
    path[path_len++] = current;

    if (current == end)
    {
        if (*shortest_len == -1 || path_len < *shortest_len)
        {
            memcpy(shortest, path, path_len * sizeof(vertex_t));
            *shortest_len = path_len;
        }
    }
    else
    {
        int adj_size = 0;
        const vertex_t *adj = GraphAdj(g, current, &adj_size);
        for (int i = 0; i < adj_size; ++i)
        {
            vertex_t w = adj[i];
            if (!visited[w])
            {
                ShortestDFS(g, w, end, path, path_len,
                            shortest, shortest_len, visited);
            }
        }
    }

    visited[current] = 0;
}

vertex_t *GraphShortestDFS(const GraphPtr g,
                           vertex_t start,
                           vertex_t end,
                           int *path_len)
{
    if (!g || !path_len ||
        start < 0 || start >= GraphV(g) ||
        end < 0 || end >= GraphV(g))
    {
        return NULL;
    }

    int V = GraphV(g);
    vertex_t *path = malloc(V * sizeof(vertex_t));
    vertex_t *shortest = malloc(V * sizeof(vertex_t));
    char *visited = calloc(V, sizeof(char));
    int shortest_len = -1;

    if (!path || !shortest || !visited)
    {
        free(path);
        free(shortest);
        free(visited);
        return NULL;
    }

    ShortestDFS(g, start, end, path, 0, shortest, &shortest_len, visited);

    free(path);
    free(visited);

    if (shortest_len == -1)
    {
        free(shortest);
        *path_len = 0;
        return NULL;
    }

    *path_len = shortest_len;
    vertex_t *result = malloc(shortest_len * sizeof(vertex_t));
    if (!result)
    {
        free(shortest);
        return NULL;
    }
    memcpy(result, shortest, shortest_len * sizeof(vertex_t));
    free(shortest);
    return result;
}
