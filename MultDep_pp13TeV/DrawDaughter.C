void DrawDaughter(){

	gStyle->SetOptStat(0);

	const int nset = 2;

	TFile *infile[nset];

	infile[0] = new TFile("outfile_XiEfficiencyV5_pythia6.root");
	infile[1] = new TFile("outfile_XiEfficiencyV5_pythia8.root");

	TH3D *hTrueXi[nset];
	TH3D *hTrueEe[nset];

	TH2D *hTrueXiEtaPt[nset];
	TH2D *hTrueEeEtaPt[nset];

	TH1D *hTrueXiEta[nset];
	TH1D *hTrueEeEta[nset];

	TH1D *hTrueXiPt[nset];
	TH1D *hTrueEePt[nset];

	for (int iset=0; iset<nset; iset++){

		hTrueXi[iset] = (TH3D*)infile[iset]->Get("hTrueXi");
		hTrueEe[iset] = (TH3D*)infile[iset]->Get("hTrueEe");

		int bXic0PtMin = hTrueXi[iset]->GetXaxis()->FindBin(2.0+0.1); 
		int bXic0PtMax = hTrueXi[iset]->GetXaxis()->FindBin(3.0-0.1); 

		hTrueXi[iset]->GetXaxis()->SetRange(bXic0PtMin, bXic0PtMax);
		hTrueEe[iset]->GetXaxis()->SetRange(bXic0PtMin, bXic0PtMax);

		hTrueXiEtaPt[iset] = (TH2D*)hTrueXi[iset]->Project3D(Form("hTrueXiEtaPt_set%d_yz",iset));
		hTrueEeEtaPt[iset] = (TH2D*)hTrueEe[iset]->Project3D(Form("hTrueEeEtaPt_set%d_yz",iset));

		hTrueXiEta[iset] = (TH1D*)hTrueXiEtaPt[iset]->ProjectionX(Form("hTrueXiEta_set%d",iset));
		hTrueEeEta[iset] = (TH1D*)hTrueEeEtaPt[iset]->ProjectionX(Form("hTrueEeEta_set%d",iset));

		hTrueXiEta[iset]->Scale(1./hTrueXiEta[iset]->Integral());
		hTrueEeEta[iset]->Scale(1./hTrueEeEta[iset]->Integral());

		hTrueXiEta[iset]->SetMarkerStyle(24+iset);
		hTrueXiEta[iset]->SetLineWidth(2);
		hTrueXiEta[iset]->SetLineColor(iset+1);
		hTrueXiEta[iset]->SetMarkerColor(iset+1);
		hTrueEeEta[iset]->SetMarkerStyle(24+iset);
		hTrueEeEta[iset]->SetLineWidth(2);
		hTrueEeEta[iset]->SetLineColor(iset+1);
		hTrueEeEta[iset]->SetMarkerColor(iset+1);

		int bEtaMin = hTrueXiEtaPt[iset]->GetXaxis()->FindBin(-1.0+0.01);
		int bEtaMax = hTrueXiEtaPt[iset]->GetXaxis()->FindBin(+1.0-0.01);

		hTrueXiPt[iset] = (TH1D*)hTrueXiEtaPt[iset]->ProjectionY(Form("hTrueXiPt_set%d",iset),bEtaMin,bEtaMax);
		hTrueEePt[iset] = (TH1D*)hTrueEeEtaPt[iset]->ProjectionY(Form("hTrueEePt_set%d",iset),bEtaMin,bEtaMax);

		hTrueXiPt[iset]->Scale(1./hTrueXiPt[iset]->Integral());
		hTrueEePt[iset]->Scale(1./hTrueEePt[iset]->Integral());

		hTrueXiPt[iset]->SetMarkerStyle(24+iset);
		hTrueXiPt[iset]->SetLineWidth(2);
		hTrueXiPt[iset]->SetLineColor(iset+1);
		hTrueXiPt[iset]->SetMarkerColor(iset+1);
		hTrueEePt[iset]->SetMarkerStyle(24+iset);
		hTrueEePt[iset]->SetLineWidth(2);
		hTrueEePt[iset]->SetLineColor(iset+1);
		hTrueEePt[iset]->SetMarkerColor(iset+1);

	}

	TCanvas *c1 = new TCanvas("c1","c1",1.1*2*400,2*400);
	c1->Divide(2,2);

	for (int iset=0; iset<nset; iset++){
		{
			c1->cd(2*iset+1);
			gPad->SetMargin(0.15,0.13,0.12,0.03);
			TH1D *htmp = (TH1D*)gPad->DrawFrame(-2.5,0,2.5,5);
			htmp->GetXaxis()->SetTitle("#eta");
			htmp->GetXaxis()->SetTitleSize(0.05);
			htmp->GetYaxis()->SetTitle("p_{T} [GeV/c]");
			htmp->GetYaxis()->SetTitleSize(0.05);
			hTrueXiEtaPt[iset]->Draw("colz same");
		}

		{
			c1->cd(2*iset+2);
			gPad->SetMargin(0.15,0.13,0.12,0.03);
			TH1D *htmp = (TH1D*)gPad->DrawFrame(-2.5,0,2.5,5);
			htmp->GetXaxis()->SetTitle("#eta");
			htmp->GetXaxis()->SetTitleSize(0.05);
			htmp->GetYaxis()->SetTitle("p_{T} [GeV/c]");
			htmp->GetYaxis()->SetTitleSize(0.05);
			hTrueEeEtaPt[iset]->Draw("colz same");
		}
	}

	TCanvas *c2 = new TCanvas("c2","c2",1.1*2*400,2*400);
	c2->Divide(2,2);

	{
		c2->cd(1);
		gPad->SetMargin(0.15,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(-2.5,0,2.5,1.2*hTrueXiEta[0]->GetMaximum());
		htmp->GetYaxis()->SetTitle("");
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetTitle("#eta");
		htmp->GetXaxis()->SetTitleSize(0.05);

		hTrueXiEta[0]->Draw("same");
		hTrueXiEta[1]->Draw("same");
	}

	{
		c2->cd(2);
		gPad->SetMargin(0.15,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,5,1.2*hTrueXiPt[0]->GetMaximum());
		htmp->GetYaxis()->SetTitle("");
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetTitle("p_{T} [GeV/c]");
		htmp->GetXaxis()->SetTitleSize(0.05);

		hTrueXiPt[0]->Draw("same");
		hTrueXiPt[1]->Draw("same");
	}

	{
		c2->cd(3);
		gPad->SetMargin(0.15,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(-2.5,0,2.5,1.2*hTrueEeEta[0]->GetMaximum());
		htmp->GetYaxis()->SetTitle("");
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetTitle("#eta");
		htmp->GetXaxis()->SetTitleSize(0.05);

		hTrueEeEta[0]->Draw("same");
		hTrueEeEta[1]->Draw("same");
	}

	{
		c2->cd(4);
		gPad->SetMargin(0.15,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,5,1.2*hTrueEePt[0]->GetMaximum());
		htmp->GetYaxis()->SetTitle("");
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetTitle("p_{T} [GeV/c]");
		htmp->GetXaxis()->SetTitleSize(0.05);

		hTrueEePt[0]->Draw("same");
		hTrueEePt[1]->Draw("same");
	}

}
