#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <chrono>

int main(int argc, char *argv[]) {
    //define collision energy here, needs to be configurable via terminal. This is just the default value:
    double Ce = 5;
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
    //Ask KC why the nuetrinos oscillate if they have different masses? and by this much? seems impossible.

    // here is where we need to check our collision energy against our array of product masses, remember, 2x the product masses because
    // we will be making one matter and one antimatter pair.

    //define an integer to be incremented as we compare our collision energy to our product mass array
    unsigned int counter = 0;
    int j = 0;
    while (j < masses_size && Ce >= 2.0 * product_masses[j]) {
        if (Ce > product_masses[j]) {
            counter++;
        }
        j++;
    }

    //std::cout << "Counter: " << counter << std::endl;

    // now we create a "possible products" array, this is just a reduced length version of our product_arrays from above.
    // For our chosen collision energy, these are the possible outcomes.
    int possible_products_size = counter;
    std::vector<double> possible_products(possible_products_size);

    for (int i = 0; i < possible_products_size; i++) {
        possible_products[i] = product_masses[i];
    }
    std::cout << "from an electron-positron collision at collision energy = " << Ce << " GeV, possible outcomes are: "
              << std::endl;
    // Print the name of the possible final state particles
    for (int i = 0; i < possible_products_size; i++) {
        std::cout << product_names[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "these final state particles have corresponding masses (in units of GeV/c^2) of: " << std::endl;

    // Print the new array of masses
    for (int i = 0; i < possible_products_size; i++) {
        std::cout << possible_products[i] << " ";
    }
    std::cout << std::endl;



    // define our range of allowed products, i.e. length of possible_products[], which is already stored as possible_products_size
    double distribution = 1.0 / possible_products_size;
    //std::cout << distribution << std::endl;
    // ok, our probability distribution is broken up evenly into groups of integer multiplications of our 'distribution' double defined above
    // so, just generate a number between 0 and 1.0 and do arithmatic to figure out which integer multiplication of our distribution

    // generate random double between 0 and 1, will use the current time in nanoseconds to give us much more diverse random numbers when running this
    // program back to back.

    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);
    std::cout << "generated decay products for Nexp = " << Nexp << std::endl;
    for (int i = 0; i < Nexp; i++) {
        double randomNumber = (double) rand() / RAND_MAX;
        //std::cout << "Random number between 0 and 1: " << randomNumber << std::endl;
            unsigned int outcome = randomNumber / distribution;
            std::cout << product_names[outcome] << " ";
    }
    std::cout << std::endl;
    // std::cout << possible_products[i] << " ";
    return 0;
}
