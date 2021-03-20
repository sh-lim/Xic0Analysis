void DrawTrkEffV2(){

	const int nset = 2;

	const string setname[nset] = {"pPb_pythia6","pPb_pythia8"};
	//const string setname[nset] = {"LHC17MCd2b","LHC20MCk2","LHC20MCj7b"};
	//const string setname[nset] = {"LHC17MCd2b"};

	const int nColor[5] = {1, 2, 4, 6, 8};

	TFile *infile[nset];

	TH2D *hTruePion0[nset];
	TH2D *hTruePion1[nset];
	TH2D *hTruePion2[nset];
	TH2D *hTrueProton3[nset];

	TH2D *hRecoPion0[nset];
	TH2D *hRecoPion1[nset];
	TH2D *hRecoPion2[nset];
	TH2D *hRecoProton3[nset];

	TH1D *hTruePion0Eta[nset];
	TH1D *hTruePion1Eta[nset];
	TH1D *hTruePion2Eta[nset];
	TH1D *hTrueProton3Eta[nset];

	TH1D *hRecoPion0Eta[nset];
	TH1D *hRecoPion1Eta[nset];
	TH1D *hRecoPion2Eta[nset];
	TH1D *hRecoProton3Eta[nset];

	char fname[500];
	ifstream flist;

	for (int iset=0; iset<nset; iset++){

		sprintf(fname, "list_%s.lst", setname[iset].c_str());
		flist.open(fname);

		bool bfirst = true;

		hTruePion0[iset] = new TH2D(Form("hTruePion0_set%d",iset),"",30,-1.5,1.5,100,0,10);
		hTruePion1[iset] = new TH2D(Form("hTruePion1_set%d",iset),"",30,-1.5,1.5,100,0,10);
		hTruePion2[iset] = new TH2D(Form("hTruePion2_set%d",iset),"",30,-1.5,1.5,100,0,10);
		hTrueProton3[iset] = new TH2D(Form("hTrueProton3_set%d",iset),"",30,-1.5,1.5,100,0,10);

		hRecoPion0[iset] = new TH2D(Form("hRecoPion0_set%d",iset),"",30,-1.5,1.5,100,0,10);
		hRecoPion1[iset] = new TH2D(Form("hRecoPion1_set%d",iset),"",30,-1.5,1.5,100,0,10);
		hRecoPion2[iset] = new TH2D(Form("hRecoPion2_set%d",iset),"",30,-1.5,1.5,100,0,10);
		hRecoProton3[iset] = new TH2D(Form("hRecoProton3_set%d",iset),"",30,-1.5,1.5,100,0,10);

		while ( flist >> fname ){

			cout << "OPEN: " << fname << endl;

			TFile *infile0 = new TFile(fname,"read");

			TH2D *_hTruePion0 = (TH2D*)infile0->Get("histogram")->FindObject("hTruePion0");
			TH2D *_hTruePion1 = (TH2D*)infile0->Get("histogram")->FindObject("hTruePion1");
			TH2D *_hTruePion2 = (TH2D*)infile0->Get("histogram")->FindObject("hTruePion2");
			TH2D *_hTrueProton3 = (TH2D*)infile0->Get("histogram")->FindObject("hTrueProton3");

			TH2D *_hRecoPion0 = (TH2D*)infile0->Get("histogram")->FindObject("hRecoPion0");
			TH2D *_hRecoPion1 = (TH2D*)infile0->Get("histogram")->FindObject("hRecoPion1");
			TH2D *_hRecoPion2 = (TH2D*)infile0->Get("histogram")->FindObject("hRecoPion2");
			TH2D *_hRecoProton3 = (TH2D*)infile0->Get("histogram")->FindObject("hRecoProton3");

			hTruePion0[iset]->Add(_hTruePion0);
			hTruePion1[iset]->Add(_hTruePion1);
			hTruePion2[iset]->Add(_hTruePion2);
			hTrueProton3[iset]->Add(_hTrueProton3);

			hRecoPion0[iset]->Add(_hRecoPion0);
			hRecoPion1[iset]->Add(_hRecoPion1);
			hRecoPion2[iset]->Add(_hRecoPion2);
			hRecoProton3[iset]->Add(_hRecoProton3);

			infile0->Close();
			delete infile0;

		}//while

		flist.close();

		hTruePion0Eta[iset] = (TH1D*)hTruePion0[iset]->ProjectionX(Form("hTruePion0Eta_set%d",iset));
		hTruePion1Eta[iset] = (TH1D*)hTruePion1[iset]->ProjectionX(Form("hTruePion1Eta_set%d",iset));
		hTruePion2Eta[iset] = (TH1D*)hTruePion2[iset]->ProjectionX(Form("hTruePion2Eta_set%d",iset));
		hTrueProton3Eta[iset] = (TH1D*)hTrueProton3[iset]->ProjectionX(Form("hTrueProton3Eta_set%d",iset));

		hRecoPion0Eta[iset] = (TH1D*)hRecoPion0[iset]->ProjectionX(Form("hRecoPion0Eta_set%d",iset));
		hRecoPion1Eta[iset] = (TH1D*)hRecoPion1[iset]->ProjectionX(Form("hRecoPion1Eta_set%d",iset));
		hRecoPion2Eta[iset] = (TH1D*)hRecoPion2[iset]->ProjectionX(Form("hRecoPion2Eta_set%d",iset));
		hRecoProton3Eta[iset] = (TH1D*)hRecoProton3[iset]->ProjectionX(Form("hRecoProton3Eta_set%d",iset));

		hRecoPion0Eta[iset]->Divide(hTruePion0Eta[iset]);
		hRecoPion1Eta[iset]->Divide(hTruePion1Eta[iset]);
		hRecoPion2Eta[iset]->Divide(hTruePion2Eta[iset]);
		hRecoProton3Eta[iset]->Divide(hTrueProton3Eta[iset]);

		hRecoPion0Eta[iset]->SetMarkerStyle(24);
		hRecoPion0Eta[iset]->SetMarkerColor(nColor[iset]);
		hRecoPion0Eta[iset]->SetLineColor(nColor[iset]);

		hRecoPion1Eta[iset]->SetMarkerStyle(24);
		hRecoPion1Eta[iset]->SetMarkerColor(nColor[iset]);
		hRecoPion1Eta[iset]->SetLineColor(nColor[iset]);

		hRecoPion2Eta[iset]->SetMarkerStyle(24);
		hRecoPion2Eta[iset]->SetMarkerColor(nColor[iset]);
		hRecoPion2Eta[iset]->SetLineColor(nColor[iset]);

		hRecoProton3Eta[iset]->SetMarkerStyle(24);
		hRecoProton3Eta[iset]->SetMarkerColor(nColor[iset]);
		hRecoProton3Eta[iset]->SetLineColor(nColor[iset]);

		continue;

		hTruePion0[iset]->Rebin(2);
		hTruePion1[iset]->Rebin(2);
		hTruePion2[iset]->Rebin(2);
		hTrueProton3[iset]->Rebin(2);

		hRecoPion0[iset]->Rebin(2);
		hRecoPion1[iset]->Rebin(2);
		hRecoPion2[iset]->Rebin(2);
		hRecoProton3[iset]->Rebin(2);

		hRecoPion0[iset]->Divide(hTruePion0[iset]);
		hRecoPion1[iset]->Divide(hTruePion1[iset]);
		hRecoPion2[iset]->Divide(hTruePion2[iset]);
		hRecoProton3[iset]->Divide(hTrueProton3[iset]);

		hRecoPion0[iset]->SetMarkerStyle(24);
		hRecoPion0[iset]->SetMarkerColor(nColor[iset]);
		hRecoPion0[iset]->SetLineColor(nColor[iset]);

		hRecoPion1[iset]->SetMarkerStyle(24);
		hRecoPion1[iset]->SetMarkerColor(nColor[iset]);
		hRecoPion1[iset]->SetLineColor(nColor[iset]);

		hRecoPion2[iset]->SetMarkerStyle(24);
		hRecoPion2[iset]->SetMarkerColor(nColor[iset]);
		hRecoPion2[iset]->SetLineColor(nColor[iset]);

		hRecoProton3[iset]->SetMarkerStyle(24);
		hRecoProton3[iset]->SetMarkerColor(nColor[iset]);
		hRecoProton3[iset]->SetLineColor(nColor[iset]);
	}

	TCanvas *c0 = new TCanvas("c0","c0",1.2*2*400,2*400);
	c0->Divide(2,2);
	{

		c0->cd(1);
		gPad->SetTopMargin(0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(-1.5,0,1.5,1.0);
		htmp->GetXaxis()->SetTitle("#eta");
		htmp->GetYaxis()->SetTitle("Efficiency");

		hRecoPion0Eta[0]->Draw("same");
		hRecoPion0Eta[1]->Draw("same");

		c0->cd(2);
		gPad->SetTopMargin(0.03);
		htmp = (TH1D*)gPad->DrawFrame(-1.5,0,1.5,0.6);
		htmp->GetXaxis()->SetTitle("#eta");
		htmp->GetYaxis()->SetTitle("Efficiency");

		hRecoPion1Eta[0]->Draw("same");
		hRecoPion1Eta[1]->Draw("same");

		/*
		TLegend *leg = new TLegend(0.5,0.7,0.9,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","#pi^{#pm}#leftarrow#Xi^{#pm} in |#eta|<0.9","h");
		leg->AddEntry(hRecoPion1[0],"pPb OLD","P");
		leg->AddEntry(hRecoPion1[1],"pPb NEW","P");
		leg->AddEntry(hRecoPion1[2],"pp NEW","P");
		leg->Draw();
		*/

		c0->cd(3);
		gPad->SetTopMargin(0.03);
		htmp = (TH1D*)gPad->DrawFrame(-1.5,0,1.5,0.6);
		htmp->GetXaxis()->SetTitle("#eta");
		htmp->GetYaxis()->SetTitle("Efficiency");

		hRecoPion2Eta[0]->Draw("same");
		hRecoPion2Eta[1]->Draw("same");

		/*
		leg = new TLegend(0.5,0.7,0.9,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","#pi#leftarrow#Lambda in |#eta|<0.9","h");
		leg->AddEntry(hRecoPion2[0],"pPb OLD","P");
		leg->AddEntry(hRecoPion2[1],"pPb NEW","P");
		leg->AddEntry(hRecoPion2[2],"pp NEW","P");
		leg->Draw();
		*/

		c0->cd(4);
		gPad->SetTopMargin(0.03);
		htmp = (TH1D*)gPad->DrawFrame(-1.5,0,1.5,0.6);
		htmp->GetXaxis()->SetTitle("#eta");
		htmp->GetYaxis()->SetTitle("Efficiency");

		hRecoProton3Eta[0]->Draw("same");
		hRecoProton3Eta[1]->Draw("same");

		/*
		leg = new TLegend(0.5,0.7,0.9,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","p#leftarrow#Lambda in |#eta|<0.9","h");
		leg->AddEntry(hRecoProton3[0],"pPb OLD","P");
		leg->AddEntry(hRecoProton3[1],"pPb NEW","P");
		leg->AddEntry(hRecoProton3[2],"pp NEW","P");
		leg->Draw();
		*/
	}

	return;

	TCanvas *c1 = new TCanvas("c1","c1",1.2*2*400,2*400);
	c1->Divide(2,2);
	{

		c1->cd(1);
		gPad->SetTopMargin(0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,8,1.0);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetYaxis()->SetTitle("Efficiency");

		hRecoPion0[0]->Draw("same");
		hRecoPion0[1]->Draw("same");

		c1->cd(2);
		gPad->SetTopMargin(0.03);
		htmp = (TH1D*)gPad->DrawFrame(0,0,3,0.6);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetYaxis()->SetTitle("Efficiency");

		hRecoPion1[0]->Draw("same");
		hRecoPion1[1]->Draw("same");

		/*
		TLegend *leg = new TLegend(0.5,0.7,0.9,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","#pi^{#pm}#leftarrow#Xi^{#pm} in |#eta|<0.9","h");
		leg->AddEntry(hRecoPion1[0],"pPb OLD","P");
		leg->AddEntry(hRecoPion1[1],"pPb NEW","P");
		leg->AddEntry(hRecoPion1[2],"pp NEW","P");
		leg->Draw();
		*/

		c1->cd(3);
		gPad->SetTopMargin(0.03);
		htmp = (TH1D*)gPad->DrawFrame(0,0,3,0.25);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetYaxis()->SetTitle("Efficiency");

		hRecoPion2[0]->Draw("same");
		hRecoPion2[1]->Draw("same");

		/*
		leg = new TLegend(0.5,0.7,0.9,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","#pi#leftarrow#Lambda in |#eta|<0.9","h");
		leg->AddEntry(hRecoPion2[0],"pPb OLD","P");
		leg->AddEntry(hRecoPion2[1],"pPb NEW","P");
		leg->AddEntry(hRecoPion2[2],"pp NEW","P");
		leg->Draw();
		*/

		c1->cd(4);
		gPad->SetTopMargin(0.03);
		htmp = (TH1D*)gPad->DrawFrame(0,0,5,0.5);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetYaxis()->SetTitle("Efficiency");

		hRecoProton3[0]->Draw("same");
		hRecoProton3[1]->Draw("same");

		/*
		leg = new TLegend(0.5,0.7,0.9,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","p#leftarrow#Lambda in |#eta|<0.9","h");
		leg->AddEntry(hRecoProton3[0],"pPb OLD","P");
		leg->AddEntry(hRecoProton3[1],"pPb NEW","P");
		leg->AddEntry(hRecoProton3[2],"pp NEW","P");
		leg->Draw();
		*/
	}

	/*
	TCanvas *c2 = new TCanvas("c2","c2",1.2*2*500,500);
	c2->Divide(2,1);
	{

		c2->cd(1);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,8,1.0);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetYaxis()->SetTitle("Efficiency");

		hRecoPriProton[0]->Draw("same");
		hRecoPriProton[1]->Draw("same");
		hRecoPriProton[2]->Draw("same");

		TLegend *leg = new TLegend(0.5,0.2,0.9,0.4);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","Primary charged proton in |#eta|<0.9","h");
		leg->AddEntry(hRecoPriProton[0],"pPb OLD","P");
		leg->AddEntry(hRecoPriProton[1],"pPb NEW","P");
		leg->AddEntry(hRecoPriProton[2],"pp NEW","P");
		leg->Draw();

		c2->cd(2);
		htmp = (TH1D*)gPad->DrawFrame(0,0,8,0.4);
		htmp->GetXaxis()->SetTitle("p_{T} (GeV/c)");
		htmp->GetYaxis()->SetTitle("Efficiency");

		hRecoSecProton[0]->Draw("same");
		hRecoSecProton[1]->Draw("same");
		hRecoSecProton[2]->Draw("same");

		leg = new TLegend(0.2,0.7,0.6,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->AddEntry("","Secondary charged proton in |#eta|<0.9","h");
		leg->AddEntry(hRecoSecProton[0],"pPb OLD","P");
		leg->AddEntry(hRecoSecProton[1],"pPb NEW","P");
		leg->AddEntry(hRecoSecProton[2],"pp NEW","P");
		leg->Draw();
	}
	*/

}
