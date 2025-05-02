// maze_sdl.c
// Draws the maze and solved path using SDL2 graphics

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "maze.h"
#include "../BFS/graph.h"
#include "../BFS/paths.h"
#include "../BFS/paths_helper.h"
#include "../BFS/bfs.h"
#include "../BFS/dfs.h"

#define CELL_SIZE 20         // pixels per maze cell
#define WINDOW_TITLE "Maze Solver (SDL2)"

static inline int coord_to_id(int x, int y, int N) {
    return x * N + y;
}
static inline void id_to_coord(int id, int N, int *x, int *y) {
    *x = id / N;
    *y = id % N;
}

static GraphPtr maze_to_graph(MazePtr m) {
    int N = MazeGetSize(m);
    char **grid = MazeGetPoints(m);
    GraphPtr g = GraphInit(N * N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == OBSTACLE) continue;
            int v = coord_to_id(i, j, N);
            // right neighbor
            if (j+1 < N && grid[i][j+1] != OBSTACLE) {
                GraphAddEdge(g, v, coord_to_id(i, j+1, N));
            }
            // down neighbor
            if (i+1 < N && grid[i+1][j] != OBSTACLE) {
                GraphAddEdge(g, v, coord_to_id(i+1, j, N));
            }
        }
    }
    return g;
}

static pair_t *vertex_path_to_coords(vertex_t *vpath, int len, int N) {
    pair_t *coords = malloc(len * sizeof(pair_t));
    for (int i = 0; i < len; i++) {
        int x, y;
        id_to_coord(vpath[i], N, &x, &y);
        coords[i].x = x;
        coords[i].y = y;
    }
    return coords;
}

int main(int argc, char *argv[]) {
    int N = 20;
    float density = 0.3f;
    if (argc > 1) N = atoi(argv[1]);
    if (argc > 2) density = atof(argv[2]);

    // initialize maze and graph
    MazePtr maze = MazeInit(N, density);
    GraphPtr graph = maze_to_graph(maze);
    pair_t s = MazeGetSource(maze), d = MazeGetDest(maze);
    vertex_t src = coord_to_id(s.x, s.y, N);
    vertex_t dst = coord_to_id(d.x, d.y, N);

    // solve via BFS
    PathsPtr pb = PathsInit(graph, src, BFS);
    int bfs_len = 0;
    vertex_t *bfs_v = PathsPathTo(pb, dst, &bfs_len);
    pair_t *bfs_path = bfs_v ? vertex_path_to_coords(bfs_v, bfs_len, N) : NULL;

    // setup SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window   *win = SDL_CreateWindow(WINDOW_TITLE,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            N * CELL_SIZE,
                            N * CELL_SIZE,
                            0);
    if (!win) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1,
                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // render once
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);

    char **grid = MazeGetPoints(maze);
    // draw cells
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            SDL_Rect cell = { j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE };
            // default passage
            if (grid[i][j] == OBSTACLE) {
                SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
            } else {
                SDL_SetRenderDrawColor(ren, 240, 240, 240, 255);
            }
            SDL_RenderFillRect(ren, &cell);
        }
    }

    // draw BFS path
    if (bfs_path) {
        SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
        for (int k = 0; k < bfs_len; k++) {
            SDL_Rect cell = { bfs_path[k].y * CELL_SIZE,
                              bfs_path[k].x * CELL_SIZE,
                              CELL_SIZE, CELL_SIZE };
            SDL_RenderFillRect(ren, &cell);
        }
    }
    
    // draw source
    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
    SDL_Rect src_r = { s.y * CELL_SIZE, s.x * CELL_SIZE, CELL_SIZE, CELL_SIZE };
    SDL_RenderFillRect(ren, &src_r);
    // draw dest
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_Rect dst_r = { d.y * CELL_SIZE, d.x * CELL_SIZE, CELL_SIZE, CELL_SIZE };
    SDL_RenderFillRect(ren, &dst_r);

    SDL_RenderPresent(ren);

    // wait until window closed
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
        }
        SDL_Delay(50);
    }

    // cleanup
    if (bfs_v) { free(bfs_v); free(bfs_path); }
    PathsDestroy(pb);
    GraphDestroy(graph);
    MazeDestroy(maze);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
