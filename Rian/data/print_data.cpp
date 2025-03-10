#include <TFile.h>
#include <TTree.h>
#include <iostream>

void print_data(const char* filename = "/home/oryan/laura/Rian/data/HighPurity_signal_m13m23_v2.root", const char* treename = "DecayTree", const char* branch1 = "m13Sq", const char* branch2 = "m23Sq") {
    // Abrindo o arquivo ROOT
    TFile *file = TFile::Open(filename, "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return;
    }
    
    // Obtendo a árvore
    TTree *tree = nullptr;
    file->GetObject(treename, tree);
    if (!tree) {
        std::cerr << "Erro: TTree '" << treename << "' não encontrada no arquivo." << std::endl;
        file->Close();
        return;
    }
    
    // Criando variáveis para armazenar os valores das branches
    double value1, value2;
    tree->SetBranchAddress(branch1, &value1);
    tree->SetBranchAddress(branch2, &value2);
    
    // Loop sobre os eventos
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < 37; i++) {
        tree->GetEntry(i);
        std::cout << "Evento " << i << ": " << branch1 << " = " << value1 << ", " << branch2 << " = " << value2 << std::endl;
    }
    
    // Fechando o arquivo
    file->Close();
}

// Exemplo de uso no ROOT:
// root -l 'ReadTree("meuarquivo.root", "MinhaTree", "BranchA", "BranchB")'
