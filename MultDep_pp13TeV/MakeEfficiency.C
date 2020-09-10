void MakeEfficiency(){

	const int nset = 3;
	const char *setname[nset] = {"LHC16MC", "LHC17MC", "LHC18MC"};
	const int nColor[nset] = {1, 2, 4};
	//const char *setname[1] = {"LHC16MC"};
	//const int nColor[1] = {1};

	const int npt = 7;
	const float ptbin[npt+1] = {1, 2, 3, 4, 5, 6, 8, 12};

	const int ncent = 2;
	const float centbin[ncent+1] = {0, 40, 100};

	TFile *infile[nset];

	TH2D *h2dGen[nset];
	TH2D *h2dGenSPDV[nset];

	TH2D *h2dReco[nset];
	TH2D *h2dRecoSPDV[nset];

	TH1D *h1dGen_pt[nset];
	TH1D *h1dGen_ce[nset];
	TH1D *h1dGen_spdce[nset];

	TH1D *h1dReco_pt[nset];
	TH1D *h1dReco_ce[nset];
	TH1D *h1dReco_spdce[nset];

	TH1D *h1dEff_pt[nset];
	TH1D *h1dEff_ce[nset];
	TH1D *h1dEff_spdce[nset];

	float pTe; float echarge;
	float pTv; float vcharge;
	float Massv; float cosoa; float In_Mass; float Pt;
	float nSigmaTOF; float nSigmaTPC; float TPCCluster; float ITSCluster; float TPCPIDCluster;
	float CascDecayLength; float V0DecayLength; float DCABachToPrimVertex;
	float V0CosineOfPoiningAngleXi; float DCAV0ToPrimVertex; float DCAPosToPrimVertex; float DCANegToPrimVertex;
	float e_minmass; float e_minmass_ss; float phi; float erap; float Xirap;
	float pionTPCCluster; float protonTPCCluster; float b_pionTPCCluster;
	float e_crossedratio; float e_findable; float pion_crossedratio; float pion_findable;
	float proton_crossedratio; float proton_findable; float bpion_crossedratio; float bpion_findable;
	float XiCosineOfPoiningAngle; float pTpion; float pTproton; float pTbach;
	float MassLambda; float MassAntiLambda;

	float mcpTe; float mcecharge;
	float mcpTv; float mcvcharge;
	float mcpteXi; float mcptXic0; float mcc_flag; float mcb_flag; float mcXib; float XibeXi; float mcXibMass;

	float V0MCentrality, V0MValue;
	float SPDCentrality, SPDValue;

	for (int iset=0; iset<nset; iset++){
		//infile[iset] = new TFile(Form("AnalysisResults_XiSHLNew2A_%s.root",setname[iset]));
		infile[iset] = new TFile(Form("merged_AnalysisResults_XiSHLNew2B_%s.root",setname[iset]));

		TTree *T0 = (TTree*)infile[iset]->Get("eXiTree");
		TTree *T1 = (TTree*)infile[iset]->Get("MCTree");
		TTree *T2 = (TTree*)infile[iset]->Get("EventTree");

		T0->SetBranchAddress("pTe",&pTe);
		T0->SetBranchAddress("echarge",&echarge);
		T0->SetBranchAddress("TOFnSigma",&nSigmaTOF);
		T0->SetBranchAddress("TPCnSigma",&nSigmaTPC);
		T0->SetBranchAddress("TPCPID",&TPCPIDCluster);
		T0->SetBranchAddress("ITS",&ITSCluster);
		T0->SetBranchAddress("e_crossedrows",&e_crossedratio);
		T0->SetBranchAddress("e_findable",&e_findable);
		T0->SetBranchAddress("phi",&phi);
		T0->SetBranchAddress("erap",&erap);
		T0->SetBranchAddress("e_minmass",&e_minmass);
		T0->SetBranchAddress("e_minmass_ss",&e_minmass_ss);
		T0->SetBranchAddress("pTv",&pTv);
		T0->SetBranchAddress("vcharge",&vcharge);
		T0->SetBranchAddress("Massv",&Massv);
		T0->SetBranchAddress("MassLambda",&MassLambda);
		T0->SetBranchAddress("MassAntiLambda",&MassAntiLambda);  //mod
		T0->SetBranchAddress("Xirap",&Xirap);  //mod
		T0->SetBranchAddress("V0DecayLength",&V0DecayLength);
		T0->SetBranchAddress("CascDecayLength",&CascDecayLength);
		T0->SetBranchAddress("DCABachToPrimVertex",&DCABachToPrimVertex);
		T0->SetBranchAddress("DCAV0NegToPrimVertex",&DCANegToPrimVertex);
		T0->SetBranchAddress("DCAV0PosToPrimVertex",&DCAPosToPrimVertex);
		T0->SetBranchAddress("V0CosineOfPoiningAngleXi",&V0CosineOfPoiningAngleXi);
		T0->SetBranchAddress("XiCosineOfPoiningAngle",&XiCosineOfPoiningAngle);  //modify
		T0->SetBranchAddress("DCAV0ToPrimVertex",&DCAV0ToPrimVertex);   ///new
		T0->SetBranchAddress("cosoa",&cosoa);  //mod
		T0->SetBranchAddress("pion_crossedrows",&pion_crossedratio);
		T0->SetBranchAddress("pion_findable",&pion_findable);
		T0->SetBranchAddress("proton_crossedrows",&proton_crossedratio);
		T0->SetBranchAddress("proton_findable",&proton_findable);
		T0->SetBranchAddress("bpion_crossedratio",&bpion_crossedratio);
		T0->SetBranchAddress("bpion_findable",&bpion_findable);
		T0->SetBranchAddress("pTpion",&pTpion);
		T0->SetBranchAddress("pTproton",&pTproton);
		T0->SetBranchAddress("pTbach",&pTbach);
		T0->SetBranchAddress("In_Mass",&In_Mass);
		T0->SetBranchAddress("eXiPt",&Pt);

		T1->SetBranchAddress("mcpTe",&mcpTe);
		T1->SetBranchAddress("mcecharge",&mcecharge);
		T1->SetBranchAddress("mcpTv",&mcpTv);
		T1->SetBranchAddress("mcvcharge",&mcvcharge);
		T1->SetBranchAddress("mcpTeXi",&mcpteXi);
		T1->SetBranchAddress("mcpTXic0",&mcptXic0);
		T1->SetBranchAddress("c_flag",&mcc_flag);
		T1->SetBranchAddress("b_flag",&mcb_flag);
		T1->SetBranchAddress("mcpTXib",&mcXib);
		T1->SetBranchAddress("mceXipTb",&XibeXi);
		T1->SetBranchAddress("mcXibMass",&mcXibMass);

		T2->SetBranchAddress("fV0MCentrality",&V0MCentrality);
		T2->SetBranchAddress("fSPDCentrality",&SPDCentrality);

		T2->SetBranchAddress("fV0MValue",&V0MValue);
		T2->SetBranchAddress("fPSDValue",&SPDValue);

		h2dGen[iset] = (TH2D*)infile[iset]->Get("histogram")->FindObject("hTrueXic0");
		h2dReco[iset] = (TH2D*)h2dGen[iset]->Clone(Form("h2dReco_set%d",iset));
		h2dReco[iset]->Reset();

		h2dGenSPDV[iset] = (TH2D*)infile[iset]->Get("histogram")->FindObject("hTrueXic0SPD");
		h2dRecoSPDV[iset] = (TH2D*)h2dGenSPDV[iset]->Clone(Form("h2dRecoSPDV_set%d",iset));
		h2dRecoSPDV[iset]->Reset();

		cout << iset << ", # of Generated Xic0: " << h2dGen[iset]->GetEntries() << endl;

		h1dGen_ce[iset] = (TH1D*)h2dGen[iset]->ProjectionY(Form("h1dGen_ce%d",iset),1,npt);
		h1dGen_ce[iset]->SetMarkerStyle(1);
		h1dGen_ce[iset]->SetMarkerColor(nColor[iset]);
		h1dGen_ce[iset]->SetLineColor(nColor[iset]);
		h1dGen_ce[iset]->SetLineWidth(2);

		h1dGen_pt[iset] = (TH1D*)h2dGen[iset]->ProjectionX(Form("h1dGen_pt%d",iset),1,100);
		h1dGen_pt[iset]->SetMarkerStyle(1);
		h1dGen_pt[iset]->SetMarkerColor(nColor[iset]);
		h1dGen_pt[iset]->SetLineColor(nColor[iset]);
		h1dGen_pt[iset]->SetLineWidth(2);

		h1dGen_spdce[iset] = (TH1D*)h2dGenSPDV[iset]->ProjectionY(Form("h1dGenSPDV_ce%d",iset),1,npt);
		h1dGen_spdce[iset]->SetMarkerStyle(1);
		h1dGen_spdce[iset]->SetMarkerColor(nColor[iset]);
		h1dGen_spdce[iset]->SetLineColor(nColor[iset]);
		h1dGen_spdce[iset]->SetLineWidth(2);

		int nentries0 = T0->GetEntries();
		int nentries1 = T1->GetEntries();
		int nentries2 = T2->GetEntries();

		if ( nentries0!=nentries1 || nentries0!=nentries2 ){
			cout << "inconsistent entries " << nentries0 << " " << nentries1 << " " << nentries2 << endl;
		}

		for (int ien=0; ien<nentries0; ien++){
			T0->GetEntry(ien);
			T1->GetEntry(ien);
			T2->GetEntry(ien);

			if ( fabs(Massv-1.32171)>0.008 ) continue;  //Xi mass tolerance
			if ( In_Mass<1.3 ) continue;  //pair low limit
			if ( fabs(pTe)>900 ) continue;  //tmp tree reject
			if ( mcptXic0<0 ) continue;

			float VT_e_nsigma_cut	= -3.5 + (1.15*pTe) - (0.090*pTe*pTe);
			float T_e_nsigma_cut	= -3.7 + (1.17*pTe) - (0.094*pTe*pTe); ///need to modify
			float S_e_nsigma_cut	= -3.9 + (1.17*pTe) - (0.094*pTe*pTe);
			float L_e_nsigma_cut	= -4.1 + (1.17*pTe) - (0.094*pTe*pTe); ///need to modify
			float VL_e_nsigma_cut	= -4.3 + (1.17*pTe) - (0.094*pTe*pTe);

			if ( pTe>=5.0 ){
				T_e_nsigma_cut	= -3.7+(1.17*5)-(0.094*25);
				VT_e_nsigma_cut	= -3.5+(1.15*5)-(0.090*25);
				S_e_nsigma_cut	= -3.9+(1.17*5)-(0.094*25);
				VL_e_nsigma_cut	= -4.3+(1.17*5)-(0.094*25);
				L_e_nsigma_cut	= -4.1+(1.17*5)-(0.094*25);
			}    

			Bool_t Xi_Topology_VLoose_flag = kFALSE; if(V0DecayLength>0.02 && CascDecayLength>0.02 && DCABachToPrimVertex>0.01
					&& DCANegToPrimVertex>0.05 && DCAPosToPrimVertex>0.05 && V0CosineOfPoiningAngleXi>0.98 && XiCosineOfPoiningAngle>0.98 &&DCAV0ToPrimVertex>0.01) Xi_Topology_VLoose_flag = kTRUE;
			Bool_t Xi_Topology_Loose_flag = kFALSE; if(V0DecayLength>1.55 && CascDecayLength>0.29 && DCABachToPrimVertex>0.0146
					&& DCANegToPrimVertex>0.061 && DCAPosToPrimVertex>0.061 && V0CosineOfPoiningAngleXi>0.981 && XiCosineOfPoiningAngle>0.981 &&DCAV0ToPrimVertex>0.02) Xi_Topology_Loose_flag = kTRUE;
			Bool_t Xi_Topology_Stand_flag = kFALSE; if(V0DecayLength>2.67 && CascDecayLength>0.38 && DCABachToPrimVertex>0.0204
					&& DCANegToPrimVertex>0.073 && DCAPosToPrimVertex>0.073 && V0CosineOfPoiningAngleXi>0.983 && XiCosineOfPoiningAngle>0.983 &&DCAV0ToPrimVertex>0.03) Xi_Topology_Stand_flag = kTRUE;
			Bool_t Xi_Topology_Tight_flag = kFALSE; if(V0DecayLength>3.6 && CascDecayLength>0.53 && DCABachToPrimVertex>0.037
					&& DCANegToPrimVertex>0.088 && DCAPosToPrimVertex>0.088 && V0CosineOfPoiningAngleXi>0.9839 && XiCosineOfPoiningAngle>0.9839 &&DCAV0ToPrimVertex>0.04) Xi_Topology_Tight_flag = kTRUE;
			Bool_t Xi_Topology_VTight_flag = kFALSE; if(V0DecayLength>4.39 && CascDecayLength>0.72 && DCABachToPrimVertex>0.037
					&& DCANegToPrimVertex>0.102 && DCAPosToPrimVertex>0.102 && V0CosineOfPoiningAngleXi>0.985 && XiCosineOfPoiningAngle>0.985 &&DCAV0ToPrimVertex>0.06) Xi_Topology_VTight_flag = kTRUE;

			Bool_t Xi_Topology_Stand_V0 = kFALSE; if(V0DecayLength>0.02 && CascDecayLength>0.38 && DCABachToPrimVertex>0.0204
					&& DCANegToPrimVertex>0.073 && DCAPosToPrimVertex>0.073 && V0CosineOfPoiningAngleXi>0.983 && XiCosineOfPoiningAngle>0.983 &&DCAV0ToPrimVertex>0.03) Xi_Topology_Stand_V0 = kTRUE;
			Bool_t Xi_Topology_Stand_Xi = kFALSE; if(V0DecayLength>2.67 && CascDecayLength>0.02 && DCABachToPrimVertex>0.0204
					&& DCANegToPrimVertex>0.073 && DCAPosToPrimVertex>0.073 && V0CosineOfPoiningAngleXi>0.983 && XiCosineOfPoiningAngle>0.983 &&DCAV0ToPrimVertex>0.03) Xi_Topology_Stand_Xi = kTRUE;
			Bool_t Xi_Topology_Stand_DCAb = kFALSE; if(V0DecayLength>2.67 && CascDecayLength>0.38 && DCABachToPrimVertex>0.01
					&& DCANegToPrimVertex>0.073 && DCAPosToPrimVertex>0.073 && V0CosineOfPoiningAngleXi>0.983 && XiCosineOfPoiningAngle>0.983 &&DCAV0ToPrimVertex>0.03) Xi_Topology_Stand_DCAb = kTRUE;

			Bool_t Xi_Recon_VTight_flag = kFALSE;
			Bool_t Xi_Recon_Tight_flag = kFALSE;
			Bool_t Xi_Recon_Stand_flag = kFALSE;
			Bool_t Xi_Recon_Loose_flag = kFALSE;
			Bool_t Xi_Recon_VLoose_flag = kFALSE;
			if(pion_crossedratio/pion_findable>0.81 && proton_crossedratio/proton_findable>0.81 && bpion_crossedratio/bpion_findable>0.81 && pion_crossedratio>80 && proton_crossedratio>80 && bpion_crossedratio>80) Xi_Recon_VTight_flag = kTRUE;
			if(pion_crossedratio/pion_findable>0.79 && proton_crossedratio/proton_findable>0.79 && bpion_crossedratio/bpion_findable>0.79 && pion_crossedratio>75 && proton_crossedratio>75 && bpion_crossedratio>75) Xi_Recon_Tight_flag = kTRUE;
			if(pion_crossedratio/pion_findable>0.77 && proton_crossedratio/proton_findable>0.77 && bpion_crossedratio/bpion_findable>0.77 && pion_crossedratio>70 && proton_crossedratio>70 && bpion_crossedratio>70) Xi_Recon_Stand_flag = kTRUE;
			if(pion_crossedratio/pion_findable>0.75 && proton_crossedratio/proton_findable>0.75 && bpion_crossedratio/bpion_findable>0.75 && pion_crossedratio>65 && proton_crossedratio>65 && bpion_crossedratio>65) Xi_Recon_Loose_flag = kTRUE;
			if(pion_crossedratio/pion_findable>0.70 && proton_crossedratio/proton_findable>0.70 && bpion_crossedratio/bpion_findable>0.70 && pion_crossedratio>65 && proton_crossedratio>65 && bpion_crossedratio>65) Xi_Recon_VLoose_flag = kTRUE;

			Bool_t e_Recon_VTight_flag = kFALSE;  if(e_crossedratio>85 && TPCPIDCluster>60 && e_crossedratio/e_findable>0.9 && ITSCluster>=3) e_Recon_VTight_flag = kTRUE;
			Bool_t e_Recon_Tight_flag = kFALSE;  if(e_crossedratio>75 && TPCPIDCluster>55 && e_crossedratio/e_findable>0.85 && ITSCluster>=3) e_Recon_Tight_flag = kTRUE;
			Bool_t e_Recon_Stand_flag = kFALSE; if(e_crossedratio>70 && TPCPIDCluster>50 && e_crossedratio/e_findable>0.8 && ITSCluster>=3) e_Recon_Stand_flag = kTRUE;
			Bool_t e_Recon_Loose_flag = kFALSE;  if(e_crossedratio>65 && TPCPIDCluster>45 && e_crossedratio/e_findable>0.8 && ITSCluster>=3) e_Recon_Loose_flag = kTRUE;
			Bool_t e_Recon_VLoose_flag = kFALSE;  if(e_crossedratio>65 && TPCPIDCluster>40 && e_crossedratio/e_findable>0.75 && ITSCluster>=3) e_Recon_VLoose_flag = kTRUE;

			Bool_t e_PID_VTight_flag = kFALSE; if(fabs(nSigmaTOF)<=2 && nSigmaTPC>=VT_e_nsigma_cut && nSigmaTPC<=3) e_PID_VTight_flag = kTRUE;
			Bool_t e_PID_Tight_flag = kFALSE; if(fabs(nSigmaTOF)<=3 && nSigmaTPC>=T_e_nsigma_cut && nSigmaTPC<=3) e_PID_Tight_flag = kTRUE;
			Bool_t e_PID_Stand_flag = kFALSE; if(fabs(nSigmaTOF)<=3 && nSigmaTPC>=S_e_nsigma_cut && nSigmaTPC<=3) e_PID_Stand_flag = kTRUE;
			Bool_t e_PID_Loose_flag = kFALSE; if(fabs(nSigmaTOF)<=3 && nSigmaTPC>=L_e_nsigma_cut && nSigmaTPC<=3) e_PID_Loose_flag = kTRUE;
			Bool_t e_PID_VLoose_flag = kFALSE; if(fabs(nSigmaTOF)<=3 && nSigmaTPC>=VL_e_nsigma_cut && nSigmaTPC<=3) e_PID_VLoose_flag = kTRUE;

			Bool_t OPAngle_Tight_flag = kFALSE; if(cosoa>cos(70*(3.141592/180))) OPAngle_Tight_flag = kTRUE;
			Bool_t OPAngle_Stand_flag = kFALSE; if(cosoa>cos(90*(3.141592/180))) OPAngle_Stand_flag = kTRUE;
			Bool_t OPAngle_Loose_flag = kFALSE; if(cosoa>cos(110*(3.141592/180)))OPAngle_Loose_flag = kTRUE;

			Bool_t PairMass_Tight_flag = kFALSE; if(In_Mass<2.3) PairMass_Tight_flag = kTRUE;
			Bool_t PairMass_Stand_flag = kFALSE; if(In_Mass<2.5) PairMass_Stand_flag = kTRUE;
			Bool_t PairMass_Loose_flag = kFALSE; if(In_Mass<2.7) PairMass_Loose_flag = kTRUE;

			if ( 
					e_Recon_Stand_flag 
					&& Xi_Recon_Stand_flag 
					&& e_PID_Stand_flag 
					&& Xi_Topology_Stand_flag
					&& OPAngle_Stand_flag 
					&& PairMass_Stand_flag
				 ){

				h2dReco[iset]->Fill(mcptXic0, V0MCentrality);
				h2dRecoSPDV[iset]->Fill(mcptXic0, SPDValue);

			}

		}//ien

		h1dReco_ce[iset] = (TH1D*)h2dReco[iset]->ProjectionY(Form("h1dReco_ce%d",iset),1,npt);
		h1dReco_ce[iset]->SetMarkerStyle(24);
		h1dReco_ce[iset]->SetMarkerColor(nColor[iset]);
		h1dReco_ce[iset]->SetLineColor(nColor[iset]);
		h1dReco_ce[iset]->SetLineWidth(2);

		h1dReco_spdce[iset] = (TH1D*)h2dRecoSPDV[iset]->ProjectionY(Form("h1dReco_spdce%d",iset),1,npt);
		h1dReco_spdce[iset]->SetMarkerStyle(24);
		h1dReco_spdce[iset]->SetMarkerColor(nColor[iset]);
		h1dReco_spdce[iset]->SetLineColor(nColor[iset]);
		h1dReco_spdce[iset]->SetLineWidth(2);

		h1dReco_pt[iset] = (TH1D*)h2dReco[iset]->ProjectionX(Form("h1dReco_pt%d",iset),1,100);
		h1dReco_pt[iset]->SetMarkerStyle(24);
		h1dReco_pt[iset]->SetMarkerColor(nColor[iset]);
		h1dReco_pt[iset]->SetLineColor(nColor[iset]);
		h1dReco_pt[iset]->SetLineWidth(2);

		h1dGen_ce[iset]->Rebin(10);
		h1dReco_ce[iset]->Rebin(10);

		h1dGen_spdce[iset]->Rebin(10);
		h1dReco_spdce[iset]->Rebin(10);

		h1dEff_pt[iset] = (TH1D*)h1dReco_pt[iset]->Clone(Form("h1dEff_pt_set%d",iset));
		h1dEff_ce[iset] = (TH1D*)h1dReco_ce[iset]->Clone(Form("h1dEff_ce_set%d",iset));
		h1dEff_spdce[iset] = (TH1D*)h1dReco_spdce[iset]->Clone(Form("h1dEff_spdce_set%d",iset));

		h1dEff_pt[iset]->Divide(h1dGen_pt[iset]);
		h1dEff_ce[iset]->Divide(h1dGen_ce[iset]);
		h1dEff_spdce[iset]->Divide(h1dGen_spdce[iset]);

	}//ien

	TFile *outfile = new TFile("outfile_efficiency.root","recreate");
	for (int iset=0; iset<nset; iset++){

		h1dGen_spdce[iset]->Write(Form("h1dGen_SPDV_%s",setname[iset]));
		h1dReco_spdce[iset]->Write(Form("h1dReco_SPDV_%s",setname[iset]));
		h1dEff_spdce[iset]->Write(Form("h1dEff_SPDV_%s",setname[iset]));

	}

	/*
	TCanvas *c1 = new TCanvas("c1","c1",1.1*3*300,2*300);
	c1->Divide(3,2);

	TCanvas *c2 = new TCanvas("c2","c2",1.1*3*300,2*300);
	c2->Divide(3,2);

	TCanvas *c3 = new TCanvas("c3","c3",1.1*3*300,2*300);
	c3->Divide(3,2);

	{
		for (int iset=0; iset<nset; iset++){

			c1->cd(iset+1);
			gPad->SetMargin(0.15,0.05,0.15,0.03);

			float max = h1dGen_ce[iset]->GetMaximum();

			TH1D *htmp = (TH1D*)gPad->DrawFrame(0,0,100,1.2*max);

			h1dGen_ce[iset]->Draw("p same");
			h1dReco_ce[iset]->Draw("p same");

			c1->cd(iset+4);
			gPad->SetMargin(0.15,0.05,0.15,0.03);

			htmp = (TH1D*)gPad->DrawFrame(0,0,100,0.1);

			h1dEff_ce[iset]->Draw("same");

		}//iset

		for (int iset=0; iset<nset; iset++){

			c2->cd(iset+1);
			gPad->SetMargin(0.15,0.05,0.15,0.03);

			float max = h1dGen_pt[iset]->GetMaximum();

			TH1D *htmp = (TH1D*)gPad->DrawFrame(1,0,12,1.2*max);

			h1dGen_pt[iset]->Draw("p same");
			h1dReco_pt[iset]->Draw("p same");

			c2->cd(iset+4);
			gPad->SetMargin(0.15,0.05,0.15,0.03);

			htmp = (TH1D*)gPad->DrawFrame(1,0,12,0.15);

			h1dEff_pt[iset]->Draw("same");

		}//iset

		for (int iset=0; iset<nset; iset++){

			c3->cd(iset+1);
			gPad->SetMargin(0.15,0.05,0.15,0.03);

			float max = h1dGen_spdce[iset]->GetMaximum();

			TH1D *htmp = (TH1D*)gPad->DrawFrame(1,0,100,1.2*max);

			h1dGen_spdce[iset]->Draw("p same");
			h1dReco_spdce[iset]->Draw("p same");

			c3->cd(iset+4);
			gPad->SetMargin(0.15,0.05,0.15,0.03);

			htmp = (TH1D*)gPad->DrawFrame(1,0,100,0.1);

			h1dEff_spdce[iset]->Draw("same");

		}//iset
	}
*/


}
