#include "DrawTool.C"

TH1D* GetCrossSection(TH1D* hRawXic0, TH1D* hefficiency, const Char_t* Cut, const Char_t* CutFlag){
  double ptbinning[7] = {2., 3., 4., 5., 6., 8., 12.};


  TH1D* heff_tmp = new TH1D(Form("eff_%s_%s_rebin",Cut,CutFlag),"",6,ptbinning);
  for(int i=1; i<7; i++){
    heff_tmp->SetBinContent(i,heff->GetBinContent(i+1));
    heff_tmp->SetBinError(i,heff->GetBinError(i+1));
  }

  TH1D* hXic0Eff = (TH1D*) hRawXic0->Clone(Form("hXic0Eff_%s_%s",Cut,CutFlag));
  hXic0Eff->Divide(hXic0Eff,heff_tmp);

  Double_t ptbin[6] = {1,1,1,1,2,4};
  Double_t deltaY = 1.0;
  Double_t V0ANDcs = 57.8*1000; //2.2%
  Double_t BR = 0.018;
  Double_t N_evt = 1.88554e+09;  //From AliNormalizationCounter
  Double_t Lumi = N_evt/V0ANDcs;
  Double_t CS_factor[6];
  for (int i=0; i<6; i++) CS_factor[i] = 2*ptbin[i]*deltaY*Lumi*BR;

  TH1D* hXic0CrossSection = new TH1D(Form("hXic0CrossSection_%s_%s",cut,cutflag),"",6,ptbinning);

  for (int i=1; i<7; i++){
    Double_t hCS = (hXic0Eff->GetBinContent(i))/(CS_factor[i-1]);
    hXic0CrossSection->SetBinContent(i,hCS);
    hXic0CrossSection->SetBinError(i,hXic0Eff->GetBinError(i)/CS_factor[i-1]);
  }

  delete hXic0Eff;
  delete heff_tmp;

  return hXic0CrossSection;
}
