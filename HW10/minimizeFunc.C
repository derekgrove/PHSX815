#include <TF2.h>
#include <TCanvas.h>
#include <TMinuit.h>
#include <iostream>


void threeDfunction_function(Int_t &npar, Double_t *gin, Double_t &f, Double_t *x, Int_t iflag) {
    const Double_t a = 1.0;
    const Double_t b = 100.0;
    Double_t x_val = x[0];
    Double_t y_val = x[1];

    f = (a - x_val) * (a - x_val) + b * (y_val - x_val * x_val) * (y_val - x_val * x_val);
}

void graph_threeDfunction() {
    // Define the 3D function
    TF2 *threeDfunction = new TF2("threeDfunction", "(1 - x)**2 + 100 * (y - x**2)**2", -2, 2, -2, 2);

    // Create a canvas to draw the function
    TCanvas *canvas = new TCanvas("canvas", "3D Function", 800, 600);
    canvas->SetTheta(30);  // Adjust the viewing angle (theta)
    canvas->SetPhi(30);    // Adjust the viewing angle (phi)

    // Draw the function as a 3D surface
    threeDfunction->Draw("surf1");

    // Save the plot as an image
    canvas->SaveAs("threeDfunction.png");
}

void minimize_threeDfunction() {
    TMinuit *minimizer = new TMinuit(2); // Initialize TMinuit with 2 parameters (x and y)
    minimizer->SetFCN(threeDfunction_function); // Set the function to minimize

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    minimizer->mnexcm("SET ERR", arglist, 1, ierflg); // Set error definition to 1

    // Define the parameters
    minimizer->mnparm(0, "x", 0.5, 0.1, 0, 0, ierflg);
    minimizer->mnparm(1, "y", 0.5, 0.1, 0, 0, ierflg);

    arglist[0] = 1000; // Number of function calls
    arglist[1] = 1.0;  // Tolerance
    minimizer->mnexcm("MIGRAD", arglist, 2, ierflg); // Run MIGRAD minimization algorithm

    Double_t xmin, ymin, edm, errdef;
    Int_t nvpar, nparx, icstat;
    minimizer->mnstat(xmin, edm, errdef, nvpar, nparx, icstat);

    Double_t x_opt, y_opt, x_err, y_err;
    minimizer->GetParameter(0, x_opt, x_err);
    minimizer->GetParameter(1, y_opt, y_err);

    std::cout << "Minimum found at: x = " << x_opt << " +/- " << x_err
              << ", y = " << y_opt << " +/- " << y_err << std::endl;

    delete minimizer;
}


