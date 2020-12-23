void DrawXiEfficiencyV3(const char *ver="pythia6"){

	string setname[7];
	setname[0] = "Xi reco";
	setname[1] = "+DcaXiDaughters cut";
	setname[2] = "+DcaPos(Neg)ToPrimVertex cut";
	setname[3] = "+DcaBachToPrimVertex cut";
	setname[4] = "+CosineOfPointingAngle cut";
	setname[5] = "+DecayVertex cut";
	setname[6] = "+InvMass cut";

	string esetname[4];
	esetname[0] = "e reco";
	esetname[1] = "+Filterbit check";
	esetname[2] = "+Track cut";
	esetname[3] = "+p_{T}/#eta cut";

	const int nrebin = 10;
	const int nColor[6] = {1, 2, 4, 6, 8, 9};

	TFile *infile0 = new TFile(Form("outfile_XiEfficiencyV3_%s.root",ver),"read");
	TFile *infile1 = new TFile(Form("outfile_XiEfficiencyV4_%s.root",ver),"read");

	TH3D *h3TrueXic0SPD = (TH3D*)infile0->Get("hTrueXic0SPD");
	TH1D *h1TrueXic0SPD[3];
	h1TrueXic0SPD[0] = (TH1D*)h3TrueXic0SPD->ProjectionX("h1TrueXic0SPD0",1,5,1,15);
	h1TrueXic0SPD[1] = (TH1D*)h3TrueXic0SPD->ProjectionX("h1TrueXic0SPD1",1,5,16,30);
	h1TrueXic0SPD[2] = (TH1D*)h3TrueXic0SPD->ProjectionX("h1TrueXic0SPD2",1,5,31,50);

	TH2D *h2TrueXic0CharmSPD = (TH2D*)infile0->Get("hTrueXic0CharmSPD");
	TH2D *h2TrueXic0BottomSPD = (TH2D*)infile0->Get("hTrueXic0BottomSPD");
	TH1D *h1TrueXic0CharmSPD[3];
	TH1D *h1TrueXic0BottomSPD[3];

	h1TrueXic0CharmSPD[0] = (TH1D*)h2TrueXic0CharmSPD->ProjectionX("h1TrueXic0CharmSPD0",1,15);
	h1TrueXic0CharmSPD[1] = (TH1D*)h2TrueXic0CharmSPD->ProjectionX("h1TrueXic0CharmSPD1",16,30);
	h1TrueXic0CharmSPD[2] = (TH1D*)h2TrueXic0CharmSPD->ProjectionX("h1TrueXic0CharmSPD2",31,50);

	h1TrueXic0BottomSPD[0] = (TH1D*)h2TrueXic0BottomSPD->ProjectionX("h1TrueXic0BottomSPD0",1,15);
	h1TrueXic0BottomSPD[1] = (TH1D*)h2TrueXic0BottomSPD->ProjectionX("h1TrueXic0BottomSPD1",16,30);
	h1TrueXic0BottomSPD[2] = (TH1D*)h2TrueXic0BottomSPD->ProjectionX("h1TrueXic0BottomSPD2",31,50);

	TH2D *h2TrueXiSPD[7];
	TH1D *h1TrueXiSPD[7][3];

	TH2D *h2TrueXiCharmSPD[7];
	TH1D *h1TrueXiCharmSPD[7][3];

	TH2D *h2TrueXiBottomSPD[7];
	TH1D *h1TrueXiBottomSPD[7][3];

	for (int ii=0; ii<6; ii++){
		h2TrueXiSPD[ii] = (TH2D*)infile1->Get(Form("hTrueXiSPD%d",ii));
		h2TrueXiCharmSPD[ii] = (TH2D*)infile1->Get(Form("hTrueXiCharmSPD%d",ii));
		h2TrueXiBottomSPD[ii] = (TH2D*)infile1->Get(Form("hTrueXiBottomSPD%d",ii));

		h1TrueXiSPD[ii][0] = (TH1D*)h2TrueXiSPD[ii]->ProjectionX(Form("h1TrueXiSPD_%d_%d",ii,0),1,15);
		h1TrueXiSPD[ii][1] = (TH1D*)h2TrueXiSPD[ii]->ProjectionX(Form("h1TrueXiSPD_%d_%d",ii,1),16,30);
		h1TrueXiSPD[ii][2] = (TH1D*)h2TrueXiSPD[ii]->ProjectionX(Form("h1TrueXiSPD_%d_%d",ii,2),31,50);

		h1TrueXiCharmSPD[ii][0] = (TH1D*)h2TrueXiCharmSPD[ii]->ProjectionX(Form("h1TrueXiCharmSPD_%d_%d",ii,0),1,15);
		h1TrueXiCharmSPD[ii][1] = (TH1D*)h2TrueXiCharmSPD[ii]->ProjectionX(Form("h1TrueXiCharmSPD_%d_%d",ii,1),16,30);
		h1TrueXiCharmSPD[ii][2] = (TH1D*)h2TrueXiCharmSPD[ii]->ProjectionX(Form("h1TrueXiCharmSPD_%d_%d",ii,2),31,50);

		h1TrueXiBottomSPD[ii][0] = (TH1D*)h2TrueXiBottomSPD[ii]->ProjectionX(Form("h1TrueXiBottomSPD_%d_%d",ii,0),1,15);
		h1TrueXiBottomSPD[ii][1] = (TH1D*)h2TrueXiBottomSPD[ii]->ProjectionX(Form("h1TrueXiBottomSPD_%d_%d",ii,1),16,30);
		h1TrueXiBottomSPD[ii][2] = (TH1D*)h2TrueXiBottomSPD[ii]->ProjectionX(Form("h1TrueXiBottomSPD_%d_%d",ii,2),31,50);

			for (int jj=0; jj<3; jj++){
			h1TrueXiSPD[ii][jj]->Divide(h1TrueXic0SPD[jj]);
			h1TrueXiSPD[ii][jj]->SetMarkerColor(nColor[ii]);
			h1TrueXiSPD[ii][jj]->SetLineColor(nColor[ii]);
			h1TrueXiSPD[ii][jj]->SetMarkerStyle(24+jj);

			h1TrueXiCharmSPD[ii][jj]->Divide(h1TrueXic0CharmSPD[jj]);
			h1TrueXiCharmSPD[ii][jj]->SetMarkerColor(nColor[ii]);
			h1TrueXiCharmSPD[ii][jj]->SetLineColor(nColor[ii]);
			h1TrueXiCharmSPD[ii][jj]->SetMarkerStyle(24+jj);

			h1TrueXiBottomSPD[ii][jj]->Divide(h1TrueXic0BottomSPD[jj]);
			h1TrueXiBottomSPD[ii][jj]->SetMarkerColor(nColor[ii]);
			h1TrueXiBottomSPD[ii][jj]->SetLineColor(nColor[ii]);
			h1TrueXiBottomSPD[ii][jj]->SetMarkerStyle(20+jj);
		}
	}
		
	TH2D *h2TrueEeSPD[4];
	TH1D *h1TrueEeSPD[4][3];

	TH2D *h2TrueEeCharmSPD[4];
	TH1D *h1TrueEeCharmSPD[4][3];

	TH2D *h2TrueEeBottomSPD[4];
	TH1D *h1TrueEeBottomSPD[4][3];

	for (int ii=0; ii<4; ii++){
		h2TrueEeSPD[ii] = (TH2D*)infile0->Get(Form("hTrueEeSPD%d",ii));
		h2TrueEeCharmSPD[ii] = (TH2D*)infile0->Get(Form("hTrueEeCharmSPD%d",ii));
		h2TrueEeBottomSPD[ii] = (TH2D*)infile0->Get(Form("hTrueEeBottomSPD%d",ii));

		h1TrueEeSPD[ii][0] = (TH1D*)h2TrueEeSPD[ii]->ProjectionX(Form("h1TrueEeSPD_%d_%d",ii,0),1,15);
		h1TrueEeSPD[ii][1] = (TH1D*)h2TrueEeSPD[ii]->ProjectionX(Form("h1TrueEeSPD_%d_%d",ii,1),16,30);
		h1TrueEeSPD[ii][2] = (TH1D*)h2TrueEeSPD[ii]->ProjectionX(Form("h1TrueEeSPD_%d_%d",ii,2),31,50);

		h1TrueEeCharmSPD[ii][0] = (TH1D*)h2TrueEeCharmSPD[ii]->ProjectionX(Form("h1TrueEeCharmSPD_%d_%d",ii,0),1,15);
		h1TrueEeCharmSPD[ii][1] = (TH1D*)h2TrueEeCharmSPD[ii]->ProjectionX(Form("h1TrueEeCharmSPD_%d_%d",ii,1),16,30);
		h1TrueEeCharmSPD[ii][2] = (TH1D*)h2TrueEeCharmSPD[ii]->ProjectionX(Form("h1TrueEeCharmSPD_%d_%d",ii,2),31,50);

		h1TrueEeBottomSPD[ii][0] = (TH1D*)h2TrueEeBottomSPD[ii]->ProjectionX(Form("h1TrueEeBottomSPD_%d_%d",ii,0),1,15);
		h1TrueEeBottomSPD[ii][1] = (TH1D*)h2TrueEeBottomSPD[ii]->ProjectionX(Form("h1TrueEeBottomSPD_%d_%d",ii,1),16,30);
		h1TrueEeBottomSPD[ii][2] = (TH1D*)h2TrueEeBottomSPD[ii]->ProjectionX(Form("h1TrueEeBottomSPD_%d_%d",ii,2),31,50);

			for (int jj=0; jj<3; jj++){
			h1TrueEeSPD[ii][jj]->Divide(h1TrueXic0SPD[jj]);
			h1TrueEeSPD[ii][jj]->SetMarkerColor(nColor[ii]);
			h1TrueEeSPD[ii][jj]->SetLineColor(nColor[ii]);
			h1TrueEeSPD[ii][jj]->SetMarkerStyle(24+jj);

			h1TrueEeCharmSPD[ii][jj]->Divide(h1TrueXic0CharmSPD[jj]);
			h1TrueEeCharmSPD[ii][jj]->SetMarkerColor(nColor[ii]);
			h1TrueEeCharmSPD[ii][jj]->SetLineColor(nColor[ii]);
			h1TrueEeCharmSPD[ii][jj]->SetMarkerStyle(24+jj);

			h1TrueEeBottomSPD[ii][jj]->Divide(h1TrueXic0BottomSPD[jj]);
			h1TrueEeBottomSPD[ii][jj]->SetMarkerColor(nColor[ii]);
			h1TrueEeBottomSPD[ii][jj]->SetLineColor(nColor[ii]);
			h1TrueEeBottomSPD[ii][jj]->SetMarkerStyle(20+jj);
		}
	}

	//return;

	TCanvas *c2 = new TCanvas("c2","c2",1.1*3*400,1*400);
	c2->Divide(3,1);
	for (int ii=1; ii<4; ii++)
	{
		c2->cd(ii);
		gPad->SetMargin(0.15,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(1,0,12,0.9);
		htmp->GetXaxis()->SetTitle("p_{T}^{#Xi_{c}^{0}} [GeV/c]");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetTitle("Electron reconstruction efficiency");
		htmp->GetYaxis()->SetTitleSize(0.05);

		h1TrueEeSPD[ii][0]->Draw("p same");
		h1TrueEeSPD[ii][2]->Draw("p same");

		TLegend *leg = new TLegend(0.25,0.15,0.85,0.35);
		leg->SetFillStyle(0);
		leg->SetTextSize(0.04);
		leg->SetBorderSize(0);
		if ( strstr(ver,"pythia6") ){
			leg->AddEntry("","PYTHIA6","h");
		}else if ( strstr(ver,"pythia8") ){
			leg->AddEntry("","PYTHIA8","h");
		}
		if ( ii==1 )
			leg->AddEntry("","e reco + filterbit check","h");
		else if ( ii==2 )
			leg->AddEntry("","e reco + filterbit check + track cut","h");
		else if ( ii==3 )
			leg->AddEntry("","e reco + filterbit check + track cut + p_{T}/#eta cut","h");
		leg->AddEntry(h1TrueEeSPD[ii][0],"0#leqN_{SPD}<15","P");
		leg->AddEntry(h1TrueEeSPD[ii][2],"30#leqN_{SPD}<50","P");
		leg->Draw();
	}

	TCanvas *c2_ = new TCanvas("c2_","c2_",1.1*3*400,1*400);
	c2_->Divide(3,1);
	for (int ii=1; ii<4; ii++)
	{
		c2_->cd(ii);
		gPad->SetMargin(0.15,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(1,0,12,0.9);
		htmp->GetXaxis()->SetTitle("p_{T}^{#Xi_{c}^{0}} [GeV/c]");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetTitle("Electron reconstruction efficiency");
		htmp->GetYaxis()->SetTitleSize(0.05);

		h1TrueEeCharmSPD[ii][0]->Draw("p same");
		h1TrueEeCharmSPD[ii][2]->Draw("p same");

		h1TrueEeBottomSPD[ii][0]->Draw("p same");
		h1TrueEeBottomSPD[ii][2]->Draw("p same");

		TLegend *leg = new TLegend(0.25,0.15,0.85,0.4);
		leg->SetFillStyle(0);
		leg->SetTextSize(0.04);
		leg->SetBorderSize(0);
		if ( strstr(ver,"pythia6") ){
			leg->AddEntry("","PYTHIA6","h");
		}else if ( strstr(ver,"pythia8") ){
			leg->AddEntry("","PYTHIA8","h");
		}
		if ( ii==1 )
			leg->AddEntry("","e reco + filterbit check","h");
		else if ( ii==2 )
			leg->AddEntry("","e reco + filterbit check + track cut","h");
		else if ( ii==3 )
			leg->AddEntry("","e reco + filterbit check + track cut + p_{T}/#eta cut","h");
		leg->AddEntry(h1TrueEeCharmSPD[ii][0],"Charm, 0#leqN_{SPD}<15","P");
		leg->AddEntry(h1TrueEeCharmSPD[ii][2],"Charm, 30#leqN_{SPD}<50","P");
		leg->AddEntry(h1TrueEeBottomSPD[ii][0],"Bottom, 0#leqN_{SPD}<15","P");
		leg->AddEntry(h1TrueEeBottomSPD[ii][2],"Bottom, 30#leqN_{SPD}<50","P");
		leg->Draw();
	}

	TCanvas *c3 = new TCanvas("c3","c3",1.1*3*400,2*400);
	c3->Divide(3,2);
	for (int ii=0; ii<6; ii++)
	{
		c3->cd(ii+1);

		gPad->SetMargin(0.15,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(1,0,12,1.0);
		htmp->GetXaxis()->SetTitle("p_{T}^{#Xi_{c}^{0}} [GeV/c]");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetTitle("#Xi reconstruction efficiency");
		htmp->GetYaxis()->SetTitleSize(0.05);

		h1TrueXiSPD[ii][0]->Draw("p same");
		h1TrueXiSPD[ii][2]->Draw("p same");

		TLegend *leg = new TLegend(0.25,0.70,0.9,0.90);
		leg->SetFillStyle(0);
		leg->SetTextSize(0.04);
		leg->SetBorderSize(0);
		if ( strstr(ver,"pythia6") ){
			leg->AddEntry("","PYTHIA6","h");
		}else if ( strstr(ver,"pythia8") ){
			leg->AddEntry("","PYTHIA8","h");
		}
		leg->AddEntry("",Form("%s",setname[ii].c_str()),"h");
		leg->AddEntry(h1TrueXiSPD[ii][0],"0#leqN_{SPD}<15","P");
		leg->AddEntry(h1TrueXiSPD[ii][2],"30#leqN_{SPD}<50","P");
		leg->Draw();

	}

	TCanvas *c3_ = new TCanvas("c3_","c3_",1.1*3*400,2*400);
	c3_->Divide(3,2);
	for (int ii=0; ii<6; ii++)
	{
		c3_->cd(ii+1);

		gPad->SetMargin(0.15,0.05,0.12,0.03);
		TH1D *htmp = (TH1D*)gPad->DrawFrame(1,0,12,1.0);
		htmp->GetXaxis()->SetTitle("p_{T}^{#Xi_{c}^{0}} [GeV/c]");
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetTitle("#Xi reconstruction efficiency");
		htmp->GetYaxis()->SetTitleSize(0.05);

		h1TrueXiCharmSPD[ii][0]->Draw("p same");
		h1TrueXiCharmSPD[ii][2]->Draw("p same");

		h1TrueXiBottomSPD[ii][0]->Draw("p same");
		h1TrueXiBottomSPD[ii][2]->Draw("p same");

		TLegend *leg = new TLegend(0.25,0.65,0.9,0.90);
		leg->SetFillStyle(0);
		leg->SetTextSize(0.04);
		leg->SetBorderSize(0);
		if ( strstr(ver,"pythia6") ){
			leg->AddEntry("","PYTHIA6","h");
		}else if ( strstr(ver,"pythia8") ){
			leg->AddEntry("","PYTHIA8","h");
		}
		leg->AddEntry("",Form("%s",setname[ii].c_str()),"h");
		leg->AddEntry(h1TrueXiCharmSPD[ii][0],"Charm, 0#leqN_{SPD}<15","P");
		leg->AddEntry(h1TrueXiCharmSPD[ii][2],"Charm, 30#leqN_{SPD}<50","P");
		leg->AddEntry(h1TrueXiBottomSPD[ii][0],"Bottom, 0#leqN_{SPD}<15","P");
		leg->AddEntry(h1TrueXiBottomSPD[ii][2],"Bottom, 30#leqN_{SPD}<50","P");
		leg->Draw();

	}


}
