void DrawMult(){

	const int nset = 31;
	string setname[nset] = {
		"LHC16d","LHC16e","LHC16g","LHC16h","LHC16j",
		"LHC16k","LHC16l","LHC16o","LHC16p","LHC16q",
		"LHC17c","LHC17e","LHC17f","LHC17h","LHC17i",
		"LHC17j","LHC17k","LHC17l",
		"LHC18d","LHC18e","LHC18f","LHC18g","LHC18h",
		"LHC18i","LHC18j","LHC18k","LHC18l","LHC18m",
		"LHC18n","LHC18o","LHC18p"
	};

	const int ncent = 3;

	TFile *infile = new TFile("outfile_Data.root","read");

	TH1D *hSPDMult[nset][ncent];

	for (int iset=0; iset<nset; iset++){
		for (int icent=0; icent<ncent; icent++){
			hSPDMult[iset][icent] = (TH1D*)infile->Get(Form("hSPDMult_%s_cent%d",setname[iset].c_str(),icent));
			hSPDMult[iset][icent]->SetLineWidth(2);
			hSPDMult[iset][icent]->SetLineColor(iset%9+1);
			hSPDMult[iset][icent]->SetMarkerColor(iset%9+1);
			hSPDMult[iset][icent]->Scale(1./(hSPDMult[iset][icent]->Integral()+1));
		}
	}

	{
		TCanvas *c1 = new TCanvas("c1","c1",1.2*3*400,400);
		c1->Divide(3,1);
		for (int icent=0; icent<ncent; icent++){
			c1->cd(icent+1);
			gPad->SetMargin(0.12,0.05,0.12,0.05);

			float max = hSPDMult[0][icent]->GetMaximum();

			TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,200,1.2*max);
			htmp->GetXaxis()->SetTitle("SPD Tracklets");
			htmp->GetYaxis()->SetLabelSize(0.04);
			htmp->GetYaxis()->SetTitleSize(0.05);
			htmp->GetXaxis()->SetLabelSize(0.04);
			htmp->GetXaxis()->SetTitleSize(0.05);

			for (int ii=0; ii<10; ii++){
				hSPDMult[ii][icent]->Draw("same");
			}

			TLegend *leg = new TLegend(0.6,0.7,0.9,0.9);
			leg->SetFillStyle(0);
			leg->SetBorderSize(0);
			leg->SetTextSize(0.05);
			leg->AddEntry("","Data LHC16","");
			if ( icent==0 ){
				leg->AddEntry("","V0M 0-0.1%","");
			}else if ( icent==1 ){
				leg->AddEntry("","V0M 0.1-30%","");
			}else if ( icent==2 ){
				leg->AddEntry("","V0M 30-100%","");
			}
			leg->Draw();
		}
	}

	{
		TCanvas *c2 = new TCanvas("c2","c2",1.2*3*400,400);
		c2->Divide(3,1);
		for (int icent=0; icent<ncent; icent++){
			c2->cd(icent+1);
			gPad->SetMargin(0.12,0.05,0.12,0.05);

			float max = hSPDMult[0][icent]->GetMaximum();

			TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,200,1.2*max);
			htmp->GetXaxis()->SetTitle("SPD Tracklets");
			htmp->GetYaxis()->SetLabelSize(0.04);
			htmp->GetYaxis()->SetTitleSize(0.05);
			htmp->GetXaxis()->SetLabelSize(0.04);
			htmp->GetXaxis()->SetTitleSize(0.05);

			for (int ii=10; ii<18; ii++){
				hSPDMult[ii][icent]->Draw("same");
			}

			TLegend *leg = new TLegend(0.6,0.7,0.9,0.9);
			leg->SetFillStyle(0);
			leg->SetBorderSize(0);
			leg->SetTextSize(0.05);
			leg->AddEntry("","Data LHC17","");
			if ( icent==0 ){
				leg->AddEntry("","V0M 0-0.1%","");
			}else if ( icent==1 ){
				leg->AddEntry("","V0M 0.1-30%","");
			}else if ( icent==2 ){
				leg->AddEntry("","V0M 30-100%","");
			}
			leg->Draw();
		}
	}

	{
		TCanvas *c3 = new TCanvas("c3","c3",1.2*3*400,400);
		c3->Divide(3,1);
		for (int icent=0; icent<ncent; icent++){
			c3->cd(icent+1);
			gPad->SetMargin(0.12,0.05,0.12,0.05);

			float max = hSPDMult[0][icent]->GetMaximum();

			TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,200,1.2*max);
			htmp->GetXaxis()->SetTitle("SPD Tracklets");
			htmp->GetYaxis()->SetLabelSize(0.04);
			htmp->GetYaxis()->SetTitleSize(0.05);
			htmp->GetXaxis()->SetLabelSize(0.04);
			htmp->GetXaxis()->SetTitleSize(0.05);

			for (int ii=18; ii<nset; ii++){
				hSPDMult[ii][icent]->Draw("same");
			}

			TLegend *leg = new TLegend(0.6,0.7,0.9,0.9);
			leg->SetFillStyle(0);
			leg->SetBorderSize(0);
			leg->SetTextSize(0.05);
			leg->AddEntry("","Data LHC18","");
			if ( icent==0 ){
				leg->AddEntry("","V0M 0-0.1%","");
			}else if ( icent==1 ){
				leg->AddEntry("","V0M 0.1-30%","");
			}else if ( icent==2 ){
				leg->AddEntry("","V0M 30-100%","");
			}
			leg->Draw();
		}
	}

	TH1D *hSPDMultAll[ncent];

	for (int icent=0; icent<ncent; icent++){
		hSPDMultAll[icent] = (TH1D*)hSPDMult[0][icent]->Clone(Form("hSPDMultAll_cent%d",icent));
		for (int iset=0; iset<nset; iset++){
			if ( setname[iset]=="LHC16t" || setname[iset]=="LHC16q" ){
				continue;
			}
			hSPDMultAll[icent]->Add(hSPDMult[iset][icent]);
		}
	}


	TFile *infileMC = new TFile("outfile_MC.root","read");
	TH1D *hSPDMultMC[4];
	TH1D *hSPDMultMCWT[4][ncent];
	TH1D *hSPDMultMCAll;
	TH1D *hSPDMultMCWTAll[ncent];

	for (int iset=0; iset<4; iset++){
		hSPDMultMC[iset] = (TH1D*)infileMC->Get(Form("hSPDMult_%d",iset));
		for (int icent=1; icent<ncent; icent++){
			hSPDMultMCWT[iset][icent] = (TH1D*)infileMC->Get(Form("hSPDMultWT_%d_cent%d",iset,icent));
		}

		if ( iset==0 ){
			hSPDMultMCAll = (TH1D*)hSPDMultMC[iset]->Clone("hSPDMultMCAll");
			for (int icent=1; icent<ncent; icent++){
				hSPDMultMCWTAll[icent] = (TH1D*)hSPDMultMCWT[iset][icent]->Clone(Form("hSPDMultMCWTAll_cent%d",icent));
			}
		}else if ( iset==1 || iset==2 ){
			hSPDMultMCAll->Add(hSPDMultMC[iset]);
			for (int icent=1; icent<ncent; icent++){
				hSPDMultMCWTAll[icent]->Add(hSPDMultMCWT[iset][icent]);
			}
		}

		hSPDMultMC[iset]->Scale(1./hSPDMultMC[iset]->Integral());
		hSPDMultMC[iset]->SetMarkerColor(iset+1);
		hSPDMultMC[iset]->SetMarkerStyle(24);
		hSPDMultMC[iset]->SetMarkerSize(0.8);
		hSPDMultMC[iset]->SetLineColor(iset+1);
		hSPDMultMC[iset]->SetLineWidth(2);
	}

	hSPDMultMCAll->Scale(1./hSPDMultMCAll->Integral());

	{
		TCanvas *c4 = new TCanvas("c4","c4",1.2*400,400);
		gPad->SetMargin(0.12,0.05,0.12,0.05);

		float max = hSPDMultMC[0]->GetMaximum();

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,200,1.2*max);
		htmp->GetXaxis()->SetTitle("SPD Tracklets");
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);
		htmp->GetXaxis()->SetTitleSize(0.05);

		for (int iset=0; iset<4; iset++){
			hSPDMultMC[iset]->Draw("same");
		}

		TLegend *leg = new TLegend(0.6,0.7,0.9,0.9);
		leg->SetFillStyle(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.05);
		leg->AddEntry("","MC","");
		leg->AddEntry(hSPDMultMC[0],"LHC16","P");
		leg->AddEntry(hSPDMultMC[3],"LHC16 w/ SDD","P");
		leg->AddEntry(hSPDMultMC[1],"LHC17","P");
		leg->AddEntry(hSPDMultMC[2],"LHC18","P");
		leg->Draw();
	}

	TH1D *hRatio[ncent];

	cout << hSPDMultMCAll->Integral(81,200)/hSPDMultMCAll->Integral() << endl;

	for (int icent=0; icent<ncent; icent++){
		hRatio[icent] = (TH1D*)hSPDMultAll[icent]->Clone(Form("hRatio_cent%d",icent));
		hRatio[icent]->Scale(1./hRatio[icent]->Integral());
		hRatio[icent]->Divide(hSPDMultMCAll);

		hRatio[icent]->SetMarkerColor(icent+1);
		hRatio[icent]->SetMarkerStyle(20);
		hRatio[icent]->SetMarkerSize(0.8);
		hRatio[icent]->SetLineColor(icent+1);
		hRatio[icent]->SetLineWidth(2);
	}

	{
		TCanvas *c6 = new TCanvas("c6","c6",1.2*400,400);
		gPad->SetMargin(0.12,0.05,0.12,0.05);

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,100,20);
		htmp->GetXaxis()->SetTitle("SPD Tracklets");
		htmp->GetYaxis()->SetTitle("Weight");
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);
		htmp->GetXaxis()->SetTitleSize(0.05);

		//hRatio[0]->Draw("p same");
		hRatio[1]->Draw("p same");
		hRatio[2]->Draw("p same");

		c6->SaveAs("plots/DrawMult_c6.png");

	}

	{
		TCanvas *c5 = new TCanvas("c5","c5",1.2*400,400);
		gPad->SetMargin(0.12,0.05,0.12,0.05);

		for (int icent=0; icent<ncent; icent++){
			hSPDMultAll[icent]->Scale(1./hSPDMultAll[icent]->Integral());
			hSPDMultAll[icent]->SetMarkerColor(icent+1);
			hSPDMultAll[icent]->SetMarkerStyle(20);
			hSPDMultAll[icent]->SetMarkerSize(0.8);
			hSPDMultAll[icent]->SetLineColor(icent+1);
			hSPDMultAll[icent]->SetLineWidth(2);
		}

		for (int icent=1; icent<ncent; icent++){
			hSPDMultMCWTAll[icent]->Scale(1./hSPDMultMCWTAll[icent]->Integral());
			hSPDMultMCWTAll[icent]->SetMarkerColor(icent+1);
			hSPDMultMCWTAll[icent]->SetMarkerStyle(25);
			hSPDMultMCWTAll[icent]->SetMarkerSize(0.8);
			hSPDMultMCWTAll[icent]->SetLineColor(icent+1);
			hSPDMultMCWTAll[icent]->SetLineWidth(2);
		}

		float max = hSPDMultAll[2]->GetMaximum();

		TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,200,1.2*max);
		htmp->GetXaxis()->SetTitle("SPD Tracklets");
		htmp->GetYaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);
		htmp->GetXaxis()->SetTitleSize(0.05);

		hSPDMultAll[0]->Draw("p same");
		hSPDMultAll[1]->Draw("p same");
		hSPDMultAll[2]->Draw("p same");

		hSPDMultMCAll->SetMarkerStyle(1);
		hSPDMultMCAll->SetLineWidth(2);
		hSPDMultMCAll->SetLineColor(4);
		hSPDMultMCAll->SetMarkerColor(4);
		hSPDMultMCAll->Draw("p same");

		TLegend *leg = new TLegend(0.4,0.7,0.9,0.9);
		leg->SetBorderSize(0);
		leg->SetFillStyle(0);
		leg->SetTextSize(0.05);
		leg->AddEntry(hSPDMultAll[0],"MB data, V0M 0-0.1%","P");
		leg->AddEntry(hSPDMultAll[1],"MB data, V0M 0.1-30%","P");
		leg->AddEntry(hSPDMultAll[2],"MB data, V0M 30-100%","P");
		leg->AddEntry(hSPDMultMCAll,"MC","L");
		leg->Draw();

		//hSPDMultMCWTAll[1]->Draw("p same");
		//hSPDMultMCWTAll[2]->Draw("p same");
		c5->SaveAs("plots/DrawMult_c5.png");
	}




	return;

	TFile *outfile = new TFile("outfile_MCWeight.root","recreate");
	hRatio[1]->Write("hWeight_cent1");
	hRatio[2]->Write("hWeight_cent2");
	outfile->Close();


}
