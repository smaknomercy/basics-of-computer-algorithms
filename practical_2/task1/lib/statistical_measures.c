
#include <math.h>
#include "statistical_measures.h"

// Function to compute the mean of a dataset
double mean(double* experiments, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += experiments[i];
    }
    return sum / n;
}

// Function to compute the standard deviation of a dataset
double stddev(double* experiments, int n) {
    double mean_val = mean(experiments, n);
    double sum_of_squares = 0.0;
    for (int i = 0; i < n; i++) {
        sum_of_squares += (experiments[i] - mean_val) * (experiments[i] - mean_val);
    }
    return sqrt(sum_of_squares / n);
}

// Function to compute the 95% confidence interval of a dataset
void confidence_interval(double* experiments, int n, double* ci) {
    double mean_val = mean(experiments, n);
    double stddev_val = stddev(experiments, n);
    double z_value = 1.96; // For 95% confidence level

    double margin_of_error = z_value * (stddev_val / sqrt(n));
    
    ci[0] = mean_val - margin_of_error;
    ci[1] = mean_val + margin_of_error;
}
