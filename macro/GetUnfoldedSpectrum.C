#include "DrawTool.C"

TH1D* GetUnfoldedSpectrum(TFile* WeightedROOTFile, TFile* MCROOTFile, TH1D* hMeas, const Char_t* Cut, const Char_t* CutFlag, const Char_t* method, Int_t iteration, Bool_t IsWeighted, Bool_t DrawOption){
  #ifdef __CINT__
    gSystem->Load("libRooUnfold");
  #endif

  double Unfoldbinning[10] = {1,2,3,4,5,6,8,12,16,20};
  double ptbinning[7] = {2., 3., 4., 5., 6., 8., 12.};

  //1) Prepare Histogram---------------------------------------------------------------------------------
  TH1D* hUnweigthedXic0 = (TH1D*) MCROOTFile->Get(Form("hMCRecoLevXic0_%s_%s",Cut,CutFlag));
  TH1D* hUnweigthedeXiPair = (TH1D*) MCROOTFile->Get(Form("hMCRecoLevPair_%s_%s",Cut,CutFlag));
  TH2D* Mat_refold = (TH2D*) MCROOTFile->Get(Form("hRPM_%s_%s",Cut,CutFlag));
  TH2D* Mat_unfold = (TH2D*) MCROOTFile->Get(Form("hRPM_%s_%s_un",Cut,CutFlag));

  TH1D* hWeigthedXic0 = (TH1D*) WeightedROOTFile->Get(Form("hMCRecoLevXic0_%s_%s",Cut,CutFlag));
  TH1D* hWeigthedeXiPair = (TH1D*) WeightedROOTFile->Get(Form("hMCRecoLevPair_%s_%s",Cut,CutFlag));
  TH2D* WeigthedMat_refold = (TH2D*) WeightedROOTFile->Get(Form("hRPM_%s_%s",Cut,CutFlag));
  TH2D* WeigthedMat_unfold = (TH2D*) WeightedROOTFile->Get(Form("hRPM_%s_%s_un",Cut,CutFlag));

  //2) Unfold step of unfolding---------------------------------------------------------------------------------
  RooUnfoldResponse unfold_unweighted(hUnweigthedeXiPair,hUnweigthedXic0,Mat_refold);
  RooUnfoldResponse refold_unweighted(hUnweigthedXic0,hUnweigthedeXiPair,Mat_unfold);
  RooUnfoldResponse unfold_weighted(hWeigthedeXiPair,hWeigthedXic0,WeigthedMat_unfold);
  RooUnfoldResponse refold_weighted(hWeigthedXic0,hWeigthedeXiPair,WeigthedMat_refold);

  TH1D *hUnweightedReco = new TH1D(Form("hUnweightedReco_%s_%s",Cut,CutFlag),"",9,Unfoldbinning);
  TH1D *hWeightedReco = new TH1D(Form("hWeightedReco_func_%s_%s",Cut,CutFlag),"",9,Unfoldbinning);

  const Char_t* Bayes = "Bayes";
  const Char_t* Svd = "Svd";
  if(method == Bayes){
    RooUnfoldBayes unfolding_unweighted (&unfold_unweighted, hMeas, iteration); // OR
    hUnweightedReco = (TH1D*) unfolding_unweighted.Hreco();
    RooUnfoldBayes unfolding_weighted (&unfold_weighted, hMeas, iteration); // OR
    hWeightedReco = (TH1D*) unfolding_weighted.Hreco();
  }
  if(method == Svd){
    RooUnfoldSvd     unfold_unweighted_svd (&unfold_unweighted, hMeas, iteration);   // OR
    hUnweightedReco = (TH1D*) unfold_unweighted_svd.Hreco();
    RooUnfoldSvd unfolding_weighted_svd (&unfold_weighted, hMeas, iteration); // OR
    hWeightedReco = (TH1D*) unfolding_weightedc_svd.Hreco();
  }

  //3) Output---------------------------------------------------------------------------------
  TH1D* hUnweightedUnfolded = new TH1D(Form("hWoUnfolded_%s_%s",Cut,CutFlag),"",6,ptbinning);
  for(int i=1; i<7; i++){
    hUnweightedUnfolded->SetBinContent(i,hUnweightedReco->GetBinContent(i+1));
    hUnweightedUnfolded->SetBinError(i,hUnweightedReco->GetBinError(i+1));
  }
  TH1D* hWeightedUnfolded = new TH1D(Form("hWUnfolded_%s_%s",Cut,CutFlag),"",6,ptbinning);
  for(int i=1; i<7; i++){
    hWeightedUnfolded->SetBinContent(i,hWeightedReco->GetBinContent(i+1));
    hWeightedUnfolded->SetBinError(i,hWeightedReco->GetBinError(i+1));
  }

  delete hUnweigthedXic0;
  delete hUnweigthedeXiPair;
  delete Mat_refold;
  delete Mat_unfold;
  delete hWeigthedXic0;
  delete hWeigthedeXiPair;
  delete WeigthedMat_refold;
  delete WeigthedMat_unfold;
  delete hUnweightedReco;
  delete hWeightedReco;

  if(!IsWeighted) return hUnweightedUnfolded;
  if(IsWeighted) return hWeightedUnfolded;

  return hWeightedUnfolded;    //default
}
