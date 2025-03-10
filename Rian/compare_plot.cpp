#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TStyle.h>
#include <TColor.h>
#include <TCanvas.h>
#include <TLegend.h>

void compare_plot(const char* file1="/home/oryan/laura/Rian/data/HighPurity_signal_m13m23_v5069.root",
                  const char* file2="/home/oryan/laura/Rian/fitToyMC_0_expt0.root",
                  int indice=0)
{   const char* m13Sq = "m13Sq";
    const char* m23Sq = "m23Sq";
    const char* tree1 = "DecayTree";
    const char* tree2 = "genResults";
    // Abrindo os arquivos ROOT
    TFile *f1 = TFile::Open(file1);
    TFile *f2 = TFile::Open(file2);
    if (!f1 || !f2 || f1->IsZombie() || f2->IsZombie()) {
        printf("Erro ao abrir arquivos ROOT!\n");
        return;
    }
    
    // Obtendo as árvores
    TTree *t1 = (TTree*)f1->Get(tree1);
    TTree *t2 = (TTree*)f2->Get(tree2);
    if (!t1 || !t2) {
        printf("Erro ao acessar árvores!\n");
        return;
    }
    
    double M_D = 1.86966;
    double M_K = 0.49368;
    double M_P = 0.13957;

    double s13_min = (M_P + M_P)*(M_P + M_P);
    double s13_max = (M_D - M_K)*(M_D - M_K);
    double s23_min = (M_P + M_K)*(M_P + M_K);
    double s23_max = (M_D - M_P)*(M_D - M_P);


    // Criando histogramas
    TH1F *h1m13Sq = new TH1F("h1m13Sq", "s13", 200, s13_min, s13_max);
    TH1F *h2m13Sq = new TH1F("h2m13Sq", "s13", 200, s13_min, s13_max);

    TH1F *h1m23Sq = new TH1F("h1m23Sq", "s23", 200, s23_min, s23_max);
    TH1F *h2m23Sq = new TH1F("h2m23Sq", "s23", 200, s23_min, s23_max);

    h1m13Sq->GetXaxis()->SetTitle("s13 [GeV]^{2}");
    h1m13Sq->GetYaxis()->SetTitle("Events");

    h2m13Sq->GetXaxis()->SetTitle("s13 [GeV]^{2}");
    h2m13Sq->GetYaxis()->SetTitle("Events");

    h1m23Sq->GetXaxis()->SetTitle("s23 [GeV]^{2}");
    h1m23Sq->GetYaxis()->SetTitle("Events");

    h2m23Sq->GetXaxis()->SetTitle("s23 [GeV]^{2}");
    h2m23Sq->GetYaxis()->SetTitle("Events");

    TH2F* dalitz_dat_hist = new TH2F("dalitz_data_hist","",500,s13_min,s13_max,500,s23_min,s23_max);
    dalitz_dat_hist->GetXaxis()->SetTitle("s13 [GeV]^{2}");
    dalitz_dat_hist->GetYaxis()->SetTitle("s23 [GeV]^{2}");

    TH2F* dalitz_pdf_hist = new TH2F("dalitz_pdf_hist","",500,s13_min,s13_max,500,s23_min,s23_max);
    dalitz_pdf_hist->GetXaxis()->SetTitle("s13 [GeV]^{2}");
    dalitz_pdf_hist->GetYaxis()->SetTitle("s23 [GeV]^{2}");
    
    // Preenchendo histogramas
    
    t2->Draw(Form("%s >> h2m13Sq", m13Sq));
    t1->Draw(Form("%s >> h1m13Sq", m13Sq), "", "same");

    gStyle->SetPalette(kCherry);
    TColor::InvertPalette();
    // Criando canvas
    TCanvas *c = new TCanvas("c", "Fit and Data comparation", 1020, 720);
    // Ajustando o eixo Y para o máximo entre os dois histogramas
    double maxY13 = std::max(h1m13Sq->GetMaximum(), h2m13Sq->GetMaximum());
    h1m13Sq->SetMaximum(maxY13 * 1.1); // Aumenta um pouco o limite para melhor visualização
    h2m13Sq->SetLineColor(kRed-4);
    h1m13Sq->SetLineWidth(1);
    h2m13Sq->SetLineWidth(1);
    h1m13Sq->SetLineColor(kBlue+1);
    h1m13Sq->Draw();
    h2m13Sq->Draw("same");
    
    
    // Adicionando legenda
    TLegend *legend1 = new TLegend(0.78, 0.68, 0.98, 0.78);
    legend1->AddEntry(h1m13Sq, "Data", "F");
    legend1->AddEntry(h2m13Sq, "Fit", "F");
    legend1->Draw();

    std::string output1 = "Fit_Results_" + std::to_string(indice) + "/s13_fit_" + std::to_string(indice) + "_.png";
    // Salvando o histograma
    c->SaveAs(output1.c_str());



    // Preenchendo histogramas
    t2->Draw(Form("%s >> h2m23Sq", m23Sq));
    t1->Draw(Form("%s >> h1m23Sq", m23Sq), "", "same");
    
    double maxY23 = std::max(h1m23Sq->GetMaximum(), h2m23Sq->GetMaximum());
    h1m23Sq->SetMaximum(maxY23 * 1.1); // Aumenta um pouco o limite para melhor visualização
    h2m23Sq->SetLineColor(kRed-4);
    h1m23Sq->SetLineColor(kBlue+1);
    h1m23Sq->SetLineWidth(1);
    h2m23Sq->SetLineWidth(1);
    h1m23Sq->Draw();
    h2m23Sq->Draw("same");
    
    // Adicionando legenda
    TLegend *legend2 = new TLegend(0.78, 0.68, 0.98, 0.78);
    legend2->AddEntry(h1m23Sq, "Data", "F");
    legend2->AddEntry(h2m23Sq, "Fit", "F");
    legend2->Draw();

    std::string output2 ="Fit_Results_" + std::to_string(indice) + "/s23_fit_" + std::to_string(indice) + "_.png";
    // Salvando o histograma
    c->SaveAs(output2.c_str());


    t1->Draw("m23Sq:m13Sq >> dalitz_data_hist","","COLZ");
    std::string output3 = "Fit_Results_" + std::to_string(indice) + "/Dalitz_data_hist.png";
    // Salvando o histograma
    c->SaveAs(output3.c_str());

    t2->Draw("m23Sq:m13Sq >> dalitz_pdf_hist","","COLZ");
    std::string output4 = "Fit_Results_" + std::to_string(indice) + "/Dalitz_pdf_hist_fit_" + std::to_string(indice) + "_.png";
    // Salvando o histograma
    c->SaveAs(output4.c_str());

    
    // Limpando memória
    delete h1m13Sq;
    delete h2m13Sq;
    delete h1m23Sq;
    delete h2m23Sq;
    delete dalitz_dat_hist;
    delete dalitz_pdf_hist;
    delete c;
    delete legend1;
    delete legend2;
    f1->Close();
    f2->Close();
}