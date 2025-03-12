#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "TFile.h"
#include "TTree.h"


int amp_phs_fit_organizer(int indice = 0) {
    // Abre o arquivo integ.dat
    std::ifstream inputFile("integ.dat");
    if (!inputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo integ.dat!" << std::endl;
        return 1;
    }

    // Lê a primeira linha (cabeçalho) e descarta
    std::string headerLine;
    std::getline(inputFile, headerLine);

    // Lê a segunda linha (nomes das ressonâncias)
    std::string resonanceLine;
    std::getline(inputFile, resonanceLine);

    // Fecha o arquivo
    inputFile.close();

    // Usa um stringstream para separar os nomes das ressonâncias
    std::istringstream iss(resonanceLine);
    std::vector<std::string> resonances;
    std::string resonance;

    // Extrai os nomes das ressonâncias
    while (iss >> resonance) {
        resonances.push_back(resonance);
    }

    // Exibe os nomes das ressonâncias e a quantidade encontrada
    std::cout << "Ressonances:" << std::endl;
    for (const auto& res : resonances) {
        std::cout << "- " << res << std::endl;
    }
    std::cout << "Number of Ressonances: " << resonances.size() << std::endl;
    std::cout << "        "<< std::endl;




    // Define o nome do arquivo ROOT
    std::string rootFileName = "fitDpipiK_" + std::to_string(indice) + "_expt_0-0.root";

    // Abre o arquivo ROOT
    TFile* file = TFile::Open(rootFileName.c_str(), "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Erro ao abrir o arquivo: " << rootFileName << std::endl;
        return 1;
    }

    // Acessa a TTree "fitResults"
    TTree* tree = (TTree*)file->Get("fitResults");
    if (!tree) {
        std::cerr << "Erro ao acessar a TTree 'fitResults'." << std::endl;
        file->Close();
        return 1;
    }

    // Abre o arquivo de texto para salvar os dados
    std::ofstream outFile( "Fit_Results_" + std::to_string(indice) +"/Fit_results_" + std::to_string(indice) + "_.txt");
    if (!outFile.is_open()) {
        std::cerr << "Erro ao criar o arquivo de saída." << std::endl;
        file->Close();
        return 1;
    }
    Double_t sum_FitFrac;

    std::cout << "Fit Results:"<< std::endl;
    std::cout << "        "<< std::endl;
    int i=0;
    for (const auto& res : resonances) {

        Double_t Amp, Phase, FitFrac, Amp_error, Phase_error;
        std::string Amp_string = "A" + std::to_string(i) + "_A";
        std::string Phase_string = "A" + std::to_string(i) + "_Delta";
        std::string FitFrac_string = "A" + std::to_string(i) + "Sq_FitFrac";
        std::string Amp_error_string = "A" + std::to_string(i) + "_A_Error";
        std::string Phase_error_string = "A" + std::to_string(i) + "_Delta_Error";


        // Associa as branches às variáveis
        tree->SetBranchAddress(Amp_string.c_str(), &Amp);
        tree->SetBranchAddress(Phase_string.c_str(), &Phase);
        tree->SetBranchAddress(FitFrac_string.c_str(), &FitFrac);

        if(i!=0){
            tree->SetBranchAddress(Amp_error_string.c_str(), &Amp_error);
            tree->SetBranchAddress(Phase_error_string.c_str(), &Phase_error);
        }

    
        tree->GetEntry(0);
        sum_FitFrac+=FitFrac;

        // Exibe os valores no terminal
        std::cout <<  res << std::endl;
        if(i==0){
            std::cout << "Amp: " << Amp  << " Fixed" << std::endl;
            std::cout << "Phase: " << Phase << " Fixed" << std::endl;
        }
        else{
            std::cout << "Amp: " << Amp << " ± " << Amp_error << std::endl;
            std::cout << "Phase: " << Phase << " ± " << Phase_error<< std::endl;
        }
        std::cout << "Fit Fraction: " << FitFrac << std::endl;
        std::cout << "           " << std::endl;

        // Salva os valores no arquivo de texto
        outFile <<  res << std::endl;
        if(i==0){
            outFile << "Amp: " << Amp  << " Fixed" << std::endl;
            outFile << "Phase: " << Phase << " Fixed" << std::endl;
        }
        else{
            outFile << "Amp: " << Amp << " ± " << Amp_error << std::endl;
            outFile << "Phase: " << Phase << " ± " << Phase_error<< std::endl;
        }
        outFile << "Fit Fraction: " << FitFrac << std::endl;
        outFile << "           " << std::endl;
    
        i++;
    }

    std::cout << "Sum Diagonal Fit Fractions: " << sum_FitFrac << std::endl;
    std::cout << "           " << std::endl;

    outFile << "Sum Diagonal Fit Fractions: " << sum_FitFrac << std::endl;
    outFile << "           " << std::endl;


    // Fecha o arquivo de texto
    outFile.close();

    // Fecha o arquivo ROOT
    file->Close();

    std::cout << "Data saved in Fit_results_" << indice << "_.txt" << std::endl;


    return 0;
}