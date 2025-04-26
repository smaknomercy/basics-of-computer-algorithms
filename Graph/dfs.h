#ifndef DFS_H
#define DFS_H

#include "graph.h"
#include "paths.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * Runs DFS from source vertex `s`, returns Paths struct with filled info.
 */
PathsPtr dfs(const GraphPtr g, vertex_t s);

#endif // DFS_H
