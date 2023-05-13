#include <TMath.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TStyle.h>

void simulation() {
    double trueMean = 50.0;
    double trueSigma = 3.0;

    // Create a random number generator
    TRandom3 rng;

    auto c4 = new TCanvas("c", "c", 600, 500);

    auto h1 = new TH1F("h1", "Energy Deposited in Detector;GeV;Counts", 100, 30, 150);
    h1->SetFillColor(kGreen);
    h1->SetFillStyle(3003);

    // Generate the data
    for (int i = 0; i < 10000; i++) {
    double x = rng.Landau(trueMean, trueSigma);
    double deviation = rng.Poisson(x) - x; // Calculate deviation from the mean
    double scaledDeviation = deviation * 0.2; // Scale down the deviation (pure smear was astromically large, idk if this is realistic or not)
    double smearedX = x + scaledDeviation; // Add scaled deviation back to the mean
    h1->Fill(smearedX);
    }

    // Print out Gaussian fit parameters
    std::cout << "Gaussian fit parameters:" << std::endl;

    // Fit a Gaussian function to the data
    auto g1 = new TF1("g1", "gaus", 30, 150);
    g1->SetParameters(1000, trueMean, trueSigma); // Initial parameter estimates
    h1->Fit(g1, "L"); 
    g1->Print();

    // Print out Landau fit parameters
    std::cout << "Landau fit parameters:" << std::endl;
    // Fit a Landau function to the data
    auto l1 = new TF1("l1", "landau", 30, 150);
    l1->SetParameters(1000, trueMean, trueSigma); // Initial parameter estimates for normalization, MPV (mean), and scale (sigma)
    h1->Fit(l1, "L+"); 
    l1->Print();

    // Print out Crystal Ball fit parameters
    std::cout << "Crystal Ball fit parameters:" << std::endl;
    // Fit a Crystal Ball function to the data
    auto cb1 = new TF1("cb1", "crystalball", 30, 150);
    cb1->SetParameters(100, trueMean, trueSigma, 1.5, 3.0); // Initial parameter estimates for normalization, mean, sigma, alpha, and n
    h1->Fit(cb1, "L+");
    cb1->Print();

    // Set line colors
    g1->SetLineColor(kBlue);
    l1->SetLineColor(kRed);
    cb1->SetLineColor(kMagenta);

    double chisq_g1 = g1->GetChisquare() / g1->GetNDF();
    double chisq_l1 = l1->GetChisquare() / l1->GetNDF();
    double chisq_cb1 = cb1->GetChisquare() / cb1->GetNDF();

    std::cout << "Gaussian chi-squared: " << chisq_g1 << std::endl;
    std::cout << "Landau chi-squared: " << chisq_l1 << std::endl;
    std::cout << "Crystal Ball chi-squared: " << chisq_cb1 << std::endl;

    // Determine the best fit
    std::string bestFit;
    double minChisq = std::min({chisq_g1, chisq_l1, chisq_cb1});

    if (minChisq == chisq_g1) {
        bestFit = "Gaussian";
    } else if (minChisq == chisq_l1) {
        bestFit = "Landau";
    } else {
        bestFit = "Crystal Ball";
    }

    std::cout << "Best fit: " << bestFit << std::endl;

    // Draw the histogram and fits
    h1->Draw("E");
    g1->Draw("same");
    l1->Draw("same");
    cb1->Draw("same");

    auto legend = new TLegend(0.1, 0.7, 0.3, 0.9);
    legend->AddEntry(h1, "Data", "lep");
    legend->AddEntry(g1, "Gaussian fit", "l");
    legend->AddEntry(l1, "Landau fit", "l");
    legend->AddEntry(cb1, "Crystal Ball fit", "l");
    legend->Draw();
}
