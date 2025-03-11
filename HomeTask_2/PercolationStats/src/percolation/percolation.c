#include "percolation.h"
#include <stdlib.h>

struct PercolationImpl {
    int n;                      // Grid size (n x n)
    int opened_count;           // Count of opened sites
    bool* grid;                 // Flattened 2D array to store open/closed states
    DynamicConnectivity dc;     // DynamicConnectivity structure
    int virtual_top;            // Virtual top site for percolation check
    int virtual_bottom;         // Virtual bottom site for percolation check
};

Percolation* create_percolation(int n) {
    Percolation* pc = (Percolation*)malloc(sizeof(Percolation));
    pc->n = n;
    pc->opened_count = 0;
    pc->grid = (bool*)calloc(n * n, sizeof(bool));
    init_dynamic_connectivity(&pc->dc, n * n + 2);
    pc->virtual_top = n * n;
    pc->virtual_bottom = n * n + 1;
    
    for (int j = 0; j < n; ++j) {
        add_union(&pc->dc, pc->virtual_top, j);
    }

    for (int j = (n * (n - 1)); j < n * n; ++j) {
        add_union(&pc->dc, pc->virtual_bottom, j);
    }

    return pc;
}

void destroy_percolation(Percolation* pc) {
    free(pc->grid);
    free(pc);
}

int get_opened_count(Percolation* pc) {
    return pc->opened_count;
}

void open_coordinate(Percolation* pc, int i, int j) {
    if (is_opened(pc, i, j)) return;

    int index = i * pc->n + j;
    pc->grid[index] = true;
    pc->opened_count++;

    if (i > 0 && is_opened(pc, i - 1, j)) {
        add_union(&pc->dc, index, (i - 1) * pc->n + j);
    }
    if (i < pc->n - 1 && is_opened(pc, i + 1, j)) {
        add_union(&pc->dc, index, (i + 1) * pc->n + j);
    }
    if (j > 0 && is_opened(pc, i, j - 1)) {
        add_union(&pc->dc, index, i * pc->n + (j - 1));
    }
    if (j < pc->n - 1 && is_opened(pc, i, j + 1)) {
        add_union(&pc->dc, index, i * pc->n + (j + 1));
    }
}

bool is_opened(Percolation* pc, int i, int j) {
    return pc->grid[i * pc->n + j];
}

bool percolates(Percolation* pc) {
    return connected(&pc->dc, pc->virtual_top, pc->virtual_bottom);
}