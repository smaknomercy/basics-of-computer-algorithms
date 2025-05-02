#ifndef BFS_H
#define BFS_H

#include "graph.h"
#include "paths.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * Runs BFS from source vertex `s`, returns Paths struct with filled info.
 */
PathsPtr bfs(const GraphPtr g, vertex_t s);

#endif // BFS_H
