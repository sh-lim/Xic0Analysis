void DrawXiEfficiencyV5(const char *ver="pythia6"){

	string esetname[7];
	esetname[0] = "e reco+Filterbit check";
	esetname[1] = "e reco+Filterbit check+Require TPC refit";
	esetname[2] = "+Require ITS refit";
	esetname[3] = "+N_{ITS cluster} cut";
	esetname[4] = "+#chi^{2}/N_{ITS cluster}";
	esetname[5] = "+DCA cut";
	esetname[6] = "+N_{TPC PID cluster}";

	const int nrebin = 10;
	const int nColor[7] = {1, 2, 4, 6, 8, 9, 1};

	TFile *infile = new TFile(Form("outfile_XiEfficiencyV5_%s.root",ver),"read");

	TH3D *h3TrueXic0SPD = (TH3D*)infile->Get("hTrueXic0SPD");
	TH1D *h1TrueXic0Pt[3];
	h1TrueXic0Pt[0] = (TH1D*)h3TrueXic0SPD->ProjectionX("h1TrueXic0Pt0",1,5,1,15);
	h1TrueXic0Pt[1] = (TH1D*)h3TrueXic0SPD->ProjectionX("h1TrueXic0Pt1",1,5,16,30);
	h1TrueXic0Pt[2] = (TH1D*)h3TrueXic0SPD->ProjectionX("h1TrueXic0SPD2",1,5,31,50);

	TH1D *h1TrueXic0SPD = (TH1D*)h3TrueXic0SPD->ProjectionZ("h1TrueXic0SPD",2,4,1,5);
	h1TrueXic0SPD->Rebin(2);

	TH2D *h2TrueEeSPD[7];
	TH1D *h1TrueEePt[7][3];
	TH1D *h1TrueEeSPD[7];

	for (int ii=0; ii<7; ii++){
		h2TrueEeSPD[ii] = (TH2D*)infile->Get(Form("hTrueEeSPD1Case%d",ii));

		h1TrueEePt[ii][0] = (TH1D*)h2TrueEeSPD[ii]->ProjectionX(Form("h1TrueEePt_%d_%d",ii,0),1,15);
		h1TrueEePt[ii][1] = (TH1D*)h2TrueEeSPD[ii]->ProjectionX(Form("h1TrueEePt_%d_%d",ii,1),16,30);
		h1TrueEePt[ii][2] = (TH1D*)h2TrueEeSPD[ii]->ProjectionX(Form("h1TrueEePt_%d_%d",ii,2),31,50);

			for (int jj=0; jj<3; jj++){
			h1TrueEePt[ii][jj]->Divide(h1TrueXic0Pt[jj]);
			h1TrueEePt[ii][jj]->SetMarkerColor(nColor[ii]);
			h1TrueEePt[ii][jj]->SetLineColor(nColor[ii]);
			h1TrueEePt[ii][jj]->SetMarkerStyle(24+jj);
		}

			h1TrueEeSPD[ii] = (TH1D*)h2TrueEeSPD[ii]->ProjectionY(Form("h1TrueEeSPD_%d",ii),2,4);
			h1TrueEeSPD[ii]->Rebin(2);
			h1TrueEeSPD[ii]->Divide(h1TrueXic0SPD);
			h1TrueEeSPD[ii]->SetMarkerColor(nColor[ii]);
			h1TrueEeSPD[ii]->SetLineColor(nColor[ii]);
			h1TrueEeSPD[ii]->SetMarkerStyle(24);
	}

	//return;

	TCanvas *c2 = new TCanvas("c2","c2",1.1*3*400,2*400);
	c2->Divide(3,2);
	for (int ii=1; ii<7; ii++)
	{
		c2->cd(ii);
		gPad->SetMargin(0.15,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(1,0,12,0.9);
		htmp->GetXaxis()->SetTitle("p_{T}^{#Xi_{c}^{0}} [GeV/c]");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetTitle("Electron reconstruction efficiency");
		htmp->GetYaxis()->SetTitleSize(0.05);

		h1TrueEePt[ii][0]->Draw("p same");
		h1TrueEePt[ii][2]->Draw("p same");

		TLegend *leg = new TLegend(0.25,0.15,0.85,0.35);
		leg->SetFillStyle(0);
		leg->SetTextSize(0.04);
		leg->SetBorderSize(0);
		if ( strstr(ver,"pythia6") ){
			leg->AddEntry("","PYTHIA6","h");
		}else if ( strstr(ver,"pythia8") ){
			leg->AddEntry("","PYTHIA8","h");
		}
		leg->AddEntry("",Form("%s",esetname[ii].c_str()),"h");
		leg->AddEntry(h1TrueEePt[ii][0],"0#leqN_{SPD}<15","P");
		leg->AddEntry(h1TrueEePt[ii][2],"30#leqN_{SPD}<50","P");
		leg->Draw();
	}

	TCanvas *c3 = new TCanvas("c3","c3",1.1*3*400,2*400);
	c3->Divide(3,2);
	for (int ii=1; ii<7; ii++)
	{
		c3->cd(ii);
		gPad->SetMargin(0.15,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,100,0.9);
		htmp->GetXaxis()->SetTitle("N_{SPD}");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetTitle("Electron reconstruction efficiency");
		htmp->GetYaxis()->SetTitleSize(0.05);

		h1TrueEeSPD[ii]->Draw("p same");

		TLegend *leg = new TLegend(0.25,0.15,0.85,0.35);
		leg->SetFillStyle(0);
		leg->SetTextSize(0.04);
		leg->SetBorderSize(0);
		leg->AddEntry("","2<p_{T}^{#Xi_{c}^{0}}<5 GeV/c","h");
		if ( strstr(ver,"pythia6") ){
			leg->AddEntry("","PYTHIA6","h");
		}else if ( strstr(ver,"pythia8") ){
			leg->AddEntry("","PYTHIA8","h");
		}
		leg->AddEntry("",Form("%s",esetname[ii].c_str()),"h");
		leg->Draw();
	}


}
