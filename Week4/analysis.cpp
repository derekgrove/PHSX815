#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void analysis() {

    // Create a 1D histogram with 12 bins from 0 to 12.
    TH1F *hist = new TH1F("hist", "Particle Distribution from e+e- collision;Value;Frequency", 12, 0, 12);

    // Define the bin labels.
    std::vector<std::string> product_names = {"#nu_{e}", "#nu_{#mu}", "#nu_{#tau}", "e", "u", "d", "s",
                                          "#mu", "c", "#tau", "b", "t"};

    // Set the bin labels.
    for (size_t i = 0; i < product_names.size(); ++i) {
        hist->GetXaxis()->SetBinLabel(i + 1, product_names[i].c_str());
    }

    // Open the .txt file.
    std::ifstream file("data.txt");
    std::string line;

    // Check if the file is open.
    if (file.is_open()) {
        // Read the file line by line.
        while (getline(file, line)) {
            // Use a string stream to split the line into separated strings.
            std::istringstream ss(line);
            std::string value;

            // Process each string in the line.
            while (getline(ss, value, ' ')) {
                // Convert the string to an integer.
                int i = std::stoi(value);

                // Fill the histogram with the integer.
                hist->Fill(i);
            }
        }

        // Close the file.
        file.close();
    } else {
        std::cout << "Unable to open the file." << std::endl;
        return;
    }

    // Create a canvas to draw the histogram.
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    hist->Draw();

    // Save the histogram as a .png file.
    c1->SaveAs("histogram.png");
}
