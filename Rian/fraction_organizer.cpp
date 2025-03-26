#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

int fraction_organizer(const char* outfile="Laura_v1") {
    gSystem->Load("libRIO");
    gSystem->Load("libHist");
    std::string sfile1 = (std::string) "/data1000/charmosinhos/Rian/Goofit3/GooFit/build/examples/D2PPK/Fit/" + outfile + (std::string) "/fractions.txt";
    std::string sfile2 = (std::string) "/data1000/charmosinhos/Rian/Goofit3/GooFit/build/examples/D2PPK/Fit/" + outfile + (std::string) "/fit_result.txt";
    // Abrir o arquivo fractions.txt
    std::ifstream fractionsFile(sfile1.c_str());
    if (!fractionsFile) {
        std::cerr << "Erro ao abrir fractions.txt" << std::endl;
        return 1;
    }

    std::vector<double> diagonalElements;
    std::string line;
    int rowCount = 0;

    while (std::getline(fractionsFile, line)) {
        std::istringstream iss(line);
        double value;
        int column = 0;
        
        while (iss >> value) {
            if (column == rowCount) {
                diagonalElements.push_back(value);
            }
            column++;
        }
        rowCount++;
    }
    fractionsFile.close();

    // Abrir o arquivo fit_result.txt
    std::ifstream fitFile(sfile2.c_str());
    if (!fitFile) {
        std::cerr << "Erro ao abrir fit_result.txt" << std::endl;
        return 1;
    }

    std::vector<std::string> truncatedNames;
    int lineIndex = 0;
    while (std::getline(fitFile, line)) {
        if (lineIndex % 2 == 0) {  // Pegar a cada 2 linhas
            std::istringstream iss(line);
            std::string element;
            iss >> element; // Pega a primeira coluna

            size_t pos = element.find('_AMP');
            if (pos != std::string::npos) {
                element = element.substr(0, pos); // Truncar no primeiro '_'
            }
            truncatedNames.push_back(element);
        }
        lineIndex++;
    }
    fitFile.close();
  
    // Criar arquivo de saída diagonal_fractions.txt
  std::string sfile3 = (std::string) "/data1000/charmosinhos/Rian/Goofit3/GooFit/build/examples/D2PPK/Fit/" + outfile + (std::string) "/diagonal_fractions.txt";
    std::ofstream outFile(sfile3.c_str());
    if (!outFile) {
        std::cerr << "Erro ao criar diagonal_fractions.txt" << std::endl;
        return 1;
    }

    for (size_t i = 0; i < diagonalElements.size() && i < truncatedNames.size(); ++i) {
        outFile << truncatedNames[i] << " " << diagonalElements[i] << "\n";
    }

    outFile.close();
    std::cout << "Arquivo diagonal_fractions.txt criado com sucesso!" << std::endl;
    
    return 0;
}
