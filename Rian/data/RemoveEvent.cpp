#include <TFile.h>
#include <TTree.h>
#include <iostream>

void RemoveEvent(const char* inputFile,const char* outputFile,Long64_t eventToRemove) {
    // const char* inputFile =  "/home/oryan/laura/Rian/data/HighPurity_signal_m13m23_v8.root";
    // const char* outputFile = "/home/oryan/laura/Rian/data/HighPurity_signal_m13m23_v9.root";
    // Long64_t eventToRemove = 274;

    const char* treename="DecayTree";
    
    // Abrindo o arquivo de entrada
    TFile *fileIn = TFile::Open(inputFile, "READ");
    if (!fileIn || fileIn->IsZombie()) {
        std::cerr << "Erro ao abrir o arquivo: " << inputFile << std::endl;
        return;
    }
    
    // Obtendo a árvore
    TTree *treeIn = nullptr;
    fileIn->GetObject(treename, treeIn);
    if (!treeIn) {
        std::cerr << "Erro: TTree '" << treename << "' não encontrada no arquivo." << std::endl;
        fileIn->Close();
        return;
    }
    
    // Criando um novo arquivo e uma nova árvore
    TFile *fileOut = new TFile(outputFile, "RECREATE");
    TTree *treeOut = treeIn->CloneTree(0);
    
    // Loop sobre os eventos
    Long64_t nEntries = treeIn->GetEntries();
    for (Long64_t i = 0; i < nEntries; i++) {
        if (i == eventToRemove) continue; // Pular o evento a ser removido
        treeIn->GetEntry(i);
        treeOut->Fill();
    }
    
    // Salvando a nova árvore e fechando os arquivos
    treeOut->Write();
    fileOut->Close();
    fileIn->Close();
    
    std::cout << "Nova TTree salva em " << outputFile << " sem o evento " << eventToRemove << std::endl;
}

// Exemplo de uso no ROOT:
// root -l 'RemoveEvent("meuarquivo.root", "novoarquivo.root", "MinhaTree", 5)'