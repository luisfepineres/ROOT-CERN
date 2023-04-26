#include "analysis_tree.h"

int main(int argc, char** argv) {
  // Check that the correct number of arguments have been provided
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " input_file.root tree_name" << std::endl;
    return 1;
  }

  // Get the input and output file names from the command line arguments
  std::string inputFileName = argv[1];
  std::string treeName = argv[2];
  //std::string outputFileName = argv[3];

  // Open the input file and get the tree
  TFile* inputFile = new TFile(inputFileName.c_str(), "READ");
  if (!inputFile) {
    std::cerr << "Error: Could not open input file \"" << inputFileName << "\"" << std::endl;
    return 1;
  }
  TTree* inputTree = (TTree*)inputFile->Get(treeName.c_str());
  if (!inputTree) {
    std::cerr << "Error: Could not find tree \"" << treeName << "\" in file \"" << inputFileName << "\"" << std::endl;
    return 1;
  }

  // Create the output file with a name based on the current date and time
  time_t now = time(0);
  struct tm tstruct;
  char dateTime[80];
  tstruct = *localtime(&now);
  strftime(dateTime, sizeof(dateTime), "%Y-%m-%d_%H-%M-%S", &tstruct);
  std::string outputFileNameWithDate = "Muons_Tree_Analysis_" + std::string(dateTime) + ".root";
  TFile* outputFile = new TFile(outputFileNameWithDate.c_str(), "RECREATE");

  // Analyze the tree and save the histograms to the output file
  analyzeTree(inputTree);
  

  // Close the input and output files
  inputFile->Close();
  outputFile->Close();

  // Clean up memory
  delete inputFile;
  delete outputFile;

  return 0;
}

