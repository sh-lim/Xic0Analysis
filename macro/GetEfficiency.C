#include "DrawTool.C"

TH1D* GetEfficiency(TFile* WeightedROOTFile, TFile* MCROOTFile, const Char_t* Cut, const Char_t* CutFlag, Bool_t IsWeighted, Bool_t DrawOption){
  TH1D* hGenXic0 = new TH1D;
  TH1D* hRecoXic0 = new TH1D;
  TH1D* hefficiency = new TH1D;

  if(IsWeighted){
    hGenXic0 = (TH1D*) WeightedROOTFile->Get("hMCGenLevXic0_incW");
    hRecoXic0 = (TH1D*) WeightedROOTFile->Get(Form("hMCRecoLevXic0_%s_%s",Cut,CutFlag));
    hefficiency = (TH1D*) hRecoXic0->Clone(Form("efficiency_%s_%s",Cut,CutFlag));
    hefficiency->Divide(hefficiency,hGenXic0,1,1,"b");

    delete hRecoXic0;

    return hefficiency;
  }

  hGenXic0 = (TH1D*) MCROOTFile->Get("hMCGenLevXic0_incW");
  hRecoXic0 = (TH1D*) MCROOTFile->Get(Form("hMCRecoLevXic0_%s_%s",Cut,CutFlag));
  hefficiency = (TH1D*) hRecoXic0->Clone(Form("efficiency_%s_%s",Cut,CutFlag));
  hefficiency->Divide(hefficiency,hGenXic0,1,1,"b");

  delete hRecoXic0;

  return hefficiency;
}
