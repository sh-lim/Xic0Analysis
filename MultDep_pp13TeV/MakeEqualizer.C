void MakeEqualizer(){

	const int nset = 5;

	string setname[nset] = {
		"LHC18d", "LHC18e", "LHC18f", "LHC18g", "LHC18h"};

	TFile *infile[nset];

	float V0MCentrality, SPDValue;
	float VertexZ;

	TH2D *h2_V0MCent_SPDTrk = new TH2D("h2_V0MCent_SPDTrk","",100,0,100,150,0,150);

	TProfile *hprof_vtxZ_SPDTrk[nset];

	for (int iset=0; iset<nset; iset++){

		infile[iset] = new TFile(Form("EventAnalysisResults_XiSHLEventA_%s.root",setname[iset].c_str()));

		hprof_vtxZ_SPDTrk[iset] = new TProfile(Form("hprof_vtxZ_SPDTrk_%s",setname[iset].c_str()),"",150,-15,15);

		TTree *T = (TTree*)infile[iset]->Get("EventTree");
		T->SetBranchAddress("fV0MCentrality",&V0MCentrality);
		T->SetBranchAddress("fPSDValue",&SPDValue);
		T->SetBranchAddress("fVertexZ",&VertexZ);

		Long64_t nentries = T->GetEntries();

		for (Long64_t ien=0; ien<nentries; ien++){

			T->GetEntry(ien);

			h2_V0MCent_SPDTrk->Fill(V0MCentrality, SPDValue);

			hprof_vtxZ_SPDTrk[iset]->Fill(VertexZ, SPDValue);

		}//ien


	}//iset

	TFile *outfile = new TFile("outfile_equalizer.root","recreate");
	h2_V0MCent_SPDTrk->Write();

	for (int iset=0; iset<nset; iset++){
		hprof_vtxZ_SPDTrk[iset]->Write();
	}

	outfile->Close();

}
