#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main() {
    std::ifstream file("data.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file\n";
        return 1;
    }

    std::string line;
    std::getline(file, line);
    std::istringstream iss(line);
    std::vector<int> data;
    int x;
    while (iss >> x) {
        data.push_back(x);
    }
    file.close();
    // ...
}
