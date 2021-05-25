void DrawEfficiencyV4(){

	gStyle->SetOptStat(0);

	TFile *infile = new TFile("outfile_efficiencyV4.root","read");

	const int ncut = 13;
	string cut_name[ncut] = {
		"OPAngle",
		"XiCosPtAngle",
		"V0CosPtAngleXi",
		"V0DecayL",
		"CascDecayL",
		"DCABachToPV",
		"DCAPosToPV",
		"DCANegToPV",
		"DCAV0ToPV",
		"ProtonTPCRatio",
		"PionTPCRatio",
		"BachPionTPCRatio",
		"ElecTPCPIDClus"
	};

	TH3D *hCut_Sig[ncut];
	TH3D *hCut_Bkg[ncut];

	TH1D *h1Cut_Sig[ncut][2][2]; //[nmult][npt]

	for (int icut=0; icut<ncut; icut++){

		hCut_Sig[icut] = (TH3D*)infile->Get(Form("hCut_%s_Sig",cut_name[icut].c_str()));
		hCut_Bkg[icut] = (TH3D*)infile->Get(Form("hCut_%s_Bkg",cut_name[icut].c_str()));

		for (int im=0; im<2; im++){
			for (int ipt=0; ipt<2; ipt++){

				if ( im==0 && ipt==0 ){
					h1Cut_Sig[icut][im][ipt] = (TH1D*)hCut_Sig[icut]->ProjectionZ(Form("h1Cut_Sig_cut%d_%d_%d",icut,im,ipt),1,1,2,3);
				}else if ( im==1 && ipt==0 ){
					h1Cut_Sig[icut][im][ipt] = (TH1D*)hCut_Sig[icut]->ProjectionZ(Form("h1Cut_Sig_cut%d_%d_%d",icut,im,ipt),3,4,2,3);
				}else if ( im==0 && ipt==1 ){
					h1Cut_Sig[icut][im][ipt] = (TH1D*)hCut_Sig[icut]->ProjectionZ(Form("h1Cut_Sig_cut%d_%d_%d",icut,im,ipt),1,1,7,8);
				}else if ( im==1 && ipt==1 ){
					h1Cut_Sig[icut][im][ipt] = (TH1D*)hCut_Sig[icut]->ProjectionZ(Form("h1Cut_Sig_cut%d_%d_%d",icut,im,ipt),3,4,7,8);
				}

				h1Cut_Sig[icut][im][ipt]->Rebin(2);
				h1Cut_Sig[icut][im][ipt]->Scale(1./h1Cut_Sig[icut][im][ipt]->Integral());

				if ( im==0 ){
					h1Cut_Sig[icut][im][ipt]->SetMarkerStyle(24);
					h1Cut_Sig[icut][im][ipt]->SetMarkerSize(0.6);
					h1Cut_Sig[icut][im][ipt]->SetLineColor(1);
					h1Cut_Sig[icut][im][ipt]->SetMarkerColor(1);
				}else{
					h1Cut_Sig[icut][im][ipt]->SetLineWidth(1);
					h1Cut_Sig[icut][im][ipt]->SetLineColor(2+2*ipt);
					h1Cut_Sig[icut][im][ipt]->SetMarkerColor(2+2*ipt);
				}


			}//ip
		}//im

	}//icut

	TCanvas *c1 = new TCanvas("c1","c1",1.1*5*300,3*300);
	c1->Divide(5,3);

	for (int ii=0; ii<ncut; ii++){

		c1->cd(ii+1);
		gPad->SetLogy();
		gPad->SetMargin(0.14,0.03,0.12,0.03);
		TH1D *htmp = h1Cut_Sig[ii][0][1]; 

		float max = TMath::Max(h1Cut_Sig[ii][0][1]->GetMaximum(), h1Cut_Sig[ii][0][0]->GetMaximum());

		htmp->SetTitle("");
		htmp->SetMaximum(2.0*max);
		htmp->GetXaxis()->SetTitleSize(0.05);
		htmp->GetYaxis()->SetTitleSize(0.05);
		htmp->GetXaxis()->SetLabelSize(0.04);
		htmp->GetYaxis()->SetLabelSize(0.04);

		htmp->GetXaxis()->SetTitle(cut_name[ii].c_str());
		htmp->Draw();
		h1Cut_Sig[ii][1][1]->Draw("p same");

		h1Cut_Sig[ii][0][0]->Draw("p same");
		h1Cut_Sig[ii][1][0]->Draw("p same");


	}//ii

	return;

	{
		c1->cd(1);
		gPad->SetLogy();
		gPad->SetMargin(0.14,0.03,0.12,0.03);
		TH1D *htmp = h1Cut_Sig[0][0][1]; 

		htmp->SetTitle("");
		htmp->SetMaximum(2.0*htmp->GetMaximum());
		htmp->Draw();
		h1Cut_Sig[0][1][1]->Draw("p same");

		h1Cut_Sig[0][0][0]->Draw("p same");
		h1Cut_Sig[0][1][0]->Draw("p same");
	}

	{
		c1->cd(2);
		gPad->SetLogy();
		gPad->SetMargin(0.14,0.03,0.12,0.03);
		TH1D *htmp = h1Cut_Sig[1][0][1]; 

		htmp->SetTitle("");
		htmp->SetMaximum(2.0*htmp->GetMaximum());
		htmp->Draw();
		h1Cut_Sig[1][1][1]->Draw("p same");

		h1Cut_Sig[1][0][0]->Draw("p same");
		h1Cut_Sig[1][1][0]->Draw("p same");
	}

	{
		c1->cd(3);
		gPad->SetLogy();
		gPad->SetMargin(0.14,0.03,0.12,0.03);
		TH1D *htmp = h1Cut_Sig[2][0][1]; 

		htmp->SetTitle("");
		htmp->SetMaximum(2.0*htmp->GetMaximum());
		htmp->Draw();
		h1Cut_Sig[2][1][1]->Draw("p same");

		h1Cut_Sig[2][0][0]->Draw("p same");
		h1Cut_Sig[2][1][0]->Draw("p same");
	}

}
