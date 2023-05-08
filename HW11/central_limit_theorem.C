#include <iostream>
#include <TRandom3.h>
#include <TH1F.h>
#include <TCanvas.h>

void central_limit_theorem(int N = 1000, int M = 10000)
{
    TRandom3 random_gen;

    TH1F h1("h1", "Central Limit Theorem;Normalized Sum;Frequency", 100, -10, 10);
    
    for (int i = 0; i < M; ++i)
    {
        double sum = 0;
        for (int j = 0; j < N; ++j)
        {
            // Sample from a uniform distribution in the range [-1, 1]
            double x = random_gen.Uniform(-1, 1);
            sum += x;
        }
        
        double normalized_sum = sum / sqrt(N);
        h1.Fill(normalized_sum);
    }

    // Normalize the histogram
    h1.Scale(1 / h1.Integral());

    TCanvas canvas("canvas", "Central Limit Theorem", 800, 600);
    h1.Draw();

    // Create the output filename with N and M included
    std::ostringstream filename;
    filename << "central_limit_theorem_N_" << N << "_M_" << M << ".png";
    canvas.Print(filename.str().c_str());
}