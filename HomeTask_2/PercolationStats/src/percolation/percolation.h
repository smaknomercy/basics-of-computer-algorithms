#ifndef PERCOLATION_H
#define PERCOLATION_H

#include "dynamic_connectivity/dynamic_connectivity.h" 
#include <stdbool.h>

typedef struct PercolationImpl Percolation;

// Structure to hold the percolation client data


// Create a new Percolation for a grid of size n x n
Percolation* create_percolation(int n);

// Destroy the Percolation and free all allocated memory
void destroy_percolation(Percolation* pc);

// Get the total number of open sites in the grid
int get_opened_count(Percolation* pc);

// Open the site at (i, j) if it is not already open
void open_coordinate(Percolation* pc, int i, int j);

// Check if the site at (i, j) is open
bool is_opened(Percolation* pc, int i, int j);

// Check if the system percolates (a path exists from the top to the bottom)
bool percolates(Percolation* pc);

#endif // PERCOLATION_H
