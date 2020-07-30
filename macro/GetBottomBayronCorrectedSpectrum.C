#include "DrawTool.C"

TH1D* GetBottomBayronCorrectedSpectrum(TFile* DataROOTFile, TFile* MCROOTFile, TH1D* hCMSLb, Double_t BRFraction, const Char_t* Cut, const Char_t* CutFlag, Bool_t DrawOption){
  #ifdef __CINT__
    gSystem->Load("libRooUnfold");
  #endif

  //1) Fit 7TeV CMS Lb spectrum with Tasllis function---------------------------------------------------------------------------------
  TF1 *fTsallis = new TF1("Lambdab","[0]*x*(pow(1+(sqrt(pow(x,2)+pow(5.619,2))-5.619)/(7.6*1.1),-7.6))",0,50);
  hCMSLb->Fit("Lambdab");
  fTsallis->SetParameters(fTsallis->GetParameters());

  //2) Multiply scale factor to convert to 13TeV Lb---------------------------------------------------------------------------------
  double binning[10] = {1,2,3,4,5,6,8,12,16,20};
  TH1D *hScaleFactor = new TH1D("hScaleFactor","",9, binning);  //B meson ratio -> B(13TeV)/B(7TeV)
  Double_t BC_ScaleFactor[9] = {1.53313, 1.69604, 1.806626, 1.887637, 1.950308, 2.018669, 2.121922, 2.249672, 2.439034};
  Double_T BE_ScaleFactor[9] = {0.002688548, 0.003208365, 0.004097259, 0.005324936, 0.006890631, 0.009749647, 0.01760265, 0.03540223, 0.06652629};
  for(int i = 0; i<9; i++){
    hScaleFactor->SetBinContent(i+1,BC_ScaleFactor[i]);
    hScaleFactor->SetBinError(i+1,BE_ScaleFactor[i]);
  }

  TH1D* h13TeVLb = new TH1D("h13TeVLb","",9,binning);
  for(int i=1; i<10; i++) h13TeVLb->SetBinContent(i,fTsallis->Eval(h13TeVLb->GetBinCenter(i))*hScaleFactor->GetBinContent(i)); //Error is not assigned since we don't know the error at 1 to 10 pT

  //3) Multiply Branching ratio fraction to conver to Xib spectrum---------------------------------------------------------------------------------
  TH1D* h13TeVXib = (TH1D*) h13TeVLb->Clone("h13TeVXib");
  h13TeVXib->Scale(BRFraction);

  //4) Calculate Xib yield---------------------------------------------------------------------------------
  double ptbin[9] = {1,1,1,1,1,2,4,4,4};
  TH1D* h13TeVXibRaw = new TH1D("h13TeVXibRaw","",9,binning);
  Double_t Luminosity=1.88554e+09/(57.8*1000000);  //pp 13TeV integrated luminosity
  for(int i=1; i<10; i++) h13TeVXibRaw->SetBinContent(i,h13TeVXib->GetBinContent(i)*ptbin[i-1]*2*Luminosity);

  TH1D* hGenXib = (TH1D*) MCROOTFile->Get("XibGen05");  //Number of Xib in generation level
  TH1D* hRecoXib = (TH1D*) MCROOTFile->Get(Form("hMCRecoLevXib_%s_%s",Cut,CutFlag));  //Number of Xib in reconstruction level
  TH1D* hRecoeXi = (TH1D*) MCROOTFile->Get(Form("hMCRecoLevPairXib_%s_%s",Cut,CutFlag));  //Number of eXi from Xib
  TH2D* hRM_Xib = (TH2D*) MCROOTFile->Get(Form("hRPM_%s_%s_Xib",Cut,CutFlag));  //Response matrix of Xib and eXi
  TH1D* hXibEff = (TH1D*) hRecoXib->Clone(Form("hXibEff_%s_%s",Cut,CutFlag));
  hXibEff->Divide(hXibEff,hGenXib,1,1,"b");  //Xib efficiency
  h13TeVXibRaw->Multiply(hXibEff);

  //5) Convert to eXi spectrum from Xib spectrum---------------------------------------------------------------------------------
  RooUnfoldResponse response(hRecoXib,hRecoeXi,hRM);
  RooUnfoldBinByBin unfolding(&response, h13TeVXibRaw);  //BinByBin refolding
  TH1D* heXiFromXib = (TH1D*) unfolding.Hreco();

  //6) Add eXi from Xib to eXi pair(RS-WS)---------------------------------------------------------------------------------
  TH1D* hMeas_tmp = (TH1D*) DataROOTFile->Get(Form("hRawPt_%s_%s",Cut,CutFlag));
  TH1D* hMeas = (TH1D*) hMeas_tmp->Clone(Form("hRawPt_%s_%s_use",Cut,CutFlag));
  hMeas->Add(heXiFromXib);

  delete hMeas_tmp;
  delete hGenXib;
  delete hRecoXib;
  delete hRecoeXi;
  delete hRM_Xib;
  delete fTsallis;
  delete hScaleFactor;
  delete h13TeVLb;
  delete h13TeVXib;

  return hMeas;
}
