void plotComplexVars( TString fileName="test.root" )
{
	TFile *_file0 = TFile::Open( fileName );
	TTree *fitResults = dynamic_cast<TTree *>(_file0->Get("fitResults"));
	fitResults->GetEntry(0);

	TCanvas * c1 = new TCanvas("c1","c1",500,500);
	TH2F histo("histo","histo",120,-1.2,1.2,120,-1.2,1.2);
	histo.Draw();

	// draw grid
	gStyle->SetLineWidth(1);
	gStyle->SetLineStyle(3);
	TEllipse ellipse2( 0.0, 0.0, 1.0, 1.0); ellipse2.Draw();
	TEllipse ellipse1( 0.0, 0.0, 0.5, 0.5); ellipse1.Draw();
	TLine lh( -1.2, 0.0, 1.2, 0.0); lh.Draw();
	TLine lv( 0.0, -1.2, 0.0, 1.2); lv.Draw();

	// draw results
	fitResults->SetMarkerColor(2); 
	fitResults->SetMarkerStyle(1);
	fitResults->Draw("A1_Y:A1_X","","same");
	fitResults->SetMarkerColor(1); 
	fitResults->SetMarkerStyle(2);
	fitResults->Draw("A1_Y_True:A1_X_True","","same");

	fitResults->SetMarkerColor(3); 
	fitResults->SetMarkerStyle(1);
	fitResults->Draw("A2_Y:A2_X","","same");
	fitResults->SetMarkerColor(1); 
	fitResults->SetMarkerStyle(2);
	fitResults->Draw("A2_Y_True:A2_X_True","","same");

	fitResults->SetMarkerColor(4); 
	fitResults->SetMarkerStyle(1);
	fitResults->Draw("A3_Y:A3_X","","same");
	fitResults->SetMarkerColor(1); 
	fitResults->SetMarkerStyle(2);
	fitResults->Draw("A3_Y_True:A3_X_True","","same");

	c1->SaveAs("complexVars.eps");

}
