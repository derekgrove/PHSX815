#include <TCanvas.h>
#include <TRandom3.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TF1.h>
#include <vector>
#include <cmath>

// Define the Gaussian Kernel
double GaussianKernel(double x, double xi, double bandwidth) {
    return (1.0 / (sqrt(2 * M_PI) * bandwidth)) * exp(-0.5 * pow((x - xi) / bandwidth, 2));
}

// Estimate the density using Gaussian Kernel Density Estimation
std::vector<double> GaussKDE(std::vector<double>& data, double bandwidth, double xmin, double xmax, unsigned int nPoints) {
    double step = (xmax - xmin) / (nPoints - 1);
    std::vector<double> densityEstimate(nPoints, 0.0);
    for (unsigned int i = 0; i < nPoints; ++i) {
        double x = xmin + i * step;
        for (double xi : data) {
            densityEstimate[i] += GaussianKernel(x, xi, bandwidth);
        }
        densityEstimate[i] /= data.size();
    }
    return densityEstimate;
}

void GaussKDE() {
    // Create a random number generator
    TRandom3 rng;

    // Generate a sample from a Gaussian distribution
    unsigned int nSamples = 10000;
    std::vector<double> data(nSamples);
    for (unsigned int i = 0; i < nSamples; ++i) {
        data[i] = rng.Gaus(0, 1);
    }

    // Define the range and bandwidth
    double xmin = -5, xmax = 5, bandwidth = 0.1;
    unsigned int nPoints = 1000;

    // Estimate the density
    std::vector<double> densityEstimate = GaussKDE(data, bandwidth, xmin, xmax, nPoints);

    // Create a canvas
    TCanvas* canvas = new TCanvas("canvas", "Gaussian KDE", 800, 600);

    // Create a histogram of the data
    TH1F* hData = new TH1F("hData", "Data;X;Density", nPoints, xmin, xmax);
    for (double xi : data) {
        hData->Fill(xi);
    }
    hData->Scale(1.0 / (hData->GetBinWidth(1) * nSamples)); // Normalize to form a density
    hData->SetLineColor(kBlue);
    hData->Draw();

    // Draw the density estimate
    TGraph* grDensityEstimate = new TGraph(nPoints);
    for (unsigned int i = 0; i < nPoints; ++i) {
        double x = xmin + i * (xmax - xmin) / (nPoints - 1);
        grDensityEstimate->SetPoint(i, x, densityEstimate[i]);
    }
    grDensityEstimate->SetLineColor(kRed);
    grDensityEstimate->Draw("L SAME");

    canvas->SaveAs("GaussKDE.png");
}
