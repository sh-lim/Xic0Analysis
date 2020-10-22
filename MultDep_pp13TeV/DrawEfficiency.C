void DrawEfficiency(){

	const int nset = 3;
	const int ncent = 3;
	string setname[3] = {"LHC16MC", "LHC17MC", "LHC18MC"};
	const int nColor[3] = {1, 2, 4};

	TFile *infile = new TFile("outfile_efficiency.root","read");

	TH2D *h2dGenSPDVWT[nset][ncent];
	TH2D *h2dRecoSPDVWT[nset][ncent];

	TH1D *h1dGenSPDVWT[nset][ncent];
	TH1D *h1dRecoSPDVWT[nset][ncent];

	TH1D *h1dSPDVWT[nset][ncent];

	for (int iset=0; iset<nset; iset++){
		for (int icent=0; icent<ncent; icent++){
			h2dGenSPDVWT[iset][icent] = (TH2D*)infile->Get(Form("h2dGenSPDVWT_set%d_cent%d",iset,icent));
			h2dRecoSPDVWT[iset][icent] = (TH2D*)infile->Get(Form("h2dRecoSPDVWT_set%d_cent%d",iset,icent));

			if ( iset>0 ){
				h2dGenSPDVWT[0][icent]->Add(h2dGenSPDVWT[iset][icent]);
				h2dRecoSPDVWT[0][icent]->Add(h2dRecoSPDVWT[iset][icent]);
			}
		}
	}

	for (int iset=0; iset<nset; iset++){
		for (int icent=0; icent<ncent; icent++){
			h1dSPDVWT[iset][icent] = (TH1D*)h2dGenSPDVWT[iset][icent]->ProjectionY(Form("h1dSPDVWT_%d_%d",iset,icent));
			h1dSPDVWT[iset][icent]->Scale(1./h1dSPDVWT[iset][icent]->Integral());

			h1dGenSPDVWT[iset][icent] = (TH1D*)h2dGenSPDVWT[iset][icent]->ProjectionX(Form("h1dGenSPDVWT_%d_%d",iset,icent));
			h1dRecoSPDVWT[iset][icent] = (TH1D*)h2dRecoSPDVWT[iset][icent]->ProjectionX(Form("h1dRecoSPDVWT_%d_%d",iset,icent));
		}
	}

	{
		TCanvas *c1 = new TCanvas("c1","c1",1.1*400,400);
		gPad->SetMargin(0.15,0.05,0.15,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,100,1.2*h1dSPDVWT[0][2]->GetMaximum());
		for (int ii=0; ii<3; ii++){
			h1dSPDVWT[0][ii]->SetMarkerStyle(24);
			h1dSPDVWT[0][ii]->SetLineWidth(2);
			h1dSPDVWT[0][ii]->SetLineColor(nColor[ii]);
			h1dSPDVWT[0][ii]->SetMarkerColor(nColor[ii]);
			h1dSPDVWT[0][ii]->Draw("p same");
		}
	}

	{
		TCanvas *c2 = new TCanvas("c2","c2",1.1*400,400);
		gPad->SetMargin(0.15,0.05,0.15,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,12,0.15);
		for (int ii=0; ii<3; ii++){
			h1dRecoSPDVWT[0][ii]->SetMarkerStyle(24);
			h1dRecoSPDVWT[0][ii]->SetLineWidth(2);
			h1dRecoSPDVWT[0][ii]->SetLineColor(nColor[ii]);
			h1dRecoSPDVWT[0][ii]->SetMarkerColor(nColor[ii]);
			h1dRecoSPDVWT[0][ii]->Divide(h1dGenSPDVWT[0][ii]);
			h1dRecoSPDVWT[0][ii]->Draw("p same");
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

	/*
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
	*/


}
