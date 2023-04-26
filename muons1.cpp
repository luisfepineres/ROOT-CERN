#include "physics_data_analysis.h"

int main(int argc, char** argv) {

  // Verificar si se ingresaron los argumentos adecuados
  if (argc != 3) {
    std::cout << "Ingrese el número de eventos y el nombre del archivo de salida." << std::endl;
    return 1;
  }

  // Convertir los argumentos de entrada en variables numéricas
  const int nEvents = std::stoi(argv[1]);
  const std::string fileName = argv[2];

  // Crear un generador de números aleatorios
  TRandom3 rng;

  // Crear vectores para almacenar la información de los muones generados
  std::vector<double> pxValues;
  std::vector<double> pyValues;
  std::vector<double> pzValues;
  std::vector<double> energyValues;
  std::vector<double> massValues;

  // Generar nEvents eventos y calcular su información
  for (int i = 0; i < nEvents; ++i) {

    // Generar las componentes del momento aleatorias
    double px = rng.Gaus(0.0, 100.0);
    double py = rng.Gaus(0.0, 100.0);
    double pz = rng.Gaus(0.0, 100.0);

    // Calcular la energía y la masa del muón
    double energy = std::sqrt(px*px + py*py + pz*pz + 105.658*105.658);
    double mass = std::sqrt(energy*energy - px*px - py*py - pz*pz);

    // Almacenar la información de los muones en los vectores
    pxValues.push_back(px);
    pyValues.push_back(py);
    pzValues.push_back(pz);
    energyValues.push_back(energy);
    massValues.push_back(mass);

  }

  // Crear un archivo ROOT
  TFile* outputFile = new TFile(fileName.c_str(), "RECREATE");

  // Crear un árbol y agregar las ramas para las variables de los muones
  TTree* outputTree = new TTree("muonTree", "Muon tree");
  double px, py, pz, energy, mass;
  outputTree->Branch("px", &px);
  outputTree->Branch("py", &py);
  outputTree->Branch("pz", &pz);
  outputTree->Branch("energy", &energy);
  outputTree->Branch("mass", &mass);

  // Llenar el árbol con la información de los muones
  for (int i = 0; i < nEvents; ++i) {
    px = pxValues[i];
    py = pyValues[i];
    pz = pzValues[i];
    energy = energyValues[i];
    mass = massValues[i];
    outputTree->Fill();
  }

  // Guardar el árbol y cerrar el archivo
  outputTree->Write();
  outputFile->Close();

  std::cout << "Archivo " << fileName << " guardado exitosamente con " << nEvents << " muones." << std::endl;

  return 0;
}