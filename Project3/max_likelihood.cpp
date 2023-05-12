#include <TMath.h>
#include <TMinuit.h>
#include <TRandom3.h>
#include <iostream>
#include <vector>

// Global variables
std::vector<double> myData;   // Vector to hold data

// Function to be minimized (negative log likelihood)
void fcn(int& npar, double* gin, double& f, double* par, int iflag) {
    double mu = par[0]; // Parameter of interest

    double lnL = 0;
    for (int i = 0; i < myData.size(); ++i) {
        double x = myData[i];
        lnL += TMath::Log(TMath::Gaus(x, mu, 1, kTRUE));
    }
    
    f = -lnL; // Minuit minimizes, so return negative log likelihood
}

void max_likelihood(int N) {
    // Generate data from a Gaussian distribution with mean = 5
    TRandom3 rand;
    myData.resize(N);
    for (int i = 0; i < N; ++i) {
        myData[i] = rand.Gaus(5, 1);
    }

    // Set up Minuit
    TMinuit minuit(1); // 1 parameter
    minuit.SetFCN(fcn);
    minuit.DefineParameter(0, "mu", 0, 0.1, -10, 10); // initial value, step size, lower limit, upper limit

    // Minimize
    minuit.Migrad();

    // Output results
    double muHat, muHatErr;
    minuit.GetParameter(0, muHat, muHatErr);
    std::cout << "N=" << N << ", muHat = " << muHat << " +/- " << muHatErr << std::endl;
}

void run_experiments() {
    std::vector<int> N_values = {10, 100, 1000, 10000};
    for (int N : N_values) {
        max_likelihood(N);
    }
}
