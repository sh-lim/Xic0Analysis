#include <iostream>
#include <fstream>

#include <TH3F.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TFile.h>

using namespace std;

void MakeXiEfficiencyV3(const char *ver="pythia6"){

	//const int nset = 3;
	//const string setname[nset] = {"LHC16MC","LHC17MC","LHC18MC"};
	//const string setname[nset] = {"LHC17MC"};
	const int nColor[3] = {1, 2, 4};
	//const char *setname[1] = {"LHC16MC"};
	//const int nColor[1] = {1};

	const int npt = 7;
	const double ptbin[npt+1] = {1, 2, 3, 4, 5, 6, 8, 12};

	const int nrap = 6;
	const double rapbin[nrap+1] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6};

	const int nrap2 = 10;
	const double rapbin2[nrap2+1] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};

	//const int ncent = 2;
	//const float centbin[ncent+1] = {0, 40, 100};

	bool bFIRST = true;

	double spdbin[201];
	for (int ii=0; ii<201; ii++) spdbin[ii] = ii;

	TH3F *h3TrueXic0SPD = new TH3F("hTrueXic0SPD","",npt,ptbin,nrap2,rapbin2,200,spdbin);

	TH2F *hTrueXic0CharmSPD = new TH2F("hTrueXic0CharmSPD","",npt,ptbin,200,spdbin);
	TH2F *hTrueXic0BottomSPD = new TH2F("hTrueXic0BottomSPD","",npt,ptbin,200,spdbin);

	TH2F *hTrueEeSPD0 = new TH2F("hTrueEeSPD0","",npt,ptbin,200,spdbin);
	TH2F *hTrueEeSPD1 = new TH2F("hTrueEeSPD1","",npt,ptbin,200,spdbin);
	TH2F *hTrueEeSPD2 = new TH2F("hTrueEeSPD2","",npt,ptbin,200,spdbin);
	TH2F *hTrueEeSPD3 = new TH2F("hTrueEeSPD3","",npt,ptbin,200,spdbin);

	TH2F *hTrueEeCharmSPD0 = new TH2F("hTrueEeCharmSPD0","",npt,ptbin,200,spdbin);
	TH2F *hTrueEeCharmSPD1 = new TH2F("hTrueEeCharmSPD1","",npt,ptbin,200,spdbin);
	TH2F *hTrueEeCharmSPD2 = new TH2F("hTrueEeCharmSPD2","",npt,ptbin,200,spdbin);
	TH2F *hTrueEeCharmSPD3 = new TH2F("hTrueEeCharmSPD3","",npt,ptbin,200,spdbin);

	TH2F *hTrueEeBottomSPD0 = new TH2F("hTrueEeBottomSPD0","",npt,ptbin,200,spdbin);
	TH2F *hTrueEeBottomSPD1 = new TH2F("hTrueEeBottomSPD1","",npt,ptbin,200,spdbin);
	TH2F *hTrueEeBottomSPD2 = new TH2F("hTrueEeBottomSPD2","",npt,ptbin,200,spdbin);
	TH2F *hTrueEeBottomSPD3 = new TH2F("hTrueEeBottomSPD3","",npt,ptbin,200,spdbin);

	/*
	TH2F *hTrueXiSPD0 = new TH2F("hTrueXiSPD0","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiSPD1 = new TH2F("hTrueXiSPD1","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiSPD2 = new TH2F("hTrueXiSPD2","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiSPD3 = new TH2F("hTrueXiSPD3","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiSPD4 = new TH2F("hTrueXiSPD4","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiSPD5 = new TH2F("hTrueXiSPD5","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiSPD6 = new TH2F("hTrueXiSPD6","",npt,ptbin,200,spdbin);

	TH2F *hTrueXiCharmSPD0 = new TH2F("hTrueXiCharmSPD0","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiCharmSPD1 = new TH2F("hTrueXiCharmSPD1","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiCharmSPD2 = new TH2F("hTrueXiCharmSPD2","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiCharmSPD3 = new TH2F("hTrueXiCharmSPD3","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiCharmSPD4 = new TH2F("hTrueXiCharmSPD4","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiCharmSPD5 = new TH2F("hTrueXiCharmSPD5","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiCharmSPD6 = new TH2F("hTrueXiCharmSPD6","",npt,ptbin,200,spdbin);

	TH2F *hTrueXiBottomSPD0 = new TH2F("hTrueXiBottomSPD0","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiBottomSPD1 = new TH2F("hTrueXiBottomSPD1","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiBottomSPD2 = new TH2F("hTrueXiBottomSPD2","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiBottomSPD3 = new TH2F("hTrueXiBottomSPD3","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiBottomSPD4 = new TH2F("hTrueXiBottomSPD4","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiBottomSPD5 = new TH2F("hTrueXiBottomSPD5","",npt,ptbin,200,spdbin);
	TH2F *hTrueXiBottomSPD6 = new TH2F("hTrueXiBottomSPD6","",npt,ptbin,200,spdbin);
	*/

	vector <TString> ent10 ={"all","Filterbit_c","TrackCut_c","pT_c","eta_c","TOF_c","TPC_c","prefilter_c"};
	TH1F *e_c_flag = new TH1F("e_c_flag","",ent10.size(), 0, ent10.size());
	for(auto i=0u; i<ent10.size(); i++) e_c_flag->GetXaxis()->SetBinLabel(i+1,ent10.at(i).Data());

	vector <TString> ent11 ={"all","Filterbit_b","TrackCut_b","pT_b","eta_b","TOF_b","TPC_b","prefilter_b"};
	TH1F *e_b_flag = new TH1F("e_b_flag","",ent11.size(), 0, ent11.size());
	for(auto i=0u; i<ent11.size(); i++) e_b_flag->GetXaxis()->SetBinLabel(i+1,ent11.at(i).Data());

	char fname[300];
	sprintf(fname,"file_%s.lst",ver);
	ifstream flist;
	flist.open(fname);

	while ( flist >> fname ){

		cout << "OPEN: " << fname << endl;

		TFile *infile = new TFile(fname,"read");

		TH3F *_h3TrueXic0SPD = (TH3F*)infile->Get("histogram")->FindObject("hTrueXic0SPD");

		TH2F *_hTrueXic0CharmSPD1 = (TH2F*)infile->Get("histogram")->FindObject("hXic0PtFromCharm1SPD");
		TH2F *_hTrueXic0CharmSPD2 = (TH2F*)infile->Get("histogram")->FindObject("hXic0PtFromCharm2SPD");

		TH2F *_hTrueXic0BottomSPD1 = (TH2F*)infile->Get("histogram")->FindObject("hXic0PtFromBottom1SPD");
		TH2F *_hTrueXic0BottomSPD2 = (TH2F*)infile->Get("histogram")->FindObject("hXic0PtFromBottom2SPD");

		//
		TH2F *_hTrueEeCharmSPD0 = (TH2F*)infile->Get("histogram")->FindObject("hTrueEeCharmSPD0");
		TH2F *_hTrueEeCharmSPD1 = (TH2F*)infile->Get("histogram")->FindObject("hTrueEeCharmSPD1");
		TH2F *_hTrueEeCharmSPD2 = (TH2F*)infile->Get("histogram")->FindObject("hTrueEeCharmSPD2");
		TH2F *_hTrueEeCharmSPD3 = (TH2F*)infile->Get("histogram")->FindObject("hTrueEeCharmSPD3");

		TH2F *_hTrueEeBottomSPD0 = (TH2F*)infile->Get("histogram")->FindObject("hTrueEeBottomSPD0");
		TH2F *_hTrueEeBottomSPD1 = (TH2F*)infile->Get("histogram")->FindObject("hTrueEeBottomSPD1");
		TH2F *_hTrueEeBottomSPD2 = (TH2F*)infile->Get("histogram")->FindObject("hTrueEeBottomSPD2");
		TH2F *_hTrueEeBottomSPD3 = (TH2F*)infile->Get("histogram")->FindObject("hTrueEeBottomSPD3");

		/*
		TH2F *_hTrueXiCharmSPD0 = (TH2F*)infile->Get("histogram")->FindObject("hTrueXiCharmSPD0");
		TH2F *_hTrueXiCharmSPD1 = (TH2F*)infile->Get("histogram")->FindObject("hTrueXiCharmSPD1");
		TH2F *_hTrueXiCharmSPD2 = (TH2F*)infile->Get("histogram")->FindObject("hTrueXiCharmSPD2");
		TH2F *_hTrueXiCharmSPD3 = (TH2F*)infile->Get("histogram")->FindObject("hTrueXiCharmSPD3");
		TH2F *_hTrueXiCharmSPD4 = (TH2F*)infile->Get("histogram")->FindObject("hTrueXiCharmSPD4");
		TH2F *_hTrueXiCharmSPD5 = (TH2F*)infile->Get("histogram")->FindObject("hTrueXiCharmSPD5");
		TH2F *_hTrueXiCharmSPD6 = (TH2F*)infile->Get("histogram")->FindObject("hTrueXiCharmSPD6");

		TH2F *_hTrueXiBottomSPD0 = (TH2F*)infile->Get("histogram")->FindObject("hTrueXiBottomSPD0");
		TH2F *_hTrueXiBottomSPD1 = (TH2F*)infile->Get("histogram")->FindObject("hTrueXiBottomSPD1");
		TH2F *_hTrueXiBottomSPD2 = (TH2F*)infile->Get("histogram")->FindObject("hTrueXiBottomSPD2");
		TH2F *_hTrueXiBottomSPD3 = (TH2F*)infile->Get("histogram")->FindObject("hTrueXiBottomSPD3");
		TH2F *_hTrueXiBottomSPD4 = (TH2F*)infile->Get("histogram")->FindObject("hTrueXiBottomSPD4");
		TH2F *_hTrueXiBottomSPD5 = (TH2F*)infile->Get("histogram")->FindObject("hTrueXiBottomSPD5");
		TH2F *_hTrueXiBottomSPD6 = (TH2F*)infile->Get("histogram")->FindObject("hTrueXiBottomSPD6");
		*/

		TH1F *_e_c_flag = (TH1F*)infile->Get("histogram")->FindObject("e_c_flag");
		TH1F *_e_b_flag = (TH1F*)infile->Get("histogram")->FindObject("e_b_flag");

		if ( !_h3TrueXic0SPD ){
			cout << "SKIP" << endl;
			infile->Close();
			delete infile;
			continue;
		}

		h3TrueXic0SPD->Add(_h3TrueXic0SPD);

		hTrueXic0CharmSPD->Add(_hTrueXic0CharmSPD1);
		hTrueXic0CharmSPD->Add(_hTrueXic0CharmSPD2);

		hTrueXic0BottomSPD->Add(_hTrueXic0BottomSPD1);
		hTrueXic0BottomSPD->Add(_hTrueXic0BottomSPD2);

		hTrueEeSPD0->Add(_hTrueEeCharmSPD0);
		hTrueEeSPD1->Add(_hTrueEeCharmSPD1);
		hTrueEeSPD2->Add(_hTrueEeCharmSPD2);
		hTrueEeSPD3->Add(_hTrueEeCharmSPD3);

		hTrueEeSPD0->Add(_hTrueEeBottomSPD0);
		hTrueEeSPD1->Add(_hTrueEeBottomSPD1);
		hTrueEeSPD2->Add(_hTrueEeBottomSPD2);
		hTrueEeSPD3->Add(_hTrueEeBottomSPD3);

		hTrueEeCharmSPD0->Add(_hTrueEeCharmSPD0);
		hTrueEeCharmSPD1->Add(_hTrueEeCharmSPD1);
		hTrueEeCharmSPD2->Add(_hTrueEeCharmSPD2);
		hTrueEeCharmSPD3->Add(_hTrueEeCharmSPD3);

		hTrueEeBottomSPD0->Add(_hTrueEeBottomSPD0);
		hTrueEeBottomSPD1->Add(_hTrueEeBottomSPD1);
		hTrueEeBottomSPD2->Add(_hTrueEeBottomSPD2);
		hTrueEeBottomSPD3->Add(_hTrueEeBottomSPD3);


		/*
		hTrueXiSPD0->Add(_hTrueXiCharmSPD0);
		hTrueXiSPD1->Add(_hTrueXiCharmSPD1);
		hTrueXiSPD2->Add(_hTrueXiCharmSPD2);
		hTrueXiSPD3->Add(_hTrueXiCharmSPD3);
		hTrueXiSPD4->Add(_hTrueXiCharmSPD4);
		hTrueXiSPD5->Add(_hTrueXiCharmSPD5);
		hTrueXiSPD6->Add(_hTrueXiCharmSPD6);

		hTrueXiSPD0->Add(_hTrueXiBottomSPD0);
		hTrueXiSPD1->Add(_hTrueXiBottomSPD1);
		hTrueXiSPD2->Add(_hTrueXiBottomSPD2);
		hTrueXiSPD3->Add(_hTrueXiBottomSPD3);
		hTrueXiSPD4->Add(_hTrueXiBottomSPD4);
		hTrueXiSPD5->Add(_hTrueXiBottomSPD5);
		hTrueXiSPD6->Add(_hTrueXiBottomSPD6);

		hTrueXiCharmSPD0->Add(_hTrueXiCharmSPD0);
		hTrueXiCharmSPD1->Add(_hTrueXiCharmSPD1);
		hTrueXiCharmSPD2->Add(_hTrueXiCharmSPD2);
		hTrueXiCharmSPD3->Add(_hTrueXiCharmSPD3);
		hTrueXiCharmSPD4->Add(_hTrueXiCharmSPD4);
		hTrueXiCharmSPD5->Add(_hTrueXiCharmSPD5);
		hTrueXiCharmSPD6->Add(_hTrueXiCharmSPD6);

		hTrueXiBottomSPD0->Add(_hTrueXiBottomSPD0);
		hTrueXiBottomSPD1->Add(_hTrueXiBottomSPD1);
		hTrueXiBottomSPD2->Add(_hTrueXiBottomSPD2);
		hTrueXiBottomSPD3->Add(_hTrueXiBottomSPD3);
		hTrueXiBottomSPD4->Add(_hTrueXiBottomSPD4);
		hTrueXiBottomSPD5->Add(_hTrueXiBottomSPD5);
		hTrueXiBottomSPD6->Add(_hTrueXiBottomSPD6);
		*/

		e_c_flag->Add(_e_c_flag);
		e_b_flag->Add(_e_b_flag);

		infile->Close();
		delete infile;

	}//while

	//return;

	TFile *outfile = new TFile(Form("outfile_XiEfficiencyV3_%s.root",ver),"recreate");
	outfile->cd();

	h3TrueXic0SPD->Write();

	hTrueXic0CharmSPD->Write();
	hTrueXic0BottomSPD->Write();

	hTrueEeSPD0->Write();
	hTrueEeSPD1->Write();
	hTrueEeSPD2->Write();
	hTrueEeSPD3->Write();

	hTrueEeCharmSPD0->Write();
	hTrueEeCharmSPD1->Write();
	hTrueEeCharmSPD2->Write();
	hTrueEeCharmSPD3->Write();

	hTrueEeBottomSPD0->Write();
	hTrueEeBottomSPD1->Write();
	hTrueEeBottomSPD2->Write();
	hTrueEeBottomSPD3->Write();

	e_c_flag->Write();
	e_b_flag->Write();

	/*
	hTrueXiSPD0->Write();
	hTrueXiSPD1->Write();
	hTrueXiSPD2->Write();
	hTrueXiSPD3->Write();
	hTrueXiSPD4->Write();
	hTrueXiSPD5->Write();
	hTrueXiSPD6->Write();

	hTrueXiCharmSPD0->Write();
	hTrueXiCharmSPD1->Write();
	hTrueXiCharmSPD2->Write();
	hTrueXiCharmSPD3->Write();
	hTrueXiCharmSPD4->Write();
	hTrueXiCharmSPD5->Write();
	hTrueXiCharmSPD6->Write();

	hTrueXiBottomSPD0->Write();
	hTrueXiBottomSPD1->Write();
	hTrueXiBottomSPD2->Write();
	hTrueXiBottomSPD3->Write();
	hTrueXiBottomSPD4->Write();
	hTrueXiBottomSPD5->Write();
	hTrueXiBottomSPD6->Write();
	*/

	outfile->Close();


}
