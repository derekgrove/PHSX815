#include <iostream>
#include <fstream>
#include <vector>

const std::string FILE_NAME = "results.txt";

    double decay_analysis() {
        std::ifstream inFile(FILE_NAME); // Open the input file
        std::vector<double> dataVector; // Create a vector to store the data

        if (inFile.is_open()) {
            double value;

            // Read data from the file into the vector
            while (inFile >> value) {
                dataVector.push_back(value);
            }

            inFile.close(); // Close the input file

            // Print the contents of the vector
            std::cout << "Contents of the vector:\n";
            for (double value: dataVector) {
                //std::cout << value << "\n";
            }
        } else {
            throw std::runtime_error("Unable to open results file!");
        }

        //calculate average value, hopefully for a large data set we approach the average lifetime of the pi+
        double total = 0;
        for (std::size_t i = 0; i < dataVector.size(); ++i) {
            total = total + dataVector[i];
        }
        double average_lifetime = total / dataVector.size();
        return average_lifetime;
    }