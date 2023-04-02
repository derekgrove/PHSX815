#include <iostream>
#include <random>
#include <vector>
#include <cmath>

// Target function (non-trivial)
double target_function(double x) {
    return std::exp(-std::pow(x - 0.5, 2) / 0.1);
}

// Proposal function (uniform)
double proposal_function(double x) {
    return 1.0;
}

// Perform rejection sampling
std::vector<double> rejection_sampling(size_t num_samples) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    std::vector<double> samples;
    double max_value = 1.0;

    while (samples.size() < num_samples) {
        double x = dis(gen);
        double y = dis(gen) * max_value;

        if (y <= target_function(x) / proposal_function(x)) {
            samples.push_back(x);
        }
    }

    return samples;
}

int main() {
    size_t num_samples = 1000;
    std::vector<double> samples = rejection_sampling(num_samples);

    // Print the samples
    for (size_t i = 0; i < samples.size(); ++i) {
        std::cout << "Sample " << i + 1 << ": " << samples[i] << std::endl;
    }

    return 0;
}
