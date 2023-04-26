#include "physics_data_analysis.h"
void analyzeTree(TFile* inputFile, TTree* inputTree, TFile* outputFile) {
  // Create histograms for each branch in the tree
  TObjArray* branches = inputTree->GetListOfBranches();
  int numBranches = branches->GetEntriesFast();
  TH1F** histos = new TH1F*[numBranches];
  for (int i = 0; i < numBranches; i++) {
    TBranch* branch = (TBranch*)branches->At(i);
    std::string histoName = std::string(branch->GetName()) + "_histo";
    std::string histoTitle = std::string(branch->GetName()) + " Distribution";
    histos[i] = new TH1F(histoName.c_str(), histoTitle.c_str(), 100, -500, 500);
  }

  // Loop over the entries in the tree and fill the histograms
  Long64_t numEntries = inputTree->GetEntries();
  for (Long64_t jentry = 0; jentry < numEntries; jentry++) {
    inputTree->GetEntry(jentry);
    for (int i = 0; i < numBranches; i++) {
      TBranch* branch = (TBranch*)branches->At(i);
      if (branch->IsA()->InheritsFrom("TLeaf")) {
        TLeaf* leaf = (TLeaf*)branch->GetListOfLeaves()->At(0);
        histos[i]->Fill(leaf->GetValue());
      }
    }
  }

  // Write histograms to output file
  outputFile->cd();
  for (int i = 0; i < numBranches; i++) {
    histos[i]->Write();
  }
  outputFile->Close();

  // Clean up memory
  for (int i = 0; i < numBranches; i++) {
    delete histos[i];
  }
  delete[] histos;
}
