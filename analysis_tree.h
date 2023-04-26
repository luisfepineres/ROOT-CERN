#include "physics_data_analysis.h"

void analyzeTree(TTree* tree) {
  // Get the list of branches in the tree
  TObjArray* branches = tree->GetListOfBranches();

  // Loop over the branches and create a histogram for each one
  for (int i = 0; i < branches->GetEntries(); i++) {
    TBranch* branch = (TBranch*)branches->At(i);
    std::string branchName = branch->GetName();
    std::string histogramName = "h_" + branchName;
    std::string histogramTitle = "Histogram of " + branchName;
    TH1F* histogram = new TH1F(histogramName.c_str(), histogramTitle.c_str(), 100, -500, 500);
    tree->Project(histogramName.c_str(), branchName.c_str());
    histogram->Write();
  }
}
