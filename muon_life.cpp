#include "physics_data_analysis.h"

int main() {
    // Create histogram
    TH1F* hist = new TH1F("hist", "Muon Lifetime", 100, 0.0, 2.0);

    // Generate random numbers according to exponential distribution
    TRandom3 rand;
    double tau = 2.2;  // Lifetime of muon in microseconds
    for (int i = 0; i < 100000; i++) {
        double lifetime = rand.Exp(tau);
        hist->Fill(lifetime);
    }

    // Draw histogram
    TCanvas* c1 = new TCanvas("c1", "Muon Lifetime", 800, 600);
    hist->GetXaxis()->SetTitle("Lifetime (#mus)");
    hist->GetYaxis()->SetTitle("Counts");
    hist->Draw();

    // Save canvas as PDF
    c1->SaveAs("muon_lifetime.pdf");

    return 0;
}
