void DrawEfficiencyV2WDF(){

	const bool bSAVE = false;

	const int nset = 3;
	string setname[nset] = {"LHC20MCj7a", "LHC20MCj7b", "LHC20MCj7c"};
	//const int nset = 1;
	//string setname[nset] = {"LHC17MC"};
	const int nColor[6] = {1, 2, 4, 6, 8, 9};

	TFile *infile[2];

	infile[0] = new TFile(Form("outfile_efficiencyV2_AOD208.root"),"read");
	infile[1] = new TFile(Form("outfile_efficiencyV2_AOD235.root"),"read");

	TH3D *h3dGenSPDV[2][nset];
	TH3D *h3dRecoSPDV[2][nset];

	TH2D *h2dGenSPDVCharm[2][nset];
	TH2D *h2dGenSPDVBottom[2][nset];

	TH2D *h2dRecoSPDVCharm[2][nset];
	TH2D *h2dRecoSPDVBottom[2][nset];

	TH2D *h2dRecoSPDVCut1[2][nset];
	TH2D *h2dRecoSPDVCut2[2][nset];
	TH2D *h2dRecoSPDVCut3[2][nset];
	TH2D *h2dRecoSPDVCut4[2][nset];
	TH2D *h2dRecoSPDVCut5[2][nset];

	TH1D *h1dGenSPDVCharm[2][nset];
	TH1D *h1dRecoSPDVCharm[2][nset];

	TH1D *h1dGenSPDVBottom[2][nset];
	TH1D *h1dRecoSPDVBottom[2][nset];

	TH1D *h1dGenPt[2];
	TH1D *h1dRecoPt[2];
	TH1D *h1dRecoCut1Pt[2];
	TH1D *h1dRecoCut2Pt[2];
	TH1D *h1dRecoCut3Pt[2];
	TH1D *h1dRecoCut4Pt[2];
	TH1D *h1dRecoCut5Pt[2];

	TH1D *h1dGenPtCharm[nset][2];
	TH1D *h1dRecoPtCharm[nset][2];

	TH1D *h1dGenPtBottom[nset][2];
	TH1D *h1dRecoPtBottom[nset][2];

	TH1D *h1dGenSPD[nset];
	TH1D *h1dRecoSPD[nset];

	for (int ii=0; ii<2; ii++){
		for (int iset=0; iset<nset; iset++){
			h2dGenSPDVCharm[ii][iset] = (TH2D*)infile[ii]->Get(Form("h2dGenSPDVCharm_set%d",iset));
			h2dRecoSPDVCharm[ii][iset] = (TH2D*)infile[ii]->Get(Form("h2dRecoSPDVCharm_set%d",iset));

			h2dGenSPDVBottom[ii][iset] = (TH2D*)infile[ii]->Get(Form("h2dGenSPDVBottom_set%d",iset));
			h2dRecoSPDVBottom[ii][iset] = (TH2D*)infile[ii]->Get(Form("h2dRecoSPDVBottom_set%d",iset));

			h3dGenSPDV[ii][iset] = (TH3D*)infile[ii]->Get(Form("h3dGenSPDV_set%d",iset));
			h3dRecoSPDV[ii][iset] = (TH3D*)infile[ii]->Get(Form("h3dRecoSPDV_set%d",iset));

			h2dRecoSPDVCut1[ii][iset] = (TH2D*)infile[ii]->Get(Form("h2dRecoSPDVCut1_set%d",iset));
			h2dRecoSPDVCut2[ii][iset] = (TH2D*)infile[ii]->Get(Form("h2dRecoSPDVCut2_set%d",iset));
			h2dRecoSPDVCut3[ii][iset] = (TH2D*)infile[ii]->Get(Form("h2dRecoSPDVCut3_set%d",iset));
			h2dRecoSPDVCut4[ii][iset] = (TH2D*)infile[ii]->Get(Form("h2dRecoSPDVCut4_set%d",iset));
			h2dRecoSPDVCut5[ii][iset] = (TH2D*)infile[ii]->Get(Form("h2dRecoSPDVCut5_set%d",iset));

			if ( iset>0 ){
				h2dGenSPDVCharm[ii][0]->Add(h2dGenSPDVCharm[ii][iset]);
				h2dRecoSPDVCharm[ii][0]->Add(h2dRecoSPDVCharm[ii][iset]);

				h2dGenSPDVBottom[ii][0]->Add(h2dGenSPDVBottom[ii][iset]);
				h2dRecoSPDVBottom[ii][0]->Add(h2dRecoSPDVBottom[ii][iset]);

				h3dGenSPDV[ii][0]->Add(h3dGenSPDV[ii][iset]);
				h3dRecoSPDV[ii][0]->Add(h3dRecoSPDV[ii][iset]);

				h2dRecoSPDVCut1[ii][0]->Add(h2dRecoSPDVCut1[ii][iset]);
				h2dRecoSPDVCut2[ii][0]->Add(h2dRecoSPDVCut2[ii][iset]);
				h2dRecoSPDVCut3[ii][0]->Add(h2dRecoSPDVCut3[ii][iset]);
				h2dRecoSPDVCut4[ii][0]->Add(h2dRecoSPDVCut4[ii][iset]);
				h2dRecoSPDVCut5[ii][0]->Add(h2dRecoSPDVCut5[ii][iset]);
			}//
		}//iset
	}//ii

	for (int ii=0; ii<2; ii++){
		h1dGenPt[ii] = (TH1D*)h3dGenSPDV[ii][0]->ProjectionX(Form("h1dGenPt_%d",ii),1,5,1,200);
		h1dRecoPt[ii] = (TH1D*)h3dRecoSPDV[ii][0]->ProjectionX(Form("h1dRecoPt_%d",ii),1,10,1,200);
		h1dRecoCut1Pt[ii] = (TH1D*)h2dRecoSPDVCut1[ii][0]->ProjectionX(Form("h1dRecoCut1Pt_%d",ii));
		h1dRecoCut2Pt[ii] = (TH1D*)h2dRecoSPDVCut2[ii][0]->ProjectionX(Form("h1dRecoCut2Pt_%d",ii));
		h1dRecoCut3Pt[ii] = (TH1D*)h2dRecoSPDVCut3[ii][0]->ProjectionX(Form("h1dRecoCut3Pt_%d",ii));
		h1dRecoCut4Pt[ii] = (TH1D*)h2dRecoSPDVCut4[ii][0]->ProjectionX(Form("h1dRecoCut4Pt_%d",ii));
		h1dRecoCut5Pt[ii] = (TH1D*)h2dRecoSPDVCut5[ii][0]->ProjectionX(Form("h1dRecoCut5Pt_%d",ii));

		h1dRecoPt[ii]->Divide(h1dGenPt[ii]);
		h1dRecoPt[ii]->SetMarkerStyle(24+ii);
		h1dRecoPt[ii]->SetMarkerColor(nColor[ii]);
		h1dRecoPt[ii]->SetLineColor(nColor[ii]);

		h1dRecoCut1Pt[ii]->Divide(h1dGenPt[ii]);
		h1dRecoCut1Pt[ii]->SetMarkerStyle(24+ii);
		h1dRecoCut1Pt[ii]->SetMarkerColor(nColor[ii]);
		h1dRecoCut1Pt[ii]->SetLineColor(nColor[ii]);

		h1dRecoCut2Pt[ii]->Divide(h1dGenPt[ii]);
		h1dRecoCut2Pt[ii]->SetMarkerStyle(24+ii);
		h1dRecoCut2Pt[ii]->SetMarkerColor(nColor[ii]);
		h1dRecoCut2Pt[ii]->SetLineColor(nColor[ii]);

		h1dRecoCut3Pt[ii]->Divide(h1dGenPt[ii]);
		h1dRecoCut3Pt[ii]->SetMarkerStyle(24+ii);
		h1dRecoCut3Pt[ii]->SetMarkerColor(nColor[ii]);
		h1dRecoCut3Pt[ii]->SetLineColor(nColor[ii]);

		h1dRecoCut4Pt[ii]->Divide(h1dGenPt[ii]);
		h1dRecoCut4Pt[ii]->SetMarkerStyle(24+ii);
		h1dRecoCut4Pt[ii]->SetMarkerColor(nColor[ii]);
		h1dRecoCut4Pt[ii]->SetLineColor(nColor[ii]);

		h1dRecoCut5Pt[ii]->Divide(h1dGenPt[ii]);
		h1dRecoCut5Pt[ii]->SetMarkerStyle(24+ii);
		h1dRecoCut5Pt[ii]->SetMarkerColor(nColor[ii]);
		h1dRecoCut5Pt[ii]->SetLineColor(nColor[ii]);
	}

	//return;

	/*
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

		h1dGenSPD[iset] = (TH1D*)h3dGenSPDV[iset]->ProjectionZ(Form("h1dGenSPD_%d",iset),1,4,1,5);
		h1dRecoSPD[iset] = (TH1D*)h3dRecoSPDV[iset]->ProjectionZ(Form("h1dRecoSPD_%d",iset),1,4,1,10);

		h1dGenSPD[iset]->Rebin(5);
		h1dRecoSPD[iset]->Rebin(5);

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


		h1dRecoSPD[iset]->Divide(h1dGenSPD[iset]);
		h1dRecoSPD[iset]->SetMarkerStyle(24);
		h1dRecoSPD[iset]->SetMarkerColor(nColor[iset]);
		h1dRecoSPD[iset]->SetLineColor(nColor[iset]);
	}
	*/

	{
		TCanvas *c1 = new TCanvas("c1","c1",1.2*500,500);
		gPad->SetMargin(0.12,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(1,0,12,0.12);

		h1dRecoPt[0]->Draw("p same");
		h1dRecoPt[1]->Draw("p same");

		TH1D *h1dRecoPtRatio = (TH1D*)h1dRecoPt[1]->Clone("h1dRecoPtRatio");
		h1dRecoPtRatio->Divide(h1dRecoPt[0]);

		TCanvas *c1r = new TCanvas("c1r","c1r",1.2*500,500);
		gPad->SetMargin(0.12,0.05,0.12,0.03);
		htmp = (TH1D*)gPad->DrawFrame(1,0.5,12,1.5);

		h1dRecoPtRatio->Draw("p same");

	}

	TCanvas *c2 = new TCanvas("c2","c2",1.1*3*400,2*400);
	c2->Divide(3,2);

	TCanvas *c2r = new TCanvas("c2r","c2r",1.1*3*400,2*400);
	c2r->Divide(3,2);

	{
		c2->cd(1);
		gPad->SetMargin(0.12,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(1,0,12,0.20);

		h1dRecoCut1Pt[0]->Draw("p same");
		h1dRecoCut1Pt[1]->Draw("p same");

		TH1D *h1dRecoCut1PtR = (TH1D*)h1dRecoCut1Pt[1]->Clone("h1dRecoCut1PtR");
		h1dRecoCut1PtR->Divide(h1dRecoCut1Pt[0]);

		c2r->cd(1);
		gPad->SetMargin(0.12,0.05,0.12,0.03);
		htmp = (TH1D*)gPad->DrawFrame(1,0.5,12,1.5);

		h1dRecoCut1PtR->Draw("p same");
	}

	{
		c2->cd(2);
		gPad->SetMargin(0.12,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(1,0,12,0.20);

		h1dRecoCut2Pt[0]->Draw("p same");
		h1dRecoCut2Pt[1]->Draw("p same");

		TH1D *h1dRecoCut2PtR = (TH1D*)h1dRecoCut2Pt[1]->Clone("h1dRecoCut2PtR");
		h1dRecoCut2PtR->Divide(h1dRecoCut2Pt[0]);

		c2r->cd(2);
		gPad->SetMargin(0.12,0.05,0.12,0.03);
		htmp = (TH1D*)gPad->DrawFrame(1,0.5,12,1.5);

		h1dRecoCut2PtR->Draw("p same");
	}

	{
		c2->cd(3);
		gPad->SetMargin(0.12,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(1,0,12,0.20);

		h1dRecoCut3Pt[0]->Draw("p same");
		h1dRecoCut3Pt[1]->Draw("p same");

		TH1D *h1dRecoCut3PtR = (TH1D*)h1dRecoCut3Pt[1]->Clone("h1dRecoCut3PtR");
		h1dRecoCut3PtR->Divide(h1dRecoCut3Pt[0]);

		c2r->cd(3);
		gPad->SetMargin(0.12,0.05,0.12,0.03);
		htmp = (TH1D*)gPad->DrawFrame(1,0.5,12,1.5);

		h1dRecoCut3PtR->Draw("p same");
	}

	{
		c2->cd(4);
		gPad->SetMargin(0.12,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(1,0,12,0.20);

		h1dRecoCut4Pt[0]->Draw("p same");
		h1dRecoCut4Pt[1]->Draw("p same");

		TH1D *h1dRecoCut4PtR = (TH1D*)h1dRecoCut4Pt[1]->Clone("h1dRecoCut4PtR");
		h1dRecoCut4PtR->Divide(h1dRecoCut4Pt[0]);

		c2r->cd(4);
		gPad->SetMargin(0.12,0.05,0.12,0.03);
		htmp = (TH1D*)gPad->DrawFrame(1,0.5,12,1.5);

		h1dRecoCut4PtR->Draw("p same");
	}

	{
		c2->cd(5);
		gPad->SetMargin(0.12,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(1,0,12,0.20);

		h1dRecoCut5Pt[0]->Draw("p same");
		h1dRecoCut5Pt[1]->Draw("p same");

		TH1D *h1dRecoCut5PtR = (TH1D*)h1dRecoCut5Pt[1]->Clone("h1dRecoCut5PtR");
		h1dRecoCut5PtR->Divide(h1dRecoCut5Pt[0]);

		c2r->cd(5);
		gPad->SetMargin(0.12,0.05,0.12,0.03);
		htmp = (TH1D*)gPad->DrawFrame(1,0.5,12,1.5);

		h1dRecoCut5PtR->Draw("p same");
	}

	/*
	{
		TCanvas *c0 = new TCanvas("c0","c0",1.2*500,500);
		gPad->SetMargin(0.12,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,100,0.08);

		h1dRecoSPD[0]->Draw("p same");
		h1dRecoSPD[3]->Draw("p same");
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
*/

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
