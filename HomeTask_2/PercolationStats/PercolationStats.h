#ifndef PERCOLATION_STATS_H
#define PERCOLATION_STATS_H

#include <stdlib.h>

typedef struct PercolationStatsImpl PercolationStats; //Pimpl

// Initialize PercolationStats for T experiments on an NxN grid
PercolationStats* create_percolation_stats(int grid_size, int experiments);
// Destroy PercolationStats and free memory
void destroy_percolation_stats(PercolationStats* ps);
// Calculate the mean of percolation thresholds
double mean_percolation_threshold(PercolationStats* ps);
// Calculate the standard deviation of percolation thresholds
double stddev_percolation_threshold(PercolationStats* ps);
// Run Monte Carlo simulations, store percolation thresholds
void run_experiments(PercolationStats* ps);
// Print mean, standard deviation, and confidence interval to the console
void print_statistics(PercolationStats* ps);
#endif // PERCOLATION_STATS_H