#include "graph.h"
#include "paths.h"
#include "paths_helper.h"
#include <stdio.h>
#include <stdlib.h>

void test_simpleDFS();

// For Practical session 11 
void test_shortestDFS() {
    GraphPtr g = GraphInit(6); // Create graph with 6 nodes

    GraphAddEdge(g, 0, 1); // 0 -> 1
    GraphAddEdge(g, 1, 2); // 1 -> 2
    GraphAddEdge(g, 2, 3); // 2 -> 3
    GraphAddEdge(g, 2, 4); // 2 -> 4
    GraphAddEdge(g, 3, 4); // 3 -> 4
    GraphAddEdge(g, 3, 5); // 3 -> 5
    GraphAddEdge(g, 0, 2); // 0 -> 2
    GraphAddEdge(g, 1, 0); // 1 -> 0
    GraphAddEdge(g, 3, 1); // 3 -> 1
    GraphAddEdge(g, 4, 0); // 4 -> 0
    
    int path_len;
    vertex_t *path = GraphShortestDFS(g, 0, 4, &path_len);

    printf("Shortest path found by DFS:\n");
    printPath(path, path_len);
    
    free(path);

    GraphDestroy(g);
}
int main() {
    {
        FILE *f = fopen("tinyG.txt", "r");
        if (f == NULL) {
            printf("Failed to open file\n");
            return 1;
        }

        GraphPtr g = GraphInitFromFile(f);
        fclose(f);

        if (g == NULL) {
            printf("Failed to read graph from file\n");
            return 1;
        }

        printf("Graph with %d vertices and %d edges:\n", GraphV(g), GraphE(g));
        GraphPrint(g);

        GraphDestroy(g);
    }
    {
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

        vertex_t source = 0;
        PathsPtr paths = PathsInit(g, source, DFS);
        if (!paths) {
            fprintf(stderr, "Failed to initialize paths\n");
            exit(1);
        }

        printf("Has paths from vertex %d:\n", source);
        for (int v = 0; v < GraphV(g); ++v) {
            if (PathsHasPathTo(paths, v)) {
                printf("%d ", v);
            }
        }
        printf("\n");

        PathsDestroy(paths);
        GraphDestroy(g);
    }

    { 
        // For Practical session 11 
        test_shortestDFS();
        
    }
    return 0;
}