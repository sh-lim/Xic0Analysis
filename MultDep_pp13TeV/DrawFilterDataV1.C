void DrawFilterDataV1(){

	TFile *infile = new TFile("outfile_FilterDataV1.root","read");

	const int nset = 2;
	const int nchg = 3;

	TH2D *h2d[nset][nchg];

	TH1D *h1d_Ximass[nset][nchg][7];

	TCanvas *c1[nset];

	for (int iset=0; iset<nset; iset++){
		for (int ichg=0; ichg<nchg; ichg++){

			h2d[iset][ichg] = (TH2D*)infile->Get(Form("h2dReco_pt_Ximass_set%d_chg%d",iset,ichg));

			for (int ipt=0; ipt<7; ipt++){
				h1d_Ximass[iset][ichg][ipt] = (TH1D*)h2d[iset][ichg]->ProjectionY(Form("h1d_Ximass_%d_%d_%d",iset,ichg,ipt),ipt+1,ipt+1);
			}

		}

		for (int ipt=0; ipt<7; ipt++){

			h1d_Ximass[iset][0][ipt]->Sumw2();
			h1d_Ximass[iset][1][ipt]->Sumw2();
			h1d_Ximass[iset][2][ipt]->Sumw2();

			h1d_Ximass[iset][0][ipt]->Add(h1d_Ximass[iset][1][ipt],-1);
			h1d_Ximass[iset][0][ipt]->Add(h1d_Ximass[iset][2][ipt],-1);

		}//


		c1[iset] = new TCanvas(Form("c1_set%d",iset),Form("c1_set%d",iset),1.1*4*300,2*300);
		c1[iset]->Divide(4,2);

		for (int ipt=0; ipt<7; ipt++){
			c1[iset]->cd(ipt+1);

			float max = h1d_Ximass[iset][0][ipt]->GetMaximum();

			float xmin = h1d_Ximass[iset][0][ipt]->GetBinLowEdge(1);
			float xmax = h1d_Ximass[iset][0][ipt]->GetNbinsX()*h1d_Ximass[iset][0][ipt]->GetBinWidth(1) + xmin;

			TH1D *htmp = (TH1D*)gPad->DrawFrame(xmin, 0, xmax, 1.15*max); 

			h1d_Ximass[iset][0][ipt]->SetMarkerStyle(24);
			h1d_Ximass[iset][0][ipt]->SetMarkerColor(1);
			h1d_Ximass[iset][0][ipt]->SetLineColor(1);
			h1d_Ximass[iset][0][ipt]->Draw("p same");

		}//

	}//iset


}
