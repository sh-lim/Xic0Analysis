void DrawEfficiency(){

	const int nset = 3;
	string setname[nset] = {"LHC16MC", "LHC17MC", "LHC18MC"};
	const int nColor[nset] = {1, 2, 4};

	TFile *infile = new TFile("outfile_efficiency.root","read");

	TH1D *h1dGen_SPDV[nset];
	TH1D *h1dReco_SPDV[nset];
	TH1D *h1dEff_SPDV[nset];

	TH1D *h1dGen_SPDV_com;
	TH1D *h1dReco_SPDV_com;

	for (int iset=0; iset<nset; iset++){

		h1dGen_SPDV[iset] = (TH1D*)infile->Get(Form("h1dGen_SPDV_%s",setname[iset].c_str()));
		h1dReco_SPDV[iset] = (TH1D*)infile->Get(Form("h1dReco_SPDV_%s",setname[iset].c_str()));
		h1dEff_SPDV[iset] = (TH1D*)infile->Get(Form("h1dEff_SPDV_%s",setname[iset].c_str()));

		if ( iset==0 ){
			h1dGen_SPDV_com = (TH1D*)h1dGen_SPDV[iset]->Clone("h1dGen_SPDV_com");
			h1dReco_SPDV_com = (TH1D*)h1dReco_SPDV[iset]->Clone("h1dReco_SPDV_com");
		}else{
			h1dGen_SPDV_com->Add(h1dGen_SPDV[iset]);
			h1dReco_SPDV_com->Add(h1dReco_SPDV[iset]);
		}

	}

	/*
	TCanvas *c1 = new TCanvas("c1","c1",2*1.1*400,2*400);
	c1->Divide(2,2);

	for (int iset=0; iset<nset; iset++){
		c1->cd(iset+1);
		h1dEff_SPDV[iset]->Draw("p");
	}
	*/

	TH1D *h1dEff_SPDV_com = (TH1D*)h1dReco_SPDV_com->Clone("h1dEff_SPDV_com");
	h1dEff_SPDV_com->Sumw2();
	h1dEff_SPDV_com->Divide(h1dGen_SPDV_com);

	TCanvas *c1 = new TCanvas("c1","c1",1.1*400,400);
	{
		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,100,0.15);
		htmp->GetXaxis()->SetTitle("Number of SPD tracklets");
		htmp->GetYaxis()->SetTitle("Efficiency");
		h1dEff_SPDV_com->Draw("p same");
	}


}
