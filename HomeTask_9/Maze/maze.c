#include "maze.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED "\033[1;31m"
#define RESET "\033[0m"

struct Maze {
    char **grid;
    int size;
    pair_t source;
    pair_t dest;
};

static void add_obstacles(MazePtr m, float density) {
    int total_cells = m->size * m->size;
    int obstacles = (int)(total_cells * density);
    int count = 0;

    while (count < obstacles) {
        int x = rand() % m->size;
        int y = rand() % m->size;
        if (m->grid[x][y] == PASSAGE) {
            m->grid[x][y] = OBSTACLE;
            count++;
        }
    }
}

static void add_source_and_dest(MazePtr m) {
    // Generate random coordinates for source and destination
    m->source.x = rand() % m->size;
    m->source.y = rand() % m->size;

    // Ensure destination is different from source
    do {
        m->dest.x = rand() % m->size;
        m->dest.y = rand() % m->size;
    } while (m->source.x == m->dest.x && m->source.y == m->dest.y);

    // Mark the source and destination in the maze
    m->grid[m->source.x][m->source.y] = SOURCE;
    m->grid[m->dest.x][m->dest.y] = DEST;
}

MazePtr MazeInit(int size, float obstacles_density) {
    srand(time(NULL));
    MazePtr m = malloc(sizeof(struct Maze));
    m->size = size;

    m->grid = malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++) {
        m->grid[i] = malloc(size);
        for (int j = 0; j < size; j++) {
            m->grid[i][j] = PASSAGE;
        }
    }

    add_obstacles(m, obstacles_density);
    add_source_and_dest(m);
    return m;
}

char **MazeGetPoints(MazePtr m) { return m->grid; }

int MazeGetSize(MazePtr m) { return m->size; }

pair_t MazeGetSource(MazePtr maze) { return maze->source; }

pair_t MazeGetDest(MazePtr maze) { return maze->dest; }


bool MazeUpdateSourceDest(MazePtr m, pair_t source, pair_t dest) {
    // Check if source and destination are within bounds and not on obstacles
    if (source.x < 0 || source.x >= m->size || source.y < 0 || source.y >= m->size ||
        m->grid[source.x][source.y] == OBSTACLE)
        return false;
    if (dest.x < 0 || dest.x >= m->size || dest.y < 0 || dest.y >= m->size ||
        m->grid[dest.x][dest.y] == OBSTACLE)
        return false;

    // Clear the old source and destination points in the maze
    m->grid[m->source.x][m->source.y] = PASSAGE;
    m->grid[m->dest.x][m->dest.y] = PASSAGE;

    // Update the source and destination with the new coordinates
    m->source = source;
    m->dest = dest;

    // Mark the new source and destination in the maze
    m->grid[m->source.x][m->source.y] = SOURCE;
    m->grid[m->dest.x][m->dest.y] = DEST;

    return true;
}

void MazePrint(MazePtr m) {
    for (int i = 0; i < m->size; i++) {
        for (int j = 0; j < m->size; j++) {
            if (i == m->source.x && j == m->source.y)
                printf(RED "%c" RESET, SOURCE);
            else if (i == m->dest.x && j == m->dest.y)
                printf(RED "%c" RESET, DEST);
            else
                putchar(m->grid[i][j]);
        }
        putchar('\n');
    }
}

void MazePrintWithPath(MazePtr m, pair_t *path, int length) {
    // Allocate a 2D boolean array to mark the path
    char **is_path = malloc(m->size * sizeof(char *));
    for (int i = 0; i < m->size; i++) {
        is_path[i] = calloc(m->size, sizeof(char));
    }

    // Mark all path points
    for (int i = 0; i < length; i++) {
        int x = path[i].x;
        int y = path[i].y;
        if (x >= 0 && x < m->size && y >= 0 && y < m->size) {
            is_path[x][y] = 1;
        }
    }

    // Print maze with path
    for (int i = 0; i < m->size; i++) {
        for (int j = 0; j < m->size; j++) {

            if (i == m->source.x && j == m->source.y)
                printf(RED "%c" RESET, SOURCE);
            else if (i == m->dest.x && j == m->dest.y)
                printf(RED "%c" RESET, DEST);
            else if (is_path[i][j])
                printf(RED "%c" RESET, PATH);
            else
                putchar(m->grid[i][j]);
        }
        putchar('\n');
    }

    // Free the temp path matrix
    for (int i = 0; i < m->size; i++) {
        free(is_path[i]);
    }
    free(is_path);
}

void MazeDestroy(MazePtr m) {
    for (int i = 0; i < m->size; i++) {
        free(m->grid[i]);
    }
    free(m->grid);
    free(m);
}
