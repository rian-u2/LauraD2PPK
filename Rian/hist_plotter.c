#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>

void hist_plotter() {
    

    int j = 17;

    // Abrir os arquivos ROOT
    std::string rootFileName1 = "/home/oryan/laura/Rian/GooFit_comp_Toys_" + std::to_string(j) + "/data.root";
    std::string rootFileName2 = "/home/oryan/laura/Rian/GooFit_comp_Toys_" + std::to_string(j) + "/Goofit_Toy_" + std::to_string(j)+ ".root";


    TFile *file1 = new TFile(rootFileName1.c_str(), "READ");
    TFile *file2 = new TFile(rootFileName2.c_str(), "READ");

    // Acessar as trees
    TTree *tree1 = (TTree*)file1->Get("DecayTree");
    TTree *tree2 = (TTree*)file2->Get("Red_Tree");

    double M_D = 1.86966;
    double M_K = 0.49368;
    double M_P = 0.13957;

    double s13_min = (M_P + M_P)*(M_P + M_P);
    double s13_max = (M_D - M_K)*(M_D - M_K);
    double s23_min = (M_P + M_K)*(M_P + M_K);
    double s23_max = (M_D - M_P)*(M_D - M_P);


    // Criar histogramas
    TH1F *hist1 = new TH1F("hist1", "", 200, s13_min, s13_max); // Ajustar range conforme necessário
    TH1F *hist2 = new TH1F("hist2", "", 200, s13_min, s13_max); // Ajustar range conforme necessário

    // Preencher histogramas com branches específicas
    tree1->Draw("m13Sq>>hist1"); // Substituir branch_name1 pelo nome real
    tree2->Draw("m12Sq>>hist2"); // Substituir branch_name2 pelo nome real

    // Normalizar histogramas
    // hist1->Scale(1.0 / hist1->Integral());
    // hist2->Scale(1.0 / hist2->Integral());

    // Configurar cores e estilos
    hist1->SetLineColor(kBlue);
    hist2->SetLineColor(kRed);

    hist1->SetStats(0);
    hist2->SetStats(0);

    // Criar canvas
    TCanvas *canvas = new TCanvas("canvas", "Normalized Histograms", 800, 800);

    // Desenhar histogramas
    hist1->Draw("HIST");
    hist2->Draw("HIST SAME");

    // Configurar título e eixos
    hist1->SetTitle("Laura++ vs GooFit");
    hist1->GetXaxis()->SetTitle("m^{2}_{#pi^{-}#pi^{+}} [GeV^{2}/c^{4}]");
    hist1->GetXaxis()->SetTitleSize(0.04);
    hist1->GetYaxis()->SetTitleSize(0.04);

    // Criar legenda
    TLegend *legend = new TLegend(0.85, 0.85, 1, 1);
    legend->AddEntry(hist1, "Laura++", "l");
    legend->AddEntry(hist2, "GooFit", "l");
    legend->Draw();

    // Salvar o canvas (opcional)
    std::string output1 = "/home/oryan/laura/Rian/GooFit_comp_Toys_" + std::to_string(j) + "/Reson_Comp_s12_"+ std::to_string(j) +".png";
    canvas->SaveAs(output1.c_str());

////////////////////////////////////////////////////////////////////////////////////


    // Criar histogramas
    TH1F *hist3 = new TH1F("hist3", "", 200, s23_min, s23_max); // Ajustar range conforme necessário
    TH1F *hist4 = new TH1F("hist4", "", 200, s23_min, s23_max); // Ajustar range conforme necessário

    // Preencher histogramas com branches específicas
    tree1->Draw("m23Sq>>hist3"); // Substituir branch_name1 pelo nome real
    tree2->Draw("m13Sq>>hist4"); // Substituir branch_name2 pelo nome real

    // Normalizar histogramas
    // hist1->Scale(1.0 / hist1->Integral());
    // hist2->Scale(1.0 / hist2->Integral());

    // Configurar cores e estilos
    hist3->SetLineColor(kBlue);
    hist4->SetLineColor(kRed);

    hist3->SetStats(0);
    hist4->SetStats(0);

 

    // Desenhar histogramas
    hist3->Draw("HIST");
    hist4->Draw("HIST SAME");

    // Configurar título e eixos
    hist3->SetTitle("Laura++ vs GooFit");
    hist3->GetXaxis()->SetTitle("m^{2}_{#pi^{-}K^{+}} [GeV^{2}/c^{4}]");
    hist3->GetXaxis()->SetTitleSize(0.04);
    hist3->GetYaxis()->SetTitleSize(0.04);

    // Criar legenda
    TLegend *legend1 = new TLegend(0.85, 0.85, 1, 1);
    legend1->AddEntry(hist3, "Laura++", "l");
    legend1->AddEntry(hist4, "GooFit", "l");
    legend1->Draw();


    // Salvar o canvas (opcional)
    std::string output2 = "/home/oryan/laura/Rian/GooFit_comp_Toys_" + std::to_string(j) + "/Reson_Comp_s13_"+ std::to_string(j) +".png";
    canvas->SaveAs(output2.c_str());



    // Fechar arquivos (opcional, evita memory leak)
    file1->Close();
    file2->Close();
}