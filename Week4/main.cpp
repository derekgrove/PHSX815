#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <chrono>

int main(int argc, char *argv[]) {
    //define collision energy here, needs to be configurable via terminal. This is just the default value:
    double Ce = 500;
    // define number of experiments here, also configurable via terminal later in this project
    int Nexp = 10;
    //create an array of all decay products in order of mass (GeV/c^2)
    std::vector<std::string> product_names = {"\u03BD_e", "\u03BD_\u03BC", "\u03BD_\u03C4", "e", "u", "d", "s",
                                              "\u03BC", "c", "\u03C4", "b", "t"};
    int names_size = product_names.size();

    for (int i = 0; i < argc; i++) {
        if (strncmp(argv[i], "-Nexp", 4) == 0) {
            i++;
            int Ne = std::stoi(argv[i]);
            if (Ne > 0)
                Nexp = Ne;
        }
        if (strncmp(argv[i], "-Ce", 4) == 0) {
            i++;
            int C_E = std::stoi(argv[i]);
            if (C_E > 0)
                Ce = C_E;
        }
    }
    //create an array of all the decay products mass, same order of increasing mass (product_names[i] corresponds to product_mass[i])
    std::vector<double> product_masses = {0.000000001, 0.00000017, 0.0000182, 0.000511, 0.0022, 0.0047, 0.096, 0.10566,
                                          1.28, 1.7768, 4.18, 173.1};
    int masses_size = product_masses.size();

    //define an integer to be incremented as we compare our collision energy to our product mass array
    unsigned int counter = 0;
    int j = 0;
    while (j < masses_size && Ce >= 2.0 * product_masses[j]) {
        if (Ce > product_masses[j]) {
            counter++;
        }
        j++;
    }

    // now we create a "possible products" array, this is just a reduced length version of our product_arrays from above.
    int possible_products_size = counter;
    std::vector<double> possible_products(possible_products_size);

    for (int i = 0; i < possible_products_size; i++) {
        possible_products[i] = product_masses[i];
    }

    // define our range of allowed products, i.e. length of possible_products[], which is already stored as possible_products_size
    double distribution = 1.0 / possible_products_size;
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);
    for (int i = 0; i < Nexp; i++) {
        double randomNumber = (double) rand() / RAND_MAX;
            unsigned int outcome = randomNumber / distribution;
            std::cout << outcome << " ";
    }
    std::cout << std::endl;
    return 0;
}
