void DrawEfficiencyV3(){

	const bool bSAVE = false;

	//const int nset = 3;
	//string setname[nset] = {"LHC20MCj7c", "LHC20MCk2", "LHC17MCd2b"};
	const int nset = 2;
	string setname[nset] = {"LHC20MCk2", "LHC17MCd2b"};
	//const int nset = 1;
	//string setname[nset] = {"LHC20MCk2"};
	const int nColor[6] = {1, 2, 4, 6, 8, 9};

	TFile *infile = new TFile("outfile_efficiencyV3_Set0.root","read");

	TH3D *h3dGenSPDV[nset];
	TH3D *h3dRecoSPDV[nset];

	TH2D *h2dGenSPDVCharm[nset];
	TH2D *h2dGenSPDVBottom[nset];

	TH2D *h2dRecoSPDVCharm[nset];
	TH2D *h2dRecoSPDVBottom[nset];

	TH1D *h1dGenSPDVCharm[nset];
	TH1D *h1dRecoSPDVCharm[nset];

	TH1D *h1dGenSPDVBottom[nset];
	TH1D *h1dRecoSPDVBottom[nset];

	TH1D *h1dGenPt[nset];
	TH1D *h1dRecoPt[nset];

	TH1D *h1dGenEta[nset];
	TH1D *h1dRecoEta[nset];

	TH1D *h1dGenPtCharm[nset][2];
	TH1D *h1dRecoPtCharm[nset][2];

	TH1D *h1dGenPtBottom[nset][2];
	TH1D *h1dRecoPtBottom[nset][2];

	for (int iset=0; iset<nset; iset++){
		h2dGenSPDVCharm[iset] = (TH2D*)infile->Get(Form("h2dGenSPDVCharm_set%d",iset));
		h2dRecoSPDVCharm[iset] = (TH2D*)infile->Get(Form("h2dRecoSPDVCharm_set%d",iset));

		h2dGenSPDVBottom[iset] = (TH2D*)infile->Get(Form("h2dGenSPDVBottom_set%d",iset));
		h2dRecoSPDVBottom[iset] = (TH2D*)infile->Get(Form("h2dRecoSPDVBottom_set%d",iset));

		h3dGenSPDV[iset] = (TH3D*)infile->Get(Form("h3dGenSPDV_set%d",iset));
		h3dRecoSPDV[iset] = (TH3D*)infile->Get(Form("h3dRecoSPDV_set%d",iset));
	}

	for (int iset=0; iset<nset; iset++){
		h1dGenSPDVCharm[iset] = (TH1D*)h2dGenSPDVCharm[iset]->ProjectionY(Form("h1dGenSPDVCharm_%d",iset),2,3);
		h1dRecoSPDVCharm[iset] = (TH1D*)h2dRecoSPDVCharm[iset]->ProjectionY(Form("h1dRecoSPDVCharm_%d",iset),2,3);

		h1dGenSPDVBottom[iset] = (TH1D*)h2dGenSPDVBottom[iset]->ProjectionY(Form("h1dGenSPDVBottom_%d",iset),2,3);
		h1dRecoSPDVBottom[iset] = (TH1D*)h2dRecoSPDVBottom[iset]->ProjectionY(Form("h1dRecoSPDVBottom_%d",iset),2,3);

		h1dGenSPDVCharm[iset]->Rebin(10);
		h1dRecoSPDVCharm[iset]->Rebin(10);

		h1dGenSPDVBottom[iset]->Rebin(10);
		h1dRecoSPDVBottom[iset]->Rebin(10);

		h1dRecoSPDVCharm[iset]->Divide(h1dGenSPDVCharm[iset]);
		h1dRecoSPDVBottom[iset]->Divide(h1dGenSPDVBottom[iset]);

		h1dRecoSPDVCharm[iset]->SetMarkerStyle(24);
		h1dRecoSPDVCharm[iset]->SetMarkerColor(nColor[iset]);
		h1dRecoSPDVCharm[iset]->SetLineColor(nColor[iset]);
		h1dRecoSPDVBottom[iset]->SetMarkerStyle(25);
		h1dRecoSPDVBottom[iset]->SetMarkerColor(nColor[iset]);
		h1dRecoSPDVBottom[iset]->SetLineColor(nColor[iset]);

		h1dGenPtCharm[iset][0] = (TH1D*)h2dGenSPDVCharm[iset]->ProjectionX(Form("h1dGenPtCharm_%d_0",iset),1,20);
		h1dRecoPtCharm[iset][0] = (TH1D*)h2dRecoSPDVCharm[iset]->ProjectionX(Form("h1dRecoPtCharm_%d_0",iset),1,20);
		h1dGenPtBottom[iset][0] = (TH1D*)h2dGenSPDVBottom[iset]->ProjectionX(Form("h1dGenPtBottom_%d_0",iset),1,20);
		h1dRecoPtBottom[iset][0] = (TH1D*)h2dRecoSPDVBottom[iset]->ProjectionX(Form("h1dRecoPtBottom_%d_0",iset),1,20);

		h1dGenPtCharm[iset][1] = (TH1D*)h2dGenSPDVCharm[iset]->ProjectionX(Form("h1dGenPtCharm_%d_1",iset),31,50);
		h1dRecoPtCharm[iset][1] = (TH1D*)h2dRecoSPDVCharm[iset]->ProjectionX(Form("h1dRecoPtCharm_%d_1",iset),31,50);
		h1dGenPtBottom[iset][1] = (TH1D*)h2dGenSPDVBottom[iset]->ProjectionX(Form("h1dGenPtBottom_%d_1",iset),31,50);
		h1dRecoPtBottom[iset][1] = (TH1D*)h2dRecoSPDVBottom[iset]->ProjectionX(Form("h1dRecoPtBottom_%d_1",iset),31,50);

		h1dGenPt[iset] = (TH1D*)h3dGenSPDV[iset]->ProjectionX(Form("h1dGenPt_%d",iset),1,5,1,200);
		h1dRecoPt[iset] = (TH1D*)h3dRecoSPDV[iset]->ProjectionX(Form("h1dRecoPt_%d",iset),1,10,1,200);
		//h1dRecoPt[iset] = (TH1D*)h3dRecoSPDV[iset]->ProjectionX(Form("h1dRecoPt_%d",iset),1,5,1,200);

		h1dGenEta[iset] = (TH1D*)h3dGenSPDV[iset]->ProjectionY(Form("h1dGenEta_%d",iset),2,4,1,200);
		h1dRecoEta[iset] = (TH1D*)h3dRecoSPDV[iset]->ProjectionY(Form("h1dRecoEta_%d",iset),2,4,1,200);

		for (int ii=0; ii<2; ii++){
			h1dRecoPtCharm[iset][ii]->Divide(h1dGenPtCharm[iset][ii]);
			h1dRecoPtBottom[iset][ii]->Divide(h1dGenPtBottom[iset][ii]);

			h1dRecoPtCharm[iset][ii]->SetMarkerStyle(20+4*ii);
			h1dRecoPtCharm[iset][ii]->SetMarkerColor(nColor[iset]);
			h1dRecoPtCharm[iset][ii]->SetLineColor(nColor[iset]);
			h1dRecoPtBottom[iset][ii]->SetMarkerStyle(21+4*ii);
			h1dRecoPtBottom[iset][ii]->SetMarkerColor(nColor[iset]);
			h1dRecoPtBottom[iset][ii]->SetLineColor(nColor[iset]);
		}

		h1dRecoPt[iset]->Divide(h1dGenPt[iset]);
		h1dRecoPt[iset]->SetMarkerStyle(24);
		h1dRecoPt[iset]->SetMarkerColor(nColor[iset]);
		h1dRecoPt[iset]->SetLineColor(nColor[iset]);

		h1dRecoEta[iset]->Divide(h1dGenEta[iset]);
		h1dRecoEta[iset]->SetMarkerStyle(24);
		h1dRecoEta[iset]->SetMarkerColor(nColor[iset]);
		h1dRecoEta[iset]->SetLineColor(nColor[iset]);
	}

	/*
	{
		TCanvas *c1 = new TCanvas("c1","c1",1.2*2*500,500);
		c1->Divide(2,1);

		c1->cd(1);
		gPad->SetMargin(0.15,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(1,0,12,0.15);
		htmp->GetXaxis()->SetTitle("p_{T}^{#Xi_{c}^{0}} (GeV/c)");
		htmp->GetYaxis()->SetTitle("Acc and reco eff");

		h1dRecoPt[0]->Draw("p same");
		h1dRecoPt[1]->Draw("p same");
		//h1dRecoPt[2]->Draw("p same");

		TLegend *leg = new TLegend(0.15,0.7,0.5,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry(h1dRecoPt[0],"PYTHIA8+HIJING","P");
		leg->AddEntry(h1dRecoPt[1],"PYTHIA6+HIJING","P");
		leg->Draw();

		c1->cd(2);
		gPad->SetMargin(0.15,0.05,0.12,0.03);
		htmp = (TH1D*)gPad->DrawFrame(1,0,12,2.0);
		htmp->GetXaxis()->SetTitle("p_{T}^{#Xi_{c}^{0}} (GeV/c)");
		htmp->GetYaxis()->SetTitle("PYTHIA8 / PYTHIA6");
		TH1D *hR = (TH1D*)h1dRecoPt[0]->Clone("hR");
		hR->Divide(h1dRecoPt[1]);
		hR->Draw("p same");

		//TH1D *hR2 = (TH1D*)h1dRecoPt[2]->Clone("hR2");
		//hR2->Divide(h1dRecoPt[0]);
		//hR2->Draw("p same");

	}
	*/

	{
		TCanvas *c2 = new TCanvas("c2","c2",1.2*2*500,500);
		c2->Divide(2,1);

		c2->cd(1);
		gPad->SetMargin(0.15,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(-1.5,0,1.5,0.05);
		htmp->GetXaxis()->SetTitle("#Xi_{c}^{0} y");
		htmp->GetYaxis()->SetTitle("Acc and reco eff");

		h1dRecoEta[0]->Draw("p same");
		//h1dRecoEta[1]->Draw("p same");

		/*
		TLegend *leg = new TLegend(0.15,0.7,0.5,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry(h1dRecoEta[0],"PYTHIA8+HIJING","P");
		leg->AddEntry(h1dRecoEta[1],"PYTHIA6+HIJING","P");
		leg->Draw();

		c2->cd(2);
		gPad->SetMargin(0.15,0.05,0.12,0.03);
		htmp = (TH1D*)gPad->DrawFrame(0,0,1,2.0);
		htmp->GetXaxis()->SetTitle("#Xi_{c}^{0} y");
		htmp->GetYaxis()->SetTitle("PYTHIA8 / PYTHIA6");
		TH1D *hR = (TH1D*)h1dRecoEta[0]->Clone("hR");
		hR->Divide(h1dRecoEta[1]);
		hR->Draw("p same");
		*/

	}

	return;

	if ( bSAVE ){

		cout << "Write an efficiency file" << endl;
		
		TFile *outfile = new TFile("EfficiencyXic0Pt.root","recreate");

		h1dRecoPt[0]->Write("hEffPtMB_Pythia6");
		h1dRecoPt[3]->Write("hEffPtMB_Pythia8");

		outfile->Close();

	}

	return;

	{
		TCanvas *c1 = new TCanvas("c1","c1",1.2*500,500);
		gPad->SetMargin(0.15,0.05,0.15,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,100,0.1);

		h1dRecoSPDVCharm[0]->Draw("p same");
		h1dRecoSPDVBottom[0]->Draw("p same");

		h1dRecoSPDVCharm[3]->Draw("p same");
		h1dRecoSPDVBottom[3]->Draw("p same");
	}

	TCanvas *c2 = new TCanvas("c2","c2",1.2*2*500,500);
	c2->Divide(2,1);
	{
		c2->cd(1);
		gPad->SetMargin(0.15,0.05,0.15,0.03);
		gPad->SetGridx();
		gPad->SetGridy();
		TH1D *htmp = (TH1D*)gPad->DrawFrame(1.0,0,12.0,0.12);

		//h1dRecoPtCharm[0][0]->Draw("p same");
		//h1dRecoPtBottom[0][0]->Draw("p same");

		h1dRecoPtCharm[0][1]->Draw("p same");
		h1dRecoPtBottom[0][1]->Draw("p same");
	}

	{
		c2->cd(2);
		gPad->SetMargin(0.15,0.05,0.15,0.03);
		gPad->SetGridx();
		gPad->SetGridy();
		TH1D *htmp = (TH1D*)gPad->DrawFrame(1.0,0,12.0,0.12);

		h1dRecoPtCharm[3][0]->Draw("p same");
		h1dRecoPtBottom[3][0]->Draw("p same");

		h1dRecoPtCharm[3][1]->Draw("p same");
		h1dRecoPtBottom[3][1]->Draw("p same");

	}

	/*
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
	*/

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
