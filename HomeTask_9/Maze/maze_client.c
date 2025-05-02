#include "maze.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int maze_size = 20;
    float obstacle_density = 0.3f;

    if (argc > 1)
        maze_size = atoi(argv[1]);
    if (argc > 2)
        obstacle_density = atof(argv[2]);

    printf("Initializing maze of size %d with obstacle density %.2f\n", maze_size,
           obstacle_density);
    MazePtr maze = MazeInit(maze_size, obstacle_density);

    printf("Maze size: %d\n", MazeGetSize(maze));
    printf("Source: (%d, %d)\n", MazeGetSource(maze).x, MazeGetSource(maze).y);
    printf("Destination: (%d, %d)\n", MazeGetDest(maze).x,
           MazeGetDest(maze).y);

    printf("Printing maze:\n");
    MazePrint(maze);
    printf("\n");

    char **points = MazeGetPoints(maze);
    printf("Printing points:\n");
    for (int i = 0; i < maze_size; i++) {
        for (int j = 0; j < maze_size; j++) {
            printf("%c", points[i][j]);
        }
        printf("\n");
    }

    // Example path: manually constructed for testing
    pair_t path[] = {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {2, 2}};
    int path_length = sizeof(path) / sizeof(path[0]);

    printf("\nMaze with random path:\n");
    MazePrintWithPath(maze, path, path_length);
    printf("\n");

    // Define new source and destination coordinates
    pair_t new_source = {5, 5};
    pair_t new_dest = {15, 15};

    // Update the source and destination, and check if it's successful
    if (MazeUpdateSourceDest(maze, new_source, new_dest)) {
        printf("Maze after updating source and destination:\n");
        MazePrint(maze);
    } else {
        printf("Failed to update source and destination (invalid position or obstacle).\n");
    }

    MazeDestroy(maze);
    return 0;
}
