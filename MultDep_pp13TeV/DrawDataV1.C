void DrawDataV1(){

	TFile *infile = new TFile("outfile_FilterDataV1.root","read");

	const int npt = 7;
	const double ptbin[npt+1] = {1, 2, 3, 4, 5, 6, 8, 12};

	TH2D *h2dReco_pt_cosoa[2][2]; //[trig][sign]
	TH2D *h2dReco_pt_oa[2][2]; //[trig][sign]
	TH2D *h2dReco_pt_mass[2][2]; //[trig][sign]
	TH2D *h2dReco_pt_mass70[2][2]; //[trig][sign]

	TH1D *h1dReco_pt_cosoa[2][2][npt];
	TH1D *h1dReco_pt_oa[2][2][npt];
	TH1D *h1dReco_pt_mass[2][2][npt];
	TH1D *h1dReco_pt_mass70[2][2][npt];

	for (int itrig=0; itrig<2; itrig++){
		for (int ichg=0; ichg<2; ichg++){
			h2dReco_pt_cosoa[itrig][ichg] = (TH2D*)infile->Get(Form("h2dReco_pt_cosoa_set0_trig%d_chg%d",itrig,ichg));
			h2dReco_pt_oa[itrig][ichg] = (TH2D*)infile->Get(Form("h2dReco_pt_oa_set0_trig%d_chg%d",itrig,ichg));
			h2dReco_pt_mass[itrig][ichg] = (TH2D*)infile->Get(Form("h2dReco_pt_mass_set0_trig%d_chg%d",itrig,ichg));
			h2dReco_pt_mass70[itrig][ichg] = (TH2D*)infile->Get(Form("h2dReco_pt_mass70_set0_trig%d_chg%d",itrig,ichg));

			for (int ipt=0; ipt<npt; ipt++){
				h1dReco_pt_cosoa[itrig][ichg][ipt] = (TH1D*)h2dReco_pt_cosoa[itrig][ichg]->ProjectionY(Form("h1dReco_pt_cosoa_%d_%d_%d",itrig,ichg,ipt),ipt+1,ipt+1);
				h1dReco_pt_cosoa[itrig][ichg][ipt]->Sumw2();

				h1dReco_pt_oa[itrig][ichg][ipt] = (TH1D*)h2dReco_pt_oa[itrig][ichg]->ProjectionY(Form("h1dReco_pt_oa_%d_%d_%d",itrig,ichg,ipt),ipt+1,ipt+1);
				h1dReco_pt_oa[itrig][ichg][ipt]->Sumw2();

				h1dReco_pt_mass[itrig][ichg][ipt] = (TH1D*)h2dReco_pt_mass[itrig][ichg]->ProjectionY(Form("h1dReco_pt_mass_%d_%d_%d",itrig,ichg,ipt),ipt+1,ipt+1);
				h1dReco_pt_mass[itrig][ichg][ipt]->Sumw2();

				h1dReco_pt_mass70[itrig][ichg][ipt] = (TH1D*)h2dReco_pt_mass70[itrig][ichg]->ProjectionY(Form("h1dReco_pt_mass70_%d_%d_%d",itrig,ichg,ipt),ipt+1,ipt+1);
				h1dReco_pt_mass70[itrig][ichg][ipt]->Sumw2();

				h1dReco_pt_cosoa[itrig][ichg][ipt]->Rebin(4);
				h1dReco_pt_oa[itrig][ichg][ipt]->Rebin(4);
				h1dReco_pt_mass[itrig][ichg][ipt]->Rebin(6);
				h1dReco_pt_mass70[itrig][ichg][ipt]->Rebin(6);

			}//ipt
		}//ichg
	}//itrig

	TCanvas *c1[2];
	TCanvas *c2[2];
	TCanvas *c3[2];

	/*
	for (int itrig=0; itrig<2; itrig++){

		c1[itrig] = new TCanvas(Form("c1_%d",itrig),Form("c1_%d",itrig),1.1*4*300,2*300);
		c1[itrig]->Divide(4,2);

		for (int ipt=0; ipt<npt; ipt++){

			c1[itrig]->cd(ipt+1);
			gPad->SetMargin(0.14,0.03,0.12,0.03);

			float max = TMath::Max(h1dReco_pt_cosoa[itrig][0][ipt]->GetMaximum(), h1dReco_pt_cosoa[itrig][1][ipt]->GetMaximum());

			TH1D *htmp;
			if ( ipt==0 ){
				htmp = (TH1D*)gPad->DrawFrame(-1.1,0,1.1,1.2*max);
			}else if ( ipt==1 ){
				htmp = (TH1D*)gPad->DrawFrame(-0.5,0,1.1,1.2*max);
			}else{
				htmp = (TH1D*)gPad->DrawFrame(0,0,1.1,1.2*max);
			}

			h1dReco_pt_cosoa[itrig][0][ipt]->SetMarkerStyle(20);
			h1dReco_pt_cosoa[itrig][0][ipt]->SetLineColor(1);
			h1dReco_pt_cosoa[itrig][0][ipt]->SetMarkerColor(1);
			h1dReco_pt_cosoa[itrig][0][ipt]->Draw("p same");

			h1dReco_pt_cosoa[itrig][1][ipt]->SetMarkerStyle(24);
			h1dReco_pt_cosoa[itrig][1][ipt]->SetLineColor(2);
			h1dReco_pt_cosoa[itrig][1][ipt]->SetMarkerColor(2);
			h1dReco_pt_cosoa[itrig][1][ipt]->Draw("p same");

		}//ipt
	}//itrig
	*/


	for (int itrig=0; itrig<2; itrig++){

		c2[itrig] = new TCanvas(Form("c2_%d",itrig),Form("c2_%d",itrig),1.1*4*300,2*300);
		c2[itrig]->Divide(4,2);

		for (int ipt=0; ipt<npt; ipt++){

			c2[itrig]->cd(ipt+1);
			gPad->SetMargin(0.14,0.03,0.12,0.03);

			float max = TMath::Max(h1dReco_pt_oa[itrig][0][ipt]->GetMaximum(), h1dReco_pt_oa[itrig][1][ipt]->GetMaximum());

			TH1D *htmp;
			if ( ipt==0 ){
				htmp = (TH1D*)gPad->DrawFrame(0,0,180,1.2*max);
			}else if ( ipt==1 ){
				htmp = (TH1D*)gPad->DrawFrame(0,0,135,1.2*max);
			}else{
				htmp = (TH1D*)gPad->DrawFrame(0,0,90,1.2*max);
			}

			htmp->GetYaxis()->SetTitleSize(0.045);
			htmp->GetYaxis()->SetLabelSize(0.04);
			htmp->GetXaxis()->SetTitleSize(0.045);
			htmp->GetXaxis()->SetLabelSize(0.04);
			htmp->GetXaxis()->SetTitle("Opening angle (deg)");

			h1dReco_pt_oa[itrig][0][ipt]->SetMarkerStyle(20);
			h1dReco_pt_oa[itrig][0][ipt]->SetLineColor(1);
			h1dReco_pt_oa[itrig][0][ipt]->SetMarkerColor(1);
			h1dReco_pt_oa[itrig][0][ipt]->Draw("p same");

			h1dReco_pt_oa[itrig][1][ipt]->SetMarkerStyle(24);
			h1dReco_pt_oa[itrig][1][ipt]->SetLineColor(2);
			h1dReco_pt_oa[itrig][1][ipt]->SetMarkerColor(2);
			h1dReco_pt_oa[itrig][1][ipt]->Draw("p same");

			TLegend *leg = new TLegend(0.6,0.75,0.95,0.95);
			leg->SetFillStyle(0);
			leg->SetBorderSize(0);
			leg->SetTextSize(0.045);
			leg->AddEntry("",Form("%g<p_{T}^{e#Xi}<%g GeV/c",ptbin[ipt],ptbin[ipt+1]),"");
			leg->AddEntry(h1dReco_pt_oa[itrig][0][ipt],"RS","P");
			leg->AddEntry(h1dReco_pt_oa[itrig][1][ipt],"WS","P");
			leg->Draw();

		}//ipt
	}//itrig


	for (int itrig=0; itrig<2; itrig++){
		c3[itrig] = new TCanvas(Form("c3_%d",itrig),Form("c3_%d",itrig),1.1*4*300,2*300);
		c3[itrig]->Divide(4,2);

		for (int ipt=0; ipt<4; ipt++){

			{
				c3[itrig]->cd(ipt+1);
				gPad->SetMargin(0.14,0.03,0.12,0.03);

				float max = h1dReco_pt_mass[itrig][0][ipt]->GetMaximum();
				TH1D *htmp = (TH1D*)gPad->DrawFrame(1.3,0,2.5,1.3*max);

				htmp->GetYaxis()->SetTitleSize(0.045);
				htmp->GetYaxis()->SetLabelSize(0.04);
				htmp->GetXaxis()->SetTitleSize(0.045);
				htmp->GetXaxis()->SetLabelSize(0.04);
				htmp->GetXaxis()->SetTitle("e#Xi mass (GeV/c^{2})");

				h1dReco_pt_mass[itrig][0][ipt]->SetMarkerStyle(20);
				h1dReco_pt_mass[itrig][0][ipt]->SetLineColor(1);
				h1dReco_pt_mass[itrig][0][ipt]->SetMarkerColor(1);
				h1dReco_pt_mass[itrig][0][ipt]->Draw("p same");

				h1dReco_pt_mass[itrig][1][ipt]->SetMarkerStyle(24);
				h1dReco_pt_mass[itrig][1][ipt]->SetLineColor(2);
				h1dReco_pt_mass[itrig][1][ipt]->SetMarkerColor(2);
				h1dReco_pt_mass[itrig][1][ipt]->Draw("p same");

				TLegend *leg = new TLegend(0.6,0.75,0.95,0.95);
				leg->SetFillStyle(0);
				leg->SetBorderSize(0);
				leg->SetTextSize(0.045);
				leg->AddEntry("",Form("%g<p_{T}^{e#Xi}<%g GeV/c",ptbin[ipt],ptbin[ipt+1]),"");
				leg->AddEntry(h1dReco_pt_oa[itrig][0][ipt],"RS","P");
				leg->AddEntry(h1dReco_pt_oa[itrig][1][ipt],"WS","P");
				leg->Draw();
			}

			{
				c3[itrig]->cd(ipt+1+4);
				gPad->SetMargin(0.14,0.03,0.12,0.03);

				float max = h1dReco_pt_mass70[itrig][0][ipt]->GetMaximum();
				TH1D *htmp = (TH1D*)gPad->DrawFrame(1.3,0,2.5,1.3*max);

				htmp->GetYaxis()->SetTitleSize(0.045);
				htmp->GetYaxis()->SetLabelSize(0.04);
				htmp->GetXaxis()->SetTitleSize(0.045);
				htmp->GetXaxis()->SetLabelSize(0.04);
				htmp->GetXaxis()->SetTitle("e#Xi mass (GeV/c^{2})");

				h1dReco_pt_mass70[itrig][0][ipt]->SetMarkerStyle(20);
				h1dReco_pt_mass70[itrig][0][ipt]->SetLineColor(1);
				h1dReco_pt_mass70[itrig][0][ipt]->SetMarkerColor(1);
				h1dReco_pt_mass70[itrig][0][ipt]->Draw("p same");

				h1dReco_pt_mass70[itrig][1][ipt]->SetMarkerStyle(24);
				h1dReco_pt_mass70[itrig][1][ipt]->SetLineColor(2);
				h1dReco_pt_mass70[itrig][1][ipt]->SetMarkerColor(2);
				h1dReco_pt_mass70[itrig][1][ipt]->Draw("p same");

				TLegend *leg = new TLegend(0.6,0.75,0.95,0.95);
				leg->SetFillStyle(0);
				leg->SetBorderSize(0);
				leg->SetTextSize(0.045);
				leg->AddEntry("",Form("%g<p_{T}^{e#Xi}<%g GeV/c",ptbin[ipt],ptbin[ipt+1]),"");
				leg->AddEntry(h1dReco_pt_oa[itrig][0][ipt],"RS","P");
				leg->AddEntry(h1dReco_pt_oa[itrig][1][ipt],"WS","P");
				leg->Draw();
			}

		}
	}

}
