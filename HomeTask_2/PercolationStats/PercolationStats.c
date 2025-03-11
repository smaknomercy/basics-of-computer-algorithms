#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "percolation/percolation.h"
#include "PercolationStats.h"
#include "statistical_measures/statistical_measures.h"

struct PercolationStatsImpl{
    int n; // Grid size (n x n)
    int T; // T: number of experiments
    double* thresholds; // Array to store percolation thresholds for each experiment
};

PercolationStats* create_percolation_stats(int grid_size, int experiments) {
    PercolationStats* ps = (PercolationStats*)malloc(sizeof(PercolationStats));
    ps->n = grid_size;
    ps->T = experiments;
    ps->thresholds = (double*)malloc(sizeof(double) * experiments);
    return ps;
}


void destroy_percolation_stats(PercolationStats* ps) {
    free(ps->thresholds);
    free(ps);
}

double mean_percolation_threshold(PercolationStats* ps) {
    return mean(ps->thresholds, ps->T);
}

double stddev_percolation_threshold(PercolationStats* ps) {
    return stddev(ps->thresholds, ps->T);
}

void run_experiments(PercolationStats* ps) {
    for (int t = 0; t < ps->T; t++) {
        Percolation* pc = create_percolation(ps->n);
        while (!percolates(pc)) {
            int i = rand() % ps->n;
            int j = rand() % ps->n;
            open_coordinate(pc, i, j);
        }
        ps->thresholds[t] = (double)get_opened_count(pc) / (ps->n * ps->n);
        destroy_percolation(pc);
    }
}

void print_statistics(PercolationStats* ps) {
    double mean_value = mean_percolation_threshold(ps);
    double stddev_value = stddev_percolation_threshold(ps);
    double ci[2];
    confidence_interval(ps->thresholds, ps->T, ci);

    printf("Mean percolation threshold: %f\n", mean_value);
    printf("Standard deviation: %f\n", stddev_value);
    printf("95%% confidence interval: [%f, %f]\n", ci[0], ci[1]);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <grid size> <number of experiments>\n", argv[0]);
        return 1;
    }

    int grid_size = atoi(argv[1]);
    int num_experiments = atoi(argv[2]);

    // Seed the random number generator
    srand(time(NULL));

    // Create PercolationStats object
    PercolationStats* stats = create_percolation_stats(grid_size, num_experiments);

    // Run the experiments
    run_experiments(stats);

    // Print statistics
    print_statistics(stats);

    // Clean up
    destroy_percolation_stats(stats);

    return 0;
}