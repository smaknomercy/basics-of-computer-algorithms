#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "maze.h"
#include "../BFS/graph.h"
#include "../BFS/paths.h"
#include "../BFS/paths_helper.h"
#include "../BFS/bfs.h"
#include "../BFS/dfs.h"

static inline int coord_to_id(int x, int y, int N) {
    return x * N + y;
}

static inline void id_to_coord(int id, int N, int *out_x, int *out_y) {
    *out_x = id / N;
    *out_y = id % N;
}

static GraphPtr maze_to_graph(MazePtr m) {
    int N = MazeGetSize(m);
    char **grid = MazeGetPoints(m);
    GraphPtr g = GraphInit(N * N);

    // for each cell, if it's not an obstacle, connect to right & down neighbors
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == OBSTACLE) continue;
            int v = coord_to_id(i, j, N);
            // right
            if (j + 1 < N && grid[i][j+1] != OBSTACLE) {
                int w = coord_to_id(i, j+1, N);
                GraphAddEdge(g, v, w);
            }
            // down
            if (i + 1 < N && grid[i+1][j] != OBSTACLE) {
                int w = coord_to_id(i+1, j, N);
                GraphAddEdge(g, v, w);
            }
        }
    }

    return g;
}

static pair_t *vertex_path_to_coords(vertex_t *vert_path,
                                     int path_len,
                                     int N)
{
    pair_t *coords = malloc(path_len * sizeof(pair_t));
    for (int k = 0; k < path_len; k++) {
        int x, y;
        id_to_coord(vert_path[k], N, &x, &y);
        coords[k].x = x;
        coords[k].y = y;
    }
    return coords;
}

static int count_marked(PathsPtr p) {
    // paths_helper.h defines struct Paths { bool *marked; ... int vertices; }
    Paths *pp = (Paths *)p;
    int cnt = 0;
    for (int i = 0; i < pp->vertices; i++) {
        if (pp->marked[i]) cnt++;
    }
    return cnt;
}

int main(int argc, char *argv[]) {
    int N = 20;
    float density = 0.3f;
    if (argc > 1) N = atoi(argv[1]);
    if (argc > 2) density = atof(argv[2]);

    // 1) Initialize maze
    MazePtr maze = MazeInit(N, density);

    // 2) Print the raw maze
    printf("Generated %dx%d maze (density=%.2f):\n", N, N, density);
    MazePrint(maze);
    printf("\n");

    // 3) Convert to graph
    GraphPtr g = maze_to_graph(maze);

    // 4) Get source & dest IDs
    pair_t s = MazeGetSource(maze);
    pair_t d = MazeGetDest(maze);
    vertex_t src = coord_to_id(s.x, s.y, N);
    vertex_t dst = coord_to_id(d.x, d.y, N);

    // ---- BFS solve ----
    PathsPtr pb = PathsInit(g, src, BFS);
    int bfs_path_len = 0;
    vertex_t *bfs_verts = PathsPathTo(pb, dst, &bfs_path_len);
    int bfs_visited = count_marked(pb);
    printf("BFS: path length = %d, visited = %d cells\n",
           bfs_path_len, bfs_visited);

    if (bfs_verts) {
        pair_t *bfs_coords = vertex_path_to_coords(bfs_verts, bfs_path_len, N);
        printf("Maze + BFS path:\n");
        MazePrintWithPath(maze, bfs_coords, bfs_path_len);
        free(bfs_coords);
        free(bfs_verts);
    } else {
        printf("No BFS path found.\n");
    }
    PathsDestroy(pb);
    printf("\n");

    // ---- DFS solve ----
    PathsPtr pd = PathsInit(g, src, DFS);
    int dfs_path_len = 0;
    vertex_t *dfs_verts = PathsPathTo(pd, dst, &dfs_path_len);
    int dfs_visited = count_marked(pd);
    printf("DFS: path length = %d, visited = %d cells\n",
           dfs_path_len, dfs_visited);

    if (dfs_verts) {
        pair_t *dfs_coords = vertex_path_to_coords(dfs_verts, dfs_path_len, N);
        printf("Maze + DFS path:\n");
        MazePrintWithPath(maze, dfs_coords, dfs_path_len);
        free(dfs_coords);
        free(dfs_verts);
    } else {
        printf("No DFS path found.\n");
    }
    PathsDestroy(pd);
    printf("\n");

    // 5) Cleanup
    GraphDestroy(g);
    MazeDestroy(maze);
    return 0;
}
