#include <TFile.h>
#include <TTree.h>
#include <iostream>

void RenameBranches(const char* inputFile = "/home/oryan/laura/Rian/data/HighPurity_signal_s12s13.root",
                          const char* outputFile = "/home/oryan/laura/Rian/data/HighPurity_signal_m13m23.root") {
    // Abrir o arquivo de entrada
    TFile *inFile = TFile::Open(inputFile, "READ");
    if (!inFile || inFile->IsZombie()) {
        std::cerr << "Erro ao abrir o arquivo ROOT!\n";
        return;
    }

    // Obter a árvore original
    TTree *oldTree = (TTree*) inFile->Get("DecayTree");
    if (!oldTree) {
        std::cerr << "Erro: TTree não encontrada!\n";
        inFile->Close();
        return;
    }

    // Criar novo arquivo de saída
    TFile *outFile = new TFile(outputFile, "RECREATE");

    // Criar uma nova árvore
    TTree *newTree = new TTree("DecayTree", "Árvore com branches renomeadas");

    // Definir os nomes das branches antigas e os novos nomes
    Double_t m12Sq, m13Sq;  // Variáveis para armazenar os valores das branches originais
    Double_t new_m13Sq, new_m23Sq;  // Variáveis para armazenar os valores das novas branches

    oldTree->SetBranchAddress("m12Sq", &m12Sq);
    oldTree->SetBranchAddress("m13Sq", &m13Sq);

    // Criar novas branches com os nomes desejados
    newTree->Branch("m13Sq", &new_m13Sq);
    newTree->Branch("m23Sq", &new_m23Sq);

    // Loop sobre as entradas da árvore original para copiar os dados
    Long64_t nEntries = oldTree->GetEntries();
    for (Long64_t i = 0; i < nEntries; ++i) {
        oldTree->GetEntry(i);

        // Copiar os valores para as novas branches
        new_m13Sq = m12Sq;
        new_m23Sq = m13Sq;

        newTree->Fill();  // Preencher a nova árvore com os valores modificados
    }

    // Escrever nova árvore no arquivo e fechar arquivos
    newTree->Write();
    outFile->Close();
    inFile->Close();

    std::cout << "Arquivo salvo como " << outputFile << " com branches renomeadas permanentemente!\n";
}
