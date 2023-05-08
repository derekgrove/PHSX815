#include <iostream>
#include <cmath>
#include <vector>
#include <TCanvas.h>
#include <TGraph.h>
#include <TRandom3.h>
#include <TAxis.h>
#include <TMultiGraph.h>

const int kNumPoints = 1000;
const int kNumClusters = 3;
const int kMaxIterations = 1000;

// Generate data from a mixture model
std::vector<std::pair<double, double>> generateData(TRandom3 &random) {
    std::vector<std::pair<double, double>> data(kNumPoints);
    double means[kNumClusters][2] = {{2, 2}, {8, 8}, {4, 10}};
    double sigma[kNumClusters] = {1.5, 2.0, 1.0};

    for (int i = 0; i < kNumPoints; ++i) {
        int cluster = random.Integer(kNumClusters);
        double x = random.Gaus(means[cluster][0], sigma[cluster]);
        double y = random.Gaus(means[cluster][1], sigma[cluster]);
        data[i] = std::make_pair(x, y);
    }

    return data;
}

// Calculate Euclidean distance between two points
double euclideanDistance(const std::pair<double, double> &a, const std::pair<double, double> &b) {
    return std::sqrt(std::pow(a.first - b.first, 2) + std::pow(a.second - b.second, 2));
}

// Implement the K-means clustering algorithm and apply it to the data
std::vector<int> kMeans(const std::vector<std::pair<double, double>> &data) {
    std::vector<int> labels(kNumPoints);
    std::pair<double, double> centroids[kNumClusters];
    TRandom3 random;

    // Initialize centroids randomly
    for (int i = 0; i < kNumClusters; ++i) {
        int idx = random.Integer(kNumPoints);
        centroids[i] = data[idx];
    }

    bool converged = false;
    int iterations = 0;

    while (!converged && iterations < kMaxIterations) {
        converged = true;

        // Assign each point to the nearest centroid
        for (int i = 0; i < kNumPoints; ++i) {
            int nearestCentroid = -1;
            double minDistance = std::numeric_limits<double>::max();

            for (int j = 0; j < kNumClusters; ++j) {
                double distance = euclideanDistance(data[i], centroids[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestCentroid = j;
                }
            }

            if (labels[i] != nearestCentroid) {
                labels[i] = nearestCentroid;
                converged = false;
            }
        }

        // Update centroids
        for (int i = 0; i < kNumClusters; ++i) {
            double sumX = 0;
            double sumY = 0;
            int count = 0;

            for (int j = 0; j < kNumPoints; ++j) {
                if (labels[j] == i) {
                    sumX += data[j].first;
                    sumY += data[j].second;
                    count++;
                }
            }

            if (count > 0) {
                centroids[i].first = sumX / count;
                centroids[i].second = sumY / count;
            }
        }

        iterations++;
    }

    return labels;
}

void visualizeData(const std::vector<std::pair<double, double>> &data, const std::vector<int> &labels) {
    TCanvas *canvas = new TCanvas("canvas", "K-means Clustering", 600, 600);
    TMultiGraph *multiGraph = new TMultiGraph();
    TGraph *graphs[kNumClusters];

    for (int i = 0; i < kNumClusters; ++i) {
        graphs[i] = new TGraph();
        graphs[i]->SetMarkerColor(i + 2);
        graphs[i]->SetMarkerStyle(20);
    }

    for (int i = 0; i < kNumPoints; ++i) {
        int cluster = labels[i];
        graphs[cluster]->SetPoint(graphs[cluster]->GetN(), data[i].first, data[i].second);
    }

    for (int i = 0; i < kNumClusters; ++i) {
        multiGraph->Add(graphs[i]);
    }

    multiGraph->SetTitle("K-means Clustering;X;Y");
    multiGraph->Draw("AP");
    canvas->Update();
    canvas->SaveAs("kmeans_clustering.png");
    delete canvas;
}

void kmeans() {
    TRandom3 random;
    std::vector<std::pair<double, double>> data = generateData(random);
    std::vector<int> labels = kMeans(data);
    visualizeData(data, labels);
}
