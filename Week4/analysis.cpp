#include <iostream>
#include <fstream>
#include <vector>
#include "gnuplot.hpp"

int main() {
    std::ifstream infile;
    // attempt to open the file
    infile.open("data2.txt");
    if (!infile) {
        std::cerr << "Failed to open input file." << std::endl;
        return 1;
    }

    // verify that the file actually opened...
    std::vector<int> results;
    if (infile.is_open())
    {
        int num;
        while(infile >> num) {
            results.push_back(num);
        }

        infile.close();
    }
    //for (int i = 0; i < results.size(); i++) {
    //    std::cout << results[i] << " ";
    //}
    //std::cout << std::endl;

    Gnuplot gp;

    // set the style of the histogram
    gp.set_style("histogram");

    // set the title and labels of the histogram
    gp.set_title("Example Histogram");
    gp.set_xlabel("Value");
    gp.set_ylabel("Frequency");

    // create a vector of data to plot
    std::vector<double> data = {1, 2, 3, 4, 5, 5, 5, 6, 6, 6, 6};

    // plot the data as a histogram
    gp.plot_histogram(data, "Example");

    //std::cin.get(); // to pause the program

    return 0;
}
