#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdio.h>

typedef int vertex_t;           // Type of vertex (can be changed to any type)
typedef int edge_t;             // Type of edge (can be changed to any type)
typedef struct Graph *GraphPtr; // Opaque pointer to graph structure (pimpl)

GraphPtr GraphInit(int num_vertices); // Creates a new graph with num vertices
GraphPtr GraphInitFromFile(FILE *in); // Creates a graph from an input stream (assumes FILE* stream)

void GraphAddEdge(GraphPtr g, vertex_t v,
                  vertex_t w);     // Adds an undirected edge between vertices v and w

vertex_t GraphV(const GraphPtr g); // Returns the number of vertices
edge_t GraphE(const GraphPtr g);   // Returns the number of edges

// Returns an array of vertices adjacent to v and stores the number of adjacent vertices in *size.
// Caller must NOT free the returned array
const vertex_t *GraphAdj(const GraphPtr g, vertex_t v, int *size);

void GraphPrint(const GraphPtr g); // Prints the graph to stdout
void GraphDestroy(GraphPtr g);     // Frees the graph structure

// For Practical session 11 
// Finds shortest path from start to end using DFS
// Returns dynamically allocated array of vertices forming the path (or NULL if no path)
// Stores path length in *path_len
vertex_t *GraphShortestDFS(const GraphPtr g, vertex_t start, vertex_t end, int *path_len);

vertex_t *GraphShortestBFS(const GraphPtr g, vertex_t start, vertex_t end, int *path_len);

#endif // GRAPH_H
