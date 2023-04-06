#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <vector>
#include "decay_analysis.h"

int main(int argc, char *argv[]) {
    // define number of experiments here, also configurable via terminal later in this project
    int Nexp = 100000;
    //initialize lambda's value to 1/(lifetime of pi+), I want the mean to be the lifetime of the pi+
    //lifetime pi+ = 26.033*10-9 seconds
    double lambda = 38412783.7744;

    for (int i = 0; i < argc; i++) {
        if (strncmp(argv[i], "-Nexp", 4) == 0) {
            i++;
            int Ne = std::stoi(argv[i]);
            if (Ne > 0)
                Nexp = Ne;
        }
        if (strncmp(argv[i], "-lambda", 4) == 0) {
            i++;
            double lambda_temp = std::stoi(argv[i]);
            lambda = lambda_temp;
        }
    }

        // Seed the random number generator with the current time
        unsigned seed = 4589698390;
        std::default_random_engine generator(seed);
        std::exponential_distribution<double> distribution(lambda);
        double results[Nexp];
        // generate Nexp number of random numbers, observation events
        for (int i = 0; i < Nexp; ++i) {
            double random_number = distribution(generator);
            results[i] = random_number;
            //std::cout << results[i] << std::endl;
        }

    std::ofstream outFile("results.txt"); // Open the output file

    if(outFile.is_open()) {
        for(int i = 0; i < Nexp; i++) {
            outFile << results[i] << "\n"; // Write each element to the file
        }

        outFile.close(); // Close the output file
        //std::cout << "Array exported to file successfully.\n";
    } else {
        std::cerr << "Unable to open output file.\n";
        return 1;
    }
    double average_lifetime = decay_analysis();
    std::cout << "the average lifetime is: " << average_lifetime << std::endl;
    return 0;
}
