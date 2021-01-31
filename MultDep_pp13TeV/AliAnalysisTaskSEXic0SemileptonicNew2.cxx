/**************************************************************************
* Copyright(c) 1998-2018, ALICE Experiment at CERN, All rights reserved. *
*                                                                        *
* Author: The ALICE Off-line Project.                                    *
* Contributors are mentioned in the code where appropriate.              *
*                                                                        *
* Permission to use, copy, modify and distribute this software and its   *
* documentation strictly for non-commercial purposes is hereby granted   *
* without fee, provided that the above copyright notice appears in all   *
* copies and that both the copyright notice and this permission notice   *
* appear in the supporting documentation. The authors make no claims     *
* about the suitability of this software for any purpose. It is          *
* provided "as is" without express or implied warranty.                  *
**************************************************************************/

// Comment describing what this class does needed!
//==================================================================
// Xi_c^0 analysis
// by Jinjoo Seo
//==================================================================

#include <TSystem.h>
#include <TParticle.h>
#include <TParticlePDG.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <THnSparse.h>
#include <TLorentzVector.h>
#include <TTree.h>
#include "TROOT.h"
#include <TDatabasePDG.h>
#include <AliAnalysisDataSlot.h>
#include <AliAnalysisDataContainer.h>
#include "AliMCEvent.h"
#include "AliAnalysisManager.h"
#include "AliAODMCHeader.h"
#include "AliAODHandler.h"
#include "AliAODVertex.h"
#include "AliESDVertex.h"
#include "AliRDHFCuts.h"
#include "AliAODRecoDecay.h"
#include "AliAODRecoDecayHF.h"
#include "AliAODRecoCascadeHF.h"
#include "AliESDtrack.h"
#include "AliAODTrack.h"
#include "AliAODcascade.h"
#include "AliAODMCParticle.h"
#include "AliAnalysisTaskSE.h"
#include "AliAnalysisTaskSEXic0SemileptonicNew2.h"
#include "AliPIDResponse.h"
#include "AliPIDCombined.h"
#include "AliTOFPIDResponse.h"
#include "AliAODPidHF.h"
#include "AliInputEventHandler.h"
#include "AliPPVsMultUtils.h"
#include "AliESDtrackCuts.h"
#include "AliESDtrack.h"
#include "AliAODInputHandler.h"
//#include "AliAnalysisTaskSEHFTreeCreator.h"
#include "AliMultSelection.h"

using namespace std;

const Double_t pi = TMath::Pi();
enum {  kPN=1, kPP, kNN, kMixing, kAllType}; //P=Positive charge, N=Negative

AliAnalysisTaskSEXic0RunTable::AliAnalysisTaskSEXic0RunTable() :
  fCollisionType(kUnknownCollType)
  {;}   //defult constructor

AliAnalysisTaskSEXic0RunTable::AliAnalysisTaskSEXic0RunTable(Int_t fRunNumber) :
  fCollisionType(kUnknownCollType) {
  //if (fRunNumber>=256504 && fRunNumber<=260014) fCollisionType=kPP; //LHC16kl
  //else if (fRunNumber>=254604 && fRunNumber<=255467) fCollisionType=kPP; //LHC16h
  fCollisionType=kPP;
}
AliAnalysisTaskSEXic0RunTable::~AliAnalysisTaskSEXic0RunTable() {;}

//___________________________________________________________________
AliAnalysisTaskSEXic0SemileptonicNew2::AliAnalysisTaskSEXic0SemileptonicNew2() :
  AliAnalysisTaskSE("AliAnalysisTaskSEXic0SemileptonicNew2"),
  fOption(){
    DefineOutput (1, TDirectory::Class());
    DefineOutput (2, TList::Class());
    DefineOutput (3, TTree::Class());
    DefineOutput (4, TTree::Class());
    DefineOutput (5, TTree::Class());
    DefineOutput (6, TTree::Class());
    DefineOutput (7, TTree::Class());
    DefineOutput (8, AliNormalizationCounter::Class());
    fMCCutTreeVariable = 0;
    fPaireXiTreeVariable = 0;
    fMCTreeVariable = 0;
    fEventTreeVariable = 0;
    fMCeTreeVariable = 0;
    fMCCutTree = 0;
    fPaireXiTree = 0;
    fMCTree = 0;
    fEventTree = 0;
		fMCeTree = 0;
    fCounter = 0;
}
//___________________________________________________________________
AliAnalysisTaskSEXic0SemileptonicNew2::AliAnalysisTaskSEXic0SemileptonicNew2( const char *name, const char *option ) :
  AliAnalysisTaskSE(name),
  fOption(option){
    DefineOutput (1, TDirectory::Class());
    DefineOutput (2, TList::Class());
    DefineOutput (3, TTree::Class());
    DefineOutput (4, TTree::Class());
    DefineOutput (5, TTree::Class());
    DefineOutput (6, TTree::Class());
    DefineOutput (7, TTree::Class());
    DefineOutput (8, AliNormalizationCounter::Class());
    fMCCutTreeVariable = 0;
    fPaireXiTreeVariable = 0;
    fMCTreeVariable = 0;
    fEventTreeVariable = 0;
		fMCeTreeVariable = 0;
    fMCCutTree = 0;
    fPaireXiTree = 0;
    fMCTree = 0;
    fEventTree = 0;
		fMCeTree = 0;
    fCounter = 0;
}
//___________________________________________________________________
AliAnalysisTaskSEXic0SemileptonicNew2::AliAnalysisTaskSEXic0SemileptonicNew2( const AliAnalysisTaskSEXic0SemileptonicNew2& ap ) :
  AliAnalysisTaskSE("AliAnalysisTaskSEXic0SemileptonicNew2"),
  fOption(ap.fOption) {;}

//___________________________________________________________________
AliAnalysisTaskSEXic0SemileptonicNew2& AliAnalysisTaskSEXic0SemileptonicNew2::operator = ( const AliAnalysisTaskSEXic0SemileptonicNew2& ap ) {
  // assignment operator
  this->~AliAnalysisTaskSEXic0SemileptonicNew2();
  new(this) AliAnalysisTaskSEXic0SemileptonicNew2(ap);
  return *this;
}
//___________________________________________________________________
AliAnalysisTaskSEXic0SemileptonicNew2::~AliAnalysisTaskSEXic0SemileptonicNew2(){
  delete fOutput;
  delete fMCCutTree;
  delete fPaireXiTree;
  delete fHistos;
  delete fMCTree;
  delete fMCeTree;
  delete fMCCutTree;
  delete fPaireXiTree;
  delete fEventTree;
  delete fTrackCuts;
  delete fTrackCutsCase0;
  delete fTrackCutsCase1;
  delete fTrackCutsCase2;
  delete fTrackCutsCase3;
  delete fTrackCutsCase4;
  delete fTrackCutsCase5;
  delete fPIDResponse;
  delete fRunTable;
  delete fCounter;
  delete fEvtCuts;
  delete fMCCutTreeVariable;
  delete fPaireXiTreeVariable;
  delete fMCTreeVariable;
  delete fEventTreeVariable;
  delete fMCeTreeVariable;
  delete fWeightFit;
}

//___________________________________________________________________
void AliAnalysisTaskSEXic0SemileptonicNew2::UserCreateOutputObjects(){
  fTrackCuts = new AliESDtrackCuts();
  {
    //fTrackCuts->SetMinNClustersTPC(fNClustersTPCMin);  //tpc cluster
    fTrackCuts->SetRequireTPCRefit(kTRUE);  //tpc refit
    fTrackCuts->SetRequireITSRefit(kTRUE);  //its refit
    fTrackCuts->SetMinNClustersITS(fNClustersITSMin);  //its cluster
    fTrackCuts->SetClusterRequirementITS(AliESDtrackCuts::kSPD, AliESDtrackCuts::kBoth);
    fTrackCuts->SetMaxDCAToVertexXY(1.0);
    fTrackCuts->SetMaxDCAToVertexZ(2.0);
    fTrackCuts->SetDCAToVertex2D(kTRUE);
    fTrackCuts->SetMaxChi2PerClusterITS(36);
  }

  fTrackCutsCase0 = new AliESDtrackCuts();
  {
    fTrackCutsCase0->SetRequireTPCRefit(kFALSE);  //tpc refit
    fTrackCutsCase0->SetRequireITSRefit(kFALSE);  //its refit
    fTrackCutsCase0->SetMinNClustersITS(-1);  //its cluster
    fTrackCutsCase0->SetClusterRequirementITS(AliESDtrackCuts::kSPD, AliESDtrackCuts::kOff);
    fTrackCutsCase0->SetMaxDCAToVertexXY(1e10);
    fTrackCutsCase0->SetMaxDCAToVertexZ(1e10);
    fTrackCutsCase0->SetDCAToVertex2D(kTRUE);
    fTrackCutsCase0->SetMaxChi2PerClusterITS(1e10);
  }

  fTrackCutsCase1 = new AliESDtrackCuts();
  {
    fTrackCutsCase1->SetRequireTPCRefit(kTRUE);  //tpc refit
    fTrackCutsCase1->SetRequireITSRefit(kFALSE);  //its refit
    fTrackCutsCase1->SetMinNClustersITS(-1);  //its cluster
    fTrackCutsCase1->SetClusterRequirementITS(AliESDtrackCuts::kSPD, AliESDtrackCuts::kOff);
    fTrackCutsCase1->SetMaxDCAToVertexXY(1e10);
    fTrackCutsCase1->SetMaxDCAToVertexZ(1e10);
    fTrackCutsCase1->SetDCAToVertex2D(kTRUE);
    fTrackCutsCase1->SetMaxChi2PerClusterITS(1e10);
  }

  fTrackCutsCase2 = new AliESDtrackCuts();
  {
    fTrackCutsCase2->SetRequireTPCRefit(kTRUE);  //tpc refit
    fTrackCutsCase2->SetRequireITSRefit(kTRUE);  //its refit
    fTrackCutsCase2->SetMinNClustersITS(-1);  //its cluster
    fTrackCutsCase2->SetClusterRequirementITS(AliESDtrackCuts::kSPD, AliESDtrackCuts::kOff);
    fTrackCutsCase2->SetMaxDCAToVertexXY(1e10);
    fTrackCutsCase2->SetMaxDCAToVertexZ(1e10);
    fTrackCutsCase2->SetDCAToVertex2D(kTRUE);
    fTrackCutsCase2->SetMaxChi2PerClusterITS(1e10);
  }

  fTrackCutsCase3 = new AliESDtrackCuts();
  {
    fTrackCutsCase3->SetRequireTPCRefit(kTRUE);  //tpc refit
    fTrackCutsCase3->SetRequireITSRefit(kTRUE);  //its refit
    fTrackCutsCase3->SetMinNClustersITS(fNClustersITSMin);  //its cluster
    fTrackCutsCase3->SetClusterRequirementITS(AliESDtrackCuts::kSPD, AliESDtrackCuts::kBoth);
    fTrackCutsCase3->SetMaxDCAToVertexXY(1e10);
    fTrackCutsCase3->SetMaxDCAToVertexZ(1e10);
    fTrackCutsCase3->SetDCAToVertex2D(kTRUE);
    fTrackCutsCase3->SetMaxChi2PerClusterITS(1e10);
  }

  fTrackCutsCase4 = new AliESDtrackCuts();
  {
    fTrackCutsCase4->SetRequireTPCRefit(kTRUE);  //tpc refit
    fTrackCutsCase4->SetRequireITSRefit(kTRUE);  //its refit
    fTrackCutsCase4->SetMinNClustersITS(fNClustersITSMin);  //its cluster
    fTrackCutsCase4->SetClusterRequirementITS(AliESDtrackCuts::kSPD, AliESDtrackCuts::kBoth);
    fTrackCutsCase4->SetMaxDCAToVertexXY(1e10);
    fTrackCutsCase4->SetMaxDCAToVertexZ(1e10);
    fTrackCutsCase4->SetDCAToVertex2D(kTRUE);
    fTrackCutsCase4->SetMaxChi2PerClusterITS(36);
  }

  fTrackCutsCase5 = new AliESDtrackCuts();
  {
    fTrackCutsCase5->SetRequireTPCRefit(kTRUE);  //tpc refit
    fTrackCutsCase5->SetRequireITSRefit(kTRUE);  //its refit
    fTrackCutsCase5->SetMinNClustersITS(fNClustersITSMin);  //its cluster
    fTrackCutsCase5->SetClusterRequirementITS(AliESDtrackCuts::kSPD, AliESDtrackCuts::kBoth);
    fTrackCutsCase5->SetMaxDCAToVertexXY(1.0);
    fTrackCutsCase5->SetMaxDCAToVertexZ(2.0);
    fTrackCutsCase5->SetDCAToVertex2D(kTRUE);
    fTrackCutsCase5->SetMaxChi2PerClusterITS(36);
  }

  fEvtCuts=new AliRDHFCutsXictoeleXifromAODtracks();

  fEvtCuts->SetUsePhysicsSelection(kTRUE);
  fEvtCuts->SetTriggerClass("");
  fEvtCuts->SetUseInt7TriggerPP2012();
  //fEvtCuts->ResetMaskAndEnableMBTrigger();

  fHistos = new THistManager("histogram");

  vector <TString> Event ={"All","ProperB","RDHCCutsSel","Sel","MB","PSpileup","Goodz","Goodzcut"};
  auto hEventCount = fHistos->CreateTH1("hEventNumbers","",Event.size(), 0, Event.size());
  for(auto i=0u; i<Event.size(); i++) hEventCount->GetXaxis()->SetBinLabel(i+1,Event.at(i).Data());

  Double_t bin[8] = {1,2,3,4,5,6,8,12};
  Double_t bin_old[8] = {0,1,2,3.2,4.4,6,8,12};
  Double_t rapbin[21] = {-1,-0.9,-0.8,-0.7,-0.6,-0.5,-0.4,-0.3,-0.2,-0.1,0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1};
  Double_t widebin[10] = {1,2,3,4,5,6,8,12,16,20};

	Double_t rapbin2[11] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};

	Double_t centbin[101];
	for (int ii=0; ii<101; ii++) centbin[ii] = ii;

	Double_t SPDbin[201];
	for (int ii=0; ii<201; ii++) SPDbin[ii] = ii;

  fHistos->CreateTH1("NumOfEvtperRun","",5000,0,5000,"s");
  fHistos->CreateTH1("Centrality","",100,0,100,"s");
  fHistos->CreateTH1("NumOfCascs","",10,0,10,"s");
  fHistos->CreateTH1("NumOfe","",5000,0,5000,"s");
  fHistos->CreateTH1("NumOfXi","",5000,0,5000,"s");

	fHistos->CreateTH2("ZvertexGenReco","",150,-15,15,150,-15,15,"s");
	fHistos->CreateTH2("NumOfTrkGenReco","",500,0,500,500,0,500,"s");

  fHistos->CreateTH1("hNonPromptXicRap","",500,-5,5,"s");
  fHistos->CreateTH1("hPromptXicRap","",500,-5,5,"s");
  fHistos->CreateTH1("hXicRap","",500,-5,5,"s");

  fHistos->CreateTH2("nSigmaTPCvsPt","",10,0.,5.,200,-10.,10.,"s");
  fHistos->CreateTH2("nSigmaTOFvsPt","",50,0.,5.,15,-5.,5.,"s");
  fHistos->CreateTH1("DSElectronPair","",100,0.,0.5,"s");
  fHistos->CreateTH1("SSElectronPair","",100,0.,0.5,"s");

  fHistos->CreateTH1("hXimass","",100,1.26,1.38,"s");
  fHistos->CreateTH1("hXimass_total","",2000,0,3,"s");
  fHistos->CreateTH2("hXimassvsPt","",100,1.29,1.35,10,0.,10.,"s");

  fHistos->CreateTH1("hEleXiMassRS","",10,1.3,3.3,"s");
  fHistos->CreateTH1("hEleXiMassWS","",10,1.3,3.3,"s");
  fHistos->CreateTH1("hEleXiPtRS","",7,bin,"s");
  fHistos->CreateTH1("hEleXiPtWS","",7,bin,"s");
  fHistos->CreateTH1("hEleXiPtRS_SameSign","",7,bin,"s");
  fHistos->CreateTH1("hEleXiPtWS_SameSign","",7,bin,"s");
  fHistos->CreateTH1("hLooseEleXiPtRS","",7,bin,"s");
  fHistos->CreateTH1("hLooseEleXiPtWS","",7,bin,"s");

  fHistos->CreateTH1("eXiFromXib","",9,widebin,"s");
  fHistos->CreateTH1("Xib","",9,widebin,"s");
  fHistos->CreateTH2("XibvseXiRPM","",9,widebin,9,widebin,"s");
  fHistos->CreateTH1("eXiFromXibGen","",9,widebin,"s");
  fHistos->CreateTH1("XibGen","",9,widebin,"s");
  fHistos->CreateTH1("XibGen05","",9,widebin,"s");
  fHistos->CreateTH2("XibvseXiRPMGen","",9,widebin,9,widebin,"s");

	fHistos->CreateTH1("hTruePion0","",100,0,10,"s");
	fHistos->CreateTH1("hTruePion1","",100,0,10,"s");
	fHistos->CreateTH1("hTruePion2","",100,0,10,"s");
	fHistos->CreateTH1("hTrueProton3","",100,0,10,"s");

	fHistos->CreateTH1("hRecoPion0","",100,0,10,"s");
	fHistos->CreateTH1("hRecoPion1","",100,0,10,"s");
	fHistos->CreateTH1("hRecoPion2","",100,0,10,"s");
	fHistos->CreateTH1("hRecoProton3","",100,0,10,"s");

  //fHistos->CreateTH2("hXicPtRap","",9,widebin,21,rapbin,"s");
	fHistos->CreateTH2("hTrueXic0","",7,bin,100,centbin,"s");
	fHistos->CreateTH2("hTrueXic0W","",7,bin,100,centbin,"s");
	fHistos->CreateTH3("hTrueXic0SPD","",7,bin,10,rapbin2,200,SPDbin,"s");
	fHistos->CreateTH3("hTrueXic0WSPD","",7,bin,10,rapbin2,200,SPDbin,"s");
  fHistos->CreateTH1("hTrueXic0_oldbin","",7,bin_old,"s");
  fHistos->CreateTH1("hTrueXic0W_oldbin","",7,bin_old,"s");
  fHistos->CreateTH1("hTrueXic0_rap8","",7,bin,"s");
  fHistos->CreateTH1("hTrueXic0W_rap8","",7,bin,"s");
  fHistos->CreateTH1("hTrueXic0_oldbin_rap8","",7,bin_old,"s");
  fHistos->CreateTH1("hTrueXic0W_oldbin_rap8","",7,bin_old,"s");
  fHistos->CreateTH1("hTruePaireXi","",7,bin,"s");
  fHistos->CreateTH1("hGenXic0PtFromXib","",7,bin,"s");
  fHistos->CreateTH1("hGenXic0PtFromXic","",7,bin,"s");
	fHistos->CreateTH2("hXic0PtFromBottom1","",7,bin,100,centbin,"s");
	fHistos->CreateTH2("hXic0PtFromBottom2","",7,bin,100,centbin,"s");
  fHistos->CreateTH2("hXic0PtFromCharm1","",7,bin,100,centbin,"s");
  fHistos->CreateTH2("hXic0PtFromCharm2","",7,bin,100,centbin,"s");
	fHistos->CreateTH2("hXic0PtFromBottom1SPD","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hXic0PtFromBottom2SPD","",7,bin,200,SPDbin,"s");
  fHistos->CreateTH2("hXic0PtFromCharm1SPD","",7,bin,200,SPDbin,"s");
  fHistos->CreateTH2("hXic0PtFromCharm2SPD","",7,bin,200,SPDbin,"s");
  fHistos->CreateTH1("hElectronFromXic0","",7,bin,"s");
  fHistos->CreateTH1("hCascadeFromXic0","",7,bin,"s");
  fHistos->CreateTH1("hMCXic0AllRap","",12,0,12,"s");
  fHistos->CreateTH2("hMCXic0vsPair","",7,bin,7,bin,"s");

	fHistos->CreateTH3("hTrueXi","",15,0,15,100,0,20,50,-2.5,2.5,"s");
	fHistos->CreateTH3("hTrueEe","",15,0,15,100,0,20,50,-2.5,2.5,"s");

	fHistos->CreateTH2("hTrueXiCharmSPD0","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueXiCharmSPD1","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueXiCharmSPD2","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueXiCharmSPD3","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueXiCharmSPD4","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueXiCharmSPD5","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueXiCharmSPD6","",7,bin,200,SPDbin,"s");

	fHistos->CreateTH2("hTrueXiBottomSPD0","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueXiBottomSPD1","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueXiBottomSPD2","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueXiBottomSPD3","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueXiBottomSPD4","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueXiBottomSPD5","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueXiBottomSPD6","",7,bin,200,SPDbin,"s");

	fHistos->CreateTH2("hTrueEeCharmSPD0","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueEeCharmSPD1","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueEeCharmSPD2","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueEeCharmSPD3","",7,bin,200,SPDbin,"s");

	fHistos->CreateTH2("hTrueEeSPD1Case0","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueEeSPD1Case1","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueEeSPD1Case2","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueEeSPD1Case3","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueEeSPD1Case4","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueEeSPD1Case5","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueEeSPD1Case6","",7,bin,200,SPDbin,"s");

	fHistos->CreateTH2("hTrueEeBottomSPD0","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueEeBottomSPD1","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueEeBottomSPD2","",7,bin,200,SPDbin,"s");
	fHistos->CreateTH2("hTrueEeBottomSPD3","",7,bin,200,SPDbin,"s");

	fHistos->CreateTH2("hTrueEeSPD1DCA","",200,0,200,100,0,5.0,"s");

	fHistos->CreateTProfile("hprofTrueXic0PtSPD0","",7,bin,"s");
	fHistos->CreateTProfile("hprofTrueXic0PtSPD1","",7,bin,"s");
	fHistos->CreateTProfile("hprofTrueXic0PtSPD2","",7,bin,"s");

  fHistos->CreateTH2("hXic0vseXiRPM","",9,widebin,9,widebin,"s");
  fHistos->CreateTH1("hGenXic0Pt","",9,widebin,"s");
  fHistos->CreateTH1("hGenXic0Pt1","",9,widebin,"s");
  fHistos->CreateTH1("hGenXic0Pt2","",9,widebin,"s");
  fHistos->CreateTH1("hRecoPairPt","",9,widebin,"s");

  vector <TString> DecayChannel ={"e&Xi","!e&Xi","e&!Xi","!e&!Xi"};
  auto hMCXic0Decays = fHistos->CreateTH1("hMCXic0Decays","",DecayChannel.size(), 0, DecayChannel.size());
  for(auto i=0u; i<DecayChannel.size(); i++) hMCXic0Decays->GetXaxis()->SetBinLabel(i+1,DecayChannel.at(i).Data());

  fWeightFit = new TF1("fWeightFit","expo",0,12);
  fWeightFit -> SetParameter(0,GetFitParameter1());
  fWeightFit -> SetParameter(1,GetFitParameter2());

//---------------------------CUT STUDY (MC Xi from Xic0)---------------------------//
  vector <TString> ent6 ={"all","DCAV0Pr_c","DCAV0Pi_c","DCABach_c","DCAV0_c","COS1_c","COS2_c","DLXi_c","DLV0_c"};
  auto h6 = fHistos->CreateTH1("C_flag","",ent6.size(), 0, ent6.size());
  for(auto i=0u; i<ent6.size(); i++) h6->GetXaxis()->SetBinLabel(i+1,ent6.at(i).Data());

  vector <TString> ent7 ={"all","DCAV0Pr_b","DCAV0Pi_b","DCABach_b","DCAV0_b","COS1_b","COS2_b","DLXi_b","DLV0_b"};
  auto h7 = fHistos->CreateTH1("B_flag","",ent7.size(), 0, ent7.size());
  for(auto i=0u; i<ent7.size(); i++) h7->GetXaxis()->SetBinLabel(i+1,ent7.at(i).Data());

  vector <TString> ent8 ={"all","DLXi_c","DCABach_c","DCAV0Pi_c","DCAV0Pr_c","DCAV0_c","COS1_c","COS2_c","DLV0_c"};
  auto h8 = fHistos->CreateTH1("Ccut_flag","",ent8.size(), 0, ent8.size());
  for(auto i=0u; i<ent8.size(); i++) h8->GetXaxis()->SetBinLabel(i+1,ent8.at(i).Data());

  vector <TString> ent9 ={"all","DLXi_b","DCABach_b","DCAV0Pi_b","DCAV0Pr_b","DCAV0_b","COS1_b","COS2_b","DLV0_b"};
  auto h9 = fHistos->CreateTH1("Bcut_flag","",ent9.size(), 0, ent9.size());
  for(auto i=0u; i<ent9.size(); i++) h9->GetXaxis()->SetBinLabel(i+1,ent9.at(i).Data());

  vector <TString> ent10 ={"all","Filterbit_c","TrackCut_c","pT_c","eta_c","TOF_c","TPC_c","prefilter_c"};
  auto h10 = fHistos->CreateTH1("e_c_flag","",ent10.size(), 0, ent10.size());
  for(auto i=0u; i<ent10.size(); i++) h10->GetXaxis()->SetBinLabel(i+1,ent10.at(i).Data());

  vector <TString> ent11 ={"all","Filterbit_b","TrackCut_b","pT_b","eta_b","TOF_b","TPC_b","prefilter_b"};
  auto h11 = fHistos->CreateTH1("e_b_flag","",ent11.size(), 0, ent11.size());
  for(auto i=0u; i<ent11.size(); i++) h11->GetXaxis()->SetBinLabel(i+1,ent11.at(i).Data());

  fHistos->CreateTH1("hDCAV0PrToPrimVertex","",2500,0.,5.,"s");
  fHistos->CreateTH1("hDCAV0PiToPrimVertex","",2500,0.,5.,"s");
  fHistos->CreateTH1("hDCABachToPrimVertex","",2500,0.,5.,"s");
  fHistos->CreateTH1("hDCAV0ToPrimVertex","",2500,0.,5.,"s");
  fHistos->CreateTH1("hV0CosineOfPoiningAngleXi","",500,0.,1.,"s");
  fHistos->CreateTH1("hV0CosineOfPoiningAngleV0Xi","",500,0.,1.,"s");
  fHistos->CreateTH1("hCascDecayLength","",1000,0.,20.,"s");
  fHistos->CreateTH1("hDecayLengthV0","",1000,0.,20.,"s");

  fHistos->CreateTH1("hDCAV0PrToPrimVertex_b","",2500,0.,5.,"s");
  fHistos->CreateTH1("hDCAV0PiToPrimVertex_b","",2500,0.,5.,"s");
  fHistos->CreateTH1("hDCABachToPrimVertex_b","",2500,0.,5.,"s");
  fHistos->CreateTH1("hDCAV0ToPrimVertex_b","",2500,0.,5.,"s");
  fHistos->CreateTH1("hV0CosineOfPoiningAngleXi_b","",500,0.,1.,"s");
  fHistos->CreateTH1("hV0CosineOfPoiningAngleV0Xi_b","",500,0.,1.,"s");
  fHistos->CreateTH1("hCascDecayLength_b","",1000,0.,20.,"s");
  fHistos->CreateTH1("hDecayLengthV0_b","",1000,0.,20.,"s");

  fHistos->CreateTH1("hDCAV0PrToPrimVertex_c","",2500,0.,5.,"s");
  fHistos->CreateTH1("hDCAV0PiToPrimVertex_c","",2500,0.,5.,"s");
  fHistos->CreateTH1("hDCABachToPrimVertex_c","",2500,0.,5.,"s");
  fHistos->CreateTH1("hDCAV0ToPrimVertex_c","",2500,0.,5.,"s");
  fHistos->CreateTH1("hV0CosineOfPoiningAngleXi_c","",500,0.,1.,"s");
  fHistos->CreateTH1("hV0CosineOfPoiningAngleV0Xi_c","",500,0.,1.,"s");
  fHistos->CreateTH1("hCascDecayLength_c","",1000,0.,20.,"s");
  fHistos->CreateTH1("hDecayLengthV0_c","",1000,0.,20.,"s");

  PostData(1,fHistos);

  PostData(2,fTrackCuts);

  DefineMCCutTree();
  PostData(3,fMCCutTree);

  DefinePaireXiTree();
  PostData(4,fPaireXiTree);

  DefineMCPaireXiTree();
  PostData(5,fMCTree);

  DefineEventTree();
  PostData(6,fEventTree);

	DefineMCeTree();
  PostData(7,fMCeTree);

  fCounter = new AliNormalizationCounter("NormalizationCounter");
  fCounter->SetStudyMultiplicity(kTRUE,1.); //check
  fCounter->Init();
  PostData(8,fCounter);

}

//___________________________________________________________________
void AliAnalysisTaskSEXic0SemileptonicNew2::UserExec(Option_t* ){
  // Pointer to a event----------------------------------------------------
  AliVEvent *event = InputEvent();
  if (!event){
    Printf("ERROR: Could not retrieve event");
    return;
  }

  // ------------------------------------------------------------------------
  // AOD Analysis Start... --------------------------------------------------
  Int_t runnumber;
  event->IsA()==AliESDEvent::Class()
  ? fEvt = dynamic_cast<AliESDEvent*>(event)
  : fEvt = dynamic_cast<AliAODEvent*>(event);
  if (!fEvt) return;

  fHistos->FillTH1("hEventNumbers","All",1);

  fBzkG = (Double_t)fEvt->GetMagneticField();
  if (TMath::Abs(fBzkG)<0.001) return;

  fHistos->FillTH1("hEventNumbers","ProperB",1);

  fRunNumber = fEvt->GetRunNumber();
  fRunTable = new AliAnalysisTaskSEXic0RunTable(fRunNumber);

  Float_t fV0MCentrality = 300;
	Float_t fSPDCentrality = -1;
	Float_t fV0MValue = 0;
	Float_t fSPDValue = 0;
  AliMultSelection *MultSelection = 0x0;
  MultSelection = (AliMultSelection *) fEvt->FindListObject("MultSelection");
  if(!MultSelection) {
   //If you get this warning (and lPercentiles 300) please check that the AliMultSelectionTask actually ran (before your task)
   AliWarning("AliMultSelection object not found!");
  }else{
		if(kPA) fV0MCentrality = MultSelection->GetMultiplicityPercentile("V0A");
		if(kPP) fV0MCentrality = MultSelection->GetMultiplicityPercentile("V0M");
		fSPDCentrality = MultSelection->GetMultiplicityPercentile("SPDTracklets");
		fV0MValue = MultSelection->GetEstimator("V0M")->GetValue();
		fSPDValue = MultSelection->GetEstimator("SPDTracklets")->GetValue();
  }

  fCounter->StoreEvent(fEvt,fEvtCuts,IsMC);

  // Load InputHandler for each event---------------------------------------
  AliInputEventHandler* inputHandler = (AliInputEventHandler*) AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler();
  // -----------------------------------------------------------------------
  Bool_t IsMinimumBias = kFALSE;

  fPIDResponse = (AliPIDResponse*) inputHandler->GetPIDResponse();
  if(!fPIDResponse) printf("AliAnalysisTaskSEXic0SemileptonicNew2 No PIDd\n");

  //fHistos->FillTH1("hEventNumbers","All",1);
  if(fEvtCuts->IsEventSelected(fEvt)) fHistos->FillTH1("hEventNumbers","RDHCCutsSel",1);

  // Physics Selection -----------------------------------------------------
  if(!(inputHandler->IsEventSelected())) return;
  fHistos->FillTH1("hEventNumbers","Sel",1);
  // -----------------------------------------------------------------------

  // Physics Selection & kINT7----------------------------------------------
  IsMinimumBias = inputHandler->IsEventSelected() & AliVEvent::kINT7; //mulplisity flat

  //LHC16k and l are CD dedicated runs! CD-online-trigger is used.
  TString firedTriggerClasses = fEvt->GetFiredTriggerClasses();
  if (fOption.Contains("LHC16k") || fOption.Contains("LHC16l")){
    firedTriggerClasses.Contains("CINT7-B-NOPF-CENT") ?  IsMinimumBias = kTRUE : IsMinimumBias = kFALSE; }

  if (!IsMinimumBias) return;
  fHistos->FillTH1("hEventNumbers","MB",1);
  // -----------------------------------------------------------------------

  // Reject pile-up events--------------------------------------------------
  if (!IsMC && fEvt->IsPileupFromSPD(3.,0.8,3.,2.,5.)) return;
  fHistos->FillTH1("hEventNumbers","PSpileup",1);
  // -----------------------------------------------------------------------

  // Primary Vertex Selection-----------------------------------------------
  const AliVVertex* Vtx = fEvt->GetPrimaryVertex();
  if(!Vtx) return;

  if(Vtx->GetNContributors()<1) return;
  fHistos->FillTH1("hEventNumbers","Goodz",1);
  if(!(fabs(Vtx->GetZ())<10.)) return;
  fHistos->FillTH1("hEventNumbers","Goodzcut",1);

	if(IsHighMul){
		if(!AliPPVsMultUtils::IsMinimumBias(fEvt)) return;
		if(!AliPPVsMultUtils::IsINELgtZERO(fEvt)) return;                 //INEL >0
		if(!AliPPVsMultUtils::IsAcceptedVertexPosition(fEvt)) return;
		if(!AliPPVsMultUtils::IsNotPileupSPDInMultBins(fEvt)) return;
		if(!AliPPVsMultUtils::HasNoInconsistentSPDandTrackVertices(fEvt)) return;
	}

	fEventTreeVariable[0] = fRunNumber;
	fEventTreeVariable[1] = GetEvID(); 
	fEventTreeVariable[2] = fV0MCentrality;
	fEventTreeVariable[3] = fSPDCentrality;
	fEventTreeVariable[4] = fV0MValue;
	fEventTreeVariable[5] = fSPDValue;
	fEventTreeVariable[6] = Vtx->GetZ();
 // -----------------------------------------------------------------------
 //-----------------------Event Selection End------------------------------
 // -----------------------------------------------------------------------

 fHistos->FillTH1("NumOfEvtperRun",fRunNumber-fRunOffset);
 fHistos->FillTH1("Centrality",fV0MCentrality);

 if ( fEvt->IsA()!=AliAODEvent::Class() ){
	 cout << "Strange events!!" << endl;
 }

 if (IsMC && fEvt->IsA()==AliAODEvent::Class())
 {
   fMC = inputHandler->MCEvent();
   AliAODMCHeader *mcHeader = (AliAODMCHeader*)fEvt->GetList()->FindObject(AliAODMCHeader::StdBranchName());
   Double_t zMCVertex = mcHeader->GetVtxZ();

	 fHistos->FillTH2("ZvertexGenReco",zMCVertex, Vtx->GetZ());

   if(!(fabs(zMCVertex)<10.)) return;

   for (Int_t iTracks = 0; iTracks < (fMC->GetNumberOfTracks()); iTracks++)
   {
     AliAODMCParticle* MCparticle = (AliAODMCParticle*) fMC->GetTrack(iTracks);
     if(!MCparticle) continue;
     FillMCXic0(MCparticle);
     if(FillMCXib(MCparticle)) continue;
   }
 }

 int nMCTracks = fMC->GetNumberOfTracks(); 
 int nMCTracksCut = 0;

 for (Int_t iTracks = 0; iTracks < nMCTracks; iTracks++)
 {
	 AliAODMCParticle* MCparticle = (AliAODMCParticle*) fMC->GetTrack(iTracks);
	 if(!MCparticle) continue;
	 if ( fabs(MCparticle->Eta())>0.9 ) continue; 

	 int pdgcode = abs(MCparticle->GetPdgCode());

	 if ( MCparticle->IsPrimary() ){
		 if ( pdgcode==211 ) fHistos->FillTH1("hTruePion0",MCparticle->Pt());
		 /*
		 cout 
			 << "Gen index: " << MCparticle->GetGeneratorIndex()
			 << ", Gen vx: " << MCparticle->Xv()
			 << ", Gen vy: " << MCparticle->Yv()
			 << ", Gen vz: " << MCparticle->Zv()
			 << endl;
		 */
		 continue;
	 }

	 if ( !(pdgcode==211 || pdgcode==2212) ) continue;

	 AliAODMCParticle* MCmother;
	 AliAODMCParticle* MCmother2;
	 AliAODMCParticle* MCmother3;

	 if ( MCparticle ){
		 MCmother = (AliAODMCParticle*) fMC->GetTrack(MCparticle->GetMother());
		 if ( MCmother ){
			 MCmother2 = (AliAODMCParticle*) fMC->GetTrack(MCmother->GetMother());
			 if ( MCmother2 ){
				 MCmother3 = (AliAODMCParticle*) fMC->GetTrack(MCmother2->GetMother());
			 }
		 }
	 }

	 int p_pdgcode = 0;
	 int p2_pdgcode = 0;
	 int p3_pdgcode = 0;

	 if ( MCmother ){
		 p_pdgcode = abs(MCmother->GetPdgCode());
		 if ( MCmother2 ){
			 p2_pdgcode = abs(MCmother2->GetPdgCode());
			 if ( MCmother3 ){
				 p3_pdgcode = abs(MCmother3->GetPdgCode());
			 }
		 }
	 }

	 if ( p2_pdgcode==4132 || p3_pdgcode==4132 ){
		 if ( pdgcode==211 ){
			 if ( p_pdgcode==3312 ){
				 fHistos->FillTH1("hTruePion1",MCparticle->Pt());
			 }else if ( p_pdgcode==3122 ){
				 fHistos->FillTH1("hTruePion2",MCparticle->Pt());
			 }
		 }else if ( pdgcode==2212 ){
			 if ( p_pdgcode==3122 ){
				 fHistos->FillTH1("hTrueProton3",MCparticle->Pt());
			 }
		 }
	 }

	 //cout << p_pdgcode << " " << pdgcode << endl;
 }

 auto nCascs  = fEvt->GetNumberOfCascades();
 auto nTracks = fEvt->GetNumberOfTracks();
 int nTracksCut = 0;

 for (Int_t itrk = 0; itrk<nTracks; itrk++){ //Filling histogram
	 AliAODTrack *trk = (AliAODTrack*) fEvt->GetTrack(itrk);
	 if(!trk) continue;
	 if(!(FilterTrack(trk,100))) continue;
	 Double_t mass; Double_t mass_ss;
	 Bool_t DrawElectron = FilterElectron(trk,mass,mass_ss,0,0,100);
 }

 for (Int_t itrk = 0; itrk<nTracks; itrk++){ //Filling histogram
	 AliAODTrack *trk = (AliAODTrack*) fEvt->GetTrack(itrk);
	 if(!trk) continue;
	 if(!(trk->TestFilterMask(AliAODTrack::kTrkGlobalNoDCA))) continue;   //filterbit 4

	 int trk_label = trk->GetLabel();
	 if ( trk_label<=0 ) continue;

	 AliAODMCParticle* mctrk = (AliAODMCParticle*) fMC->GetTrack(trk_label);

	 if ( fabs(mctrk->Eta())>0.9 ) continue;

	 int pdgcode = abs(mctrk->GetPdgCode());

	 if ( mctrk->IsPrimary() ){
		 if ( pdgcode==211 ) fHistos->FillTH1("hRecoPion0",mctrk->Pt());
		 continue;
	 }

	 if ( !(pdgcode==211 || pdgcode==2212) ) continue;

	 AliAODMCParticle* MCmother;
	 AliAODMCParticle* MCmother2;
	 AliAODMCParticle* MCmother3;

	 if ( mctrk ){
		 MCmother = (AliAODMCParticle*) fMC->GetTrack(mctrk->GetMother());
		 if ( MCmother ){
			 MCmother2 = (AliAODMCParticle*) fMC->GetTrack(MCmother->GetMother());
			 if ( MCmother2 ){
				 MCmother3 = (AliAODMCParticle*) fMC->GetTrack(MCmother2->GetMother());
			 }
		 }
	 }

	 int p_pdgcode = 0;
	 int p2_pdgcode = 0;
	 int p3_pdgcode = 0;

	 if ( MCmother ){
		 p_pdgcode = abs(MCmother->GetPdgCode());
		 if ( MCmother2 ){
			 p2_pdgcode = abs(MCmother2->GetPdgCode());
			 if ( MCmother3 ){
				 p3_pdgcode = abs(MCmother3->GetPdgCode());
			 }
		 }
	 }

	 //cout << pdgcode << " " << p_pdgcode << " " << p2_pdgcode << " " << p3_pdgcode << endl;

	 if ( p2_pdgcode==4132 || p3_pdgcode==4132 ){
		 if ( pdgcode==211 ){
			 if ( p_pdgcode==3312 ){
				 fHistos->FillTH1("hRecoPion1",mctrk->Pt());
			 }else if ( p_pdgcode==3122 ){
				 fHistos->FillTH1("hRecoPion2",mctrk->Pt());
			 }
		 }else if ( pdgcode==2212 ){
			 if ( p_pdgcode==3122 ){
				 fHistos->FillTH1("hRecoProton3",mctrk->Pt());
			 }
		 }
	 }

 }

 //cout << "nMCTracks: " << nMCTracksCut << ", nTracks: " << nTracksCut << endl;
 //cout << "nMCTracks: " << nMCTracks << ", nTracks: " << nTracks << endl;

 fHistos->FillTH1("NumOfCascs",nCascs);
 fHistos->FillTH2("NumOfTrkGenReco",nMCTracksCut,nTracksCut);

 for (int icasc = 0; icasc<nCascs; icasc++ ){
   AliAODcascade *casc = ((AliAODEvent*)fEvt)->GetCascade(icasc);

   if(!casc) continue;
   if(!(casc->GetSecondaryVtx())) continue;
   if(!(casc->GetDecayVertexXi())) continue;
//   Int_t tmp = MatchToMCXi(casc);
   if(!FilterCascade(casc)) continue; //cascade cut
//t_t tmp = MatchToMCXic0(casc);
//cout << "MCXic0 : " <<tmp << "---------------------------------------------------------------------------" << endl;

   for (Int_t itrk = 0; itrk<nTracks; itrk++){
     AliAODTrack *trk = (AliAODTrack*) fEvt->GetTrack(itrk);

     if(!trk) continue;
     //if(IsMC) CheckXic0Info(trk,casc);
     if(!(FilterTrack(trk,1))) continue;  //track cut
     FillPairEleXi(casc, trk);
   }
 }


 PostData(1, fHistos->GetListOfHistograms());
 PostData(2, fTrackCuts);
 PostData(3, fMCCutTree);
 PostData(4, fPaireXiTree);
 PostData(5, fMCTree);
 PostData(6, fEventTree);
 PostData(7, fMCeTree);
 PostData(8, fCounter);

 return;
}

void AliAnalysisTaskSEXic0SemileptonicNew2::CheckXic0Info(AliAODTrack *trk, AliAODcascade *casc){
  Int_t MCXic0lab = MatchToMCXic0(casc, trk);
  if(MCXic0lab==-1) return;
    AliAODTrack *pion =  (AliAODTrack*)(casc->GetDaughter(0));  //positive
    AliAODTrack *proton =  (AliAODTrack*)(casc->GetDaughter(1));  //negative
    AliAODTrack *b_pion =  (AliAODTrack*)(casc->GetDecayVertexXi()->GetDaughter(0));

    if(!pion||!proton||!b_pion) return;

    if(pion->Charge()<0 && proton->Charge()>0) {
      pion = (AliAODTrack*) casc->GetDaughter(1);
      proton = (AliAODTrack*) casc->GetDaughter(0);
    }

    Bool_t isparticle = kTRUE;
    if(casc->ChargeXi()>0) isparticle = kFALSE;

    const AliVVertex* Vtx = fEvt->GetPrimaryVertex();
    Double_t primvert_2[3];
    Vtx->GetXYZ(primvert_2);
    Double_t mxiPDG =  TDatabasePDG::Instance()->GetParticle(3312)->Mass();
    Double_t ptotxi = TMath::Sqrt(pow(casc->MomXiX(),2)+pow(casc->MomXiY(),2)+pow(casc->MomXiZ(),2));
    Double_t CascDecayLength = casc->DecayLengthXi(primvert_2[0],primvert_2[1],primvert_2[2])*mxiPDG/ptotxi;
    Double_t lPosXi[3];
    lPosXi[0] = casc->DecayVertexXiX();
    lPosXi[1] = casc->DecayVertexXiY();
    lPosXi[2] = casc->DecayVertexXiZ();
    Double_t decayvertXi = TMath::Sqrt(lPosXi[0]*lPosXi[0]+lPosXi[1]*lPosXi[1]);
    Double_t lPosV0[3];
    lPosV0[0] = casc->DecayVertexV0X();
    lPosV0[1] = casc->DecayVertexV0Y();
    lPosV0[2] = casc->DecayVertexV0Z();
    Double_t decayvertV0 = TMath::Sqrt(lPosV0[0]*lPosV0[0]+lPosV0[1]*lPosV0[1]);

    Double_t lV0CosineOfPointingAngleXi = casc->CosPointingAngle(lPosXi);

    for(Int_t i=0; i<32; i++) fMCCutTreeVariable[i] = -9999.;
    fMCCutTreeVariable[ 0] = trk->GetTPCNcls();
    fMCCutTreeVariable[ 1] = trk->GetTPCsignalN();
    fMCCutTreeVariable[ 2] = trk->GetITSNcls();
    fMCCutTreeVariable[ 3] = trk->GetTPCClusterInfo(2,1);
    fMCCutTreeVariable[ 4] = fPIDResponse->NumberOfSigmasTOF(trk,AliPID::kElectron);
    fMCCutTreeVariable[ 5] = fPIDResponse->NumberOfSigmasTPC(trk,AliPID::kElectron);
    fMCCutTreeVariable[ 6] = pion->GetTPCNcls();
    fMCCutTreeVariable[ 7] = proton->GetTPCNcls();
    fMCCutTreeVariable[ 8] = b_pion->GetTPCNcls();
    fMCCutTreeVariable[ 9] = pion->GetTPCsignalN();
    fMCCutTreeVariable[10] = proton->GetTPCsignalN();
    fMCCutTreeVariable[11] = b_pion->GetTPCsignalN();
    fMCCutTreeVariable[12] = pion->GetTPCClusterInfo(2,1);
    fMCCutTreeVariable[13] = proton->GetTPCClusterInfo(2,1);
    fMCCutTreeVariable[14] = b_pion->GetTPCClusterInfo(2,1);
    fMCCutTreeVariable[15] = fPIDResponse->NumberOfSigmasTPC(proton,AliPID::kProton);
    fMCCutTreeVariable[16] = fPIDResponse->NumberOfSigmasTPC(pion,AliPID::kPion);
    fMCCutTreeVariable[17] = fPIDResponse->NumberOfSigmasTPC(pion,AliPID::kProton);
    fMCCutTreeVariable[18] = fPIDResponse->NumberOfSigmasTPC(proton,AliPID::kPion);
    fMCCutTreeVariable[19] = fPIDResponse->NumberOfSigmasTPC(b_pion,AliPID::kPion);
    fMCCutTreeVariable[20] = casc->MassXi();
    fMCCutTreeVariable[21] = decayvertV0;
    fMCCutTreeVariable[22] = casc->DcaBachToPrimVertex();
    fMCCutTreeVariable[23] = casc->DcaV0ToPrimVertex();
    fMCCutTreeVariable[24] = lV0CosineOfPointingAngleXi;
    fMCCutTreeVariable[25] = decayvertXi;
    fMCCutTreeVariable[26] = casc->DcaPosToPrimVertex();
    fMCCutTreeVariable[27] = casc->DcaNegToPrimVertex();
    fMCCutTreeVariable[28] = isparticle;

    AliAODMCParticle* MCXic0= (AliAODMCParticle*) fMC->GetTrack(MCXic0lab);
    AliAODMCParticle *MCe = 0;
    AliAODMCParticle *MCcasc = 0;
    Bool_t e_flag = kFALSE;
    Bool_t xi_flag = kFALSE;
    for(Int_t idau=MCXic0->GetDaughterFirst(); idau<MCXic0->GetDaughterLast()+1; idau++){
      if(idau<0) break;
      AliAODMCParticle* mcdau = (AliAODMCParticle*) fMC->GetTrack(idau);
      if(!mcdau) continue;
      if(TMath::Abs(mcdau->GetPdgCode())==11) { e_flag = kTRUE; MCe = mcdau; }
      if(TMath::Abs(mcdau->GetPdgCode())==3312) { xi_flag = kTRUE; MCcasc = mcdau; }
    }
    fMCCutTreeVariable[29] = MCXic0->Pt();

      Int_t motherxic = MCXic0->GetMother();
      if(motherxic>0 && e_flag && xi_flag){
        AliAODMCParticle* MCMother = (AliAODMCParticle*) fMC->GetTrack(motherxic);
        if(((TMath::Abs(MCMother->GetPdgCode()))==5132) || ((TMath::Abs(MCMother->GetPdgCode()))==5232)) fMCCutTreeVariable[30] = 1;
        else fMCCutTreeVariable[31] = 1;
      }

    fMCCutTree->Fill();
  return;
}

///////////////////////////////Filtering///////////////////////////////////
Bool_t AliAnalysisTaskSEXic0SemileptonicNew2::FilterTrack(AliAODTrack * track, Int_t FillHistosFlag){
  if(!track) return kFALSE;

  Bool_t b_flag = kFALSE;
  Bool_t c_flag = kFALSE;

	bool bMC_e = false;
	bool bMCXib = false, bMCXic = false;
	float XicY = -9999, XicPt = -9999;
	float eY = -9999, ePt = -9999, eCharge = -9999;

  if(IsMC){
    Int_t e_label = track->GetLabel();
    if(e_label>0){
      AliAODMCParticle* mc_e = (AliAODMCParticle*) fMC->GetTrack(e_label);
      Int_t mother_e_label = mc_e->GetMother();
      if(mother_e_label>0){
        AliAODMCParticle* mcXic0 = (AliAODMCParticle*) fMC->GetTrack(mother_e_label);
        if(TMath::Abs(mcXic0->GetPdgCode())==4132){

					//cout << "FilterTrack PDG: " << mc_e->GetPdgCode() << endl;
					if ( abs(mc_e->GetPdgCode())==11 ){
						bMC_e = true;

						eY = mc_e->Y();
						ePt = mc_e->Pt();
						eCharge = mc_e->Charge();
					}

					XicY = mcXic0->Y();
					XicPt = mcXic0->Pt();

          Int_t lab_mother_of_Xic0 =  mcXic0->GetMother();
          if(lab_mother_of_Xic0>0){
            AliAODMCParticle* mother_of_Xic0 = (AliAODMCParticle*) fMC->GetTrack(lab_mother_of_Xic0);
            if((TMath::Abs(mother_of_Xic0->GetPdgCode())==5132) || (TMath::Abs(mother_of_Xic0->GetPdgCode())==5232)) b_flag = kTRUE;
            else c_flag = kTRUE;
          }
        }
      }
    }
  }


  if(IsMC && FillHistosFlag==100 && c_flag) fHistos->FillTH1("e_c_flag","all",1);
  if(IsMC && FillHistosFlag==100 && b_flag) fHistos->FillTH1("e_b_flag","all",1);

	if ( FillHistosFlag==100 && bMC_e && fabs(XicY)<0.5 ){
		if ( c_flag ){
			fHistos->FillTH2("hTrueEeCharmSPD0",XicPt,fEventTreeVariable[5]);
		}else if ( b_flag ){
			fHistos->FillTH2("hTrueEeBottomSPD0",XicPt,fEventTreeVariable[5]);
		}

	}

  if(!((AliAODTrack*)track)->TestFilterMask(AliAODTrack::kTrkGlobalNoDCA)) return kFALSE;   //filterbit 4
  if(IsMC && FillHistosFlag==100 && c_flag) fHistos->FillTH1("e_c_flag","Filterbit_c",1);
  if(IsMC && FillHistosFlag==100 && b_flag) fHistos->FillTH1("e_b_flag","Filterbit_b",1);

	if ( FillHistosFlag==100 && bMC_e && fabs(XicY)<0.5 ){
		if ( c_flag ){
			fHistos->FillTH2("hTrueEeCharmSPD1",XicPt,fEventTreeVariable[5]);
		}else if ( b_flag ){
			fHistos->FillTH2("hTrueEeBottomSPD1",XicPt,fEventTreeVariable[5]);
		}
	}

  AliAODTrack *aodt = dynamic_cast<AliAODTrack*>(track);
  const AliVVertex* Vtx = fEvt->GetPrimaryVertex();
  Double_t pos[3]; Vtx->GetXYZ(pos);
  Double_t cov[3]; Vtx->GetCovarianceMatrix(cov);
  const AliESDVertex vESD(pos,cov,100.,100);
  AliESDtrack copyTrack(aodt);
    copyTrack.SetTPCClusterMap(aodt->GetTPCClusterMap());
    copyTrack.SetTPCSharedMap(aodt->GetTPCSharedMap());
    copyTrack.SetTPCPointsF(aodt->GetTPCNclsF());
    copyTrack.RelateToVertex(&vESD,0.,3.);

	if ( FillHistosFlag==100 && bMC_e && fabs(XicY)<0.5 && XicPt>2 && XicPt<5 ){
		Float_t b[2], bCov[3];
		copyTrack.GetImpactParameters(b,bCov);
		Float_t dcaToVertex = sqrt(b[0]*b[0]/1.0/1.0 + b[1]*b[1]/2.0/2.0); 

		fHistos->FillTH2("hTrueEeSPD1DCA",fEventTreeVariable[5],dcaToVertex);
	}

	if ( FillHistosFlag==100 && bMC_e && fabs(XicY)<0.5 ){
		if ( fTrackCutsCase5->IsSelected(&copyTrack) ){
			fHistos->FillTH2("hTrueEeSPD1Case5",XicPt,fEventTreeVariable[5]);
			fHistos->FillTH2("hTrueEeSPD1Case4",XicPt,fEventTreeVariable[5]);
			fHistos->FillTH2("hTrueEeSPD1Case3",XicPt,fEventTreeVariable[5]);
			fHistos->FillTH2("hTrueEeSPD1Case2",XicPt,fEventTreeVariable[5]);
			fHistos->FillTH2("hTrueEeSPD1Case1",XicPt,fEventTreeVariable[5]);
			fHistos->FillTH2("hTrueEeSPD1Case0",XicPt,fEventTreeVariable[5]);
		}else if ( fTrackCutsCase4->IsSelected(&copyTrack) ){
			fHistos->FillTH2("hTrueEeSPD1Case4",XicPt,fEventTreeVariable[5]);
			fHistos->FillTH2("hTrueEeSPD1Case3",XicPt,fEventTreeVariable[5]);
			fHistos->FillTH2("hTrueEeSPD1Case2",XicPt,fEventTreeVariable[5]);
			fHistos->FillTH2("hTrueEeSPD1Case1",XicPt,fEventTreeVariable[5]);
			fHistos->FillTH2("hTrueEeSPD1Case0",XicPt,fEventTreeVariable[5]);
		}else if ( fTrackCutsCase3->IsSelected(&copyTrack) ){
			fHistos->FillTH2("hTrueEeSPD1Case3",XicPt,fEventTreeVariable[5]);
			fHistos->FillTH2("hTrueEeSPD1Case2",XicPt,fEventTreeVariable[5]);
			fHistos->FillTH2("hTrueEeSPD1Case1",XicPt,fEventTreeVariable[5]);
			fHistos->FillTH2("hTrueEeSPD1Case0",XicPt,fEventTreeVariable[5]);
		}else if ( fTrackCutsCase2->IsSelected(&copyTrack) ){
			fHistos->FillTH2("hTrueEeSPD1Case2",XicPt,fEventTreeVariable[5]);
			fHistos->FillTH2("hTrueEeSPD1Case1",XicPt,fEventTreeVariable[5]);
			fHistos->FillTH2("hTrueEeSPD1Case0",XicPt,fEventTreeVariable[5]);
		}else if ( fTrackCutsCase1->IsSelected(&copyTrack) ){
			fHistos->FillTH2("hTrueEeSPD1Case1",XicPt,fEventTreeVariable[5]);
			fHistos->FillTH2("hTrueEeSPD1Case0",XicPt,fEventTreeVariable[5]);
		}else if ( fTrackCutsCase0->IsSelected(&copyTrack) ){
			fHistos->FillTH2("hTrueEeSPD1Case0",XicPt,fEventTreeVariable[5]);
		}
	}

	if ( IsMC && FillHistosFlag==100 && bMC_e ){
		for(Int_t i=0; i<10; i++) fMCeTreeVariable[i] = -9999.;

		unsigned char ITSClusterMap = track->GetITSClusterMap();
		int ITSClusterMap2 = (int)ITSClusterMap;

		fMCeTreeVariable[0] = track->Pt();
		fMCeTreeVariable[1] = track->Eta();
		fMCeTreeVariable[2] = ePt;
		fMCeTreeVariable[3] = eY;
		fMCeTreeVariable[4] = eCharge;
		fMCeTreeVariable[5] = XicPt;
		fMCeTreeVariable[6] = XicY;
		fMCeTreeVariable[7] = (int)ITSClusterMap;
		fMCeTreeVariable[8] = fEventTreeVariable[5];
		fMCeTreeVariable[9] = fTrackCuts->IsSelected(&copyTrack);

		//cout << "electron " << eY << " " << ePt << endl;

		//cout << "###" << track->GetITSClusterMap() << " " << fMCeTreeVariable[7] << endl;

		/*
		cout << "char ";
		for (int ii=0; ii<6; ii++){
			cout 
				<< (ITSClusterMap & (1<<ii))
				<< " ";
		}
		cout << endl;

		cout << "int ";
		for (int ii=0; ii<6; ii++){
			cout 
				<< (ITSClusterMap2 & (1<<ii))
				<< " ";
		}
		cout << endl;
		*/


		fMCeTree->Fill();
	}

  if(!(fTrackCuts->IsSelected(&copyTrack))) return kFALSE;
  /*if(track->GetTPCNclsF()>0){
	  Float_t tpcratio = (Float_t)track->GetTPCncls()/(Float_t)track->GetTPCNclsF();
	  if(tpcratio<fProdTrackTPCNclsRatioMin) return kFALSE;  //ratio of findable cluster
  }*/
  if(track->GetTPCsignalN() < fSetProdTrackTPCNclsPID) return kFALSE;
	if ( FillHistosFlag==100 && bMC_e && fabs(XicY)<0.5 ){
		fHistos->FillTH2("hTrueEeSPD1Case6",XicPt,fEventTreeVariable[5]);

	}

  if(IsMC && FillHistosFlag==100 && c_flag) fHistos->FillTH1("e_c_flag","TrackCut_c",1);
  if(IsMC && FillHistosFlag==100 && b_flag) fHistos->FillTH1("e_b_flag","TrackCut_b",1);

	if ( FillHistosFlag==100 && bMC_e && fabs(XicY)<0.5 ){
		if ( c_flag ){
			fHistos->FillTH2("hTrueEeCharmSPD2",XicPt,fEventTreeVariable[5]);
		}else if ( b_flag ){
			fHistos->FillTH2("hTrueEeBottomSPD2",XicPt,fEventTreeVariable[5]);
		}
	}

  if (track->Pt()<fPtCut) return kFALSE;  //pt cut
  if(IsMC && FillHistosFlag==100 && c_flag) fHistos->FillTH1("e_c_flag","pT_c",1);
  if(IsMC && FillHistosFlag==100 && b_flag) fHistos->FillTH1("e_b_flag","pT_b",1);

  if (fabs(track->Eta())>fEtaCut) return kFALSE;  //eta cut
  if(IsMC && FillHistosFlag==100 && c_flag) fHistos->FillTH1("e_c_flag","eta_c",1);
  if(IsMC && FillHistosFlag==100 && b_flag) fHistos->FillTH1("e_b_flag","eta_b",1);

	if ( FillHistosFlag==100 && bMC_e && fabs(XicY)<0.5 ){
		if ( c_flag ){
			fHistos->FillTH2("hTrueEeCharmSPD3",XicPt,fEventTreeVariable[5]);
		}else if ( b_flag ){
			fHistos->FillTH2("hTrueEeBottomSPD3",XicPt,fEventTreeVariable[5]);
		}
	}

  return kTRUE;
}

Bool_t AliAnalysisTaskSEXic0SemileptonicNew2::FilterElectron(AliAODTrack *etrk, Double_t &minmass, Double_t &minmass_ss, Bool_t IsSameSign, Bool_t IsLoose, Int_t FillHistosFlag){
  Double_t nSigmaTOF = -9999.;
  Double_t nSigmaTPC = -9999.;
  minmass = 9999;
  minmass_ss = 9999;
  AliAODcascade *casc = ((AliAODEvent*)fEvt)->GetCascade(1); //tmp cascasde

  Bool_t b_flag = kFALSE;
  Bool_t c_flag = kFALSE;

  if(IsMC){
    Int_t e_label = etrk->GetLabel();
    if(e_label>0){
      AliAODMCParticle* mc_e = (AliAODMCParticle*) fMC->GetTrack(e_label);
      Int_t mother_e_label = mc_e->GetMother();
      if(mother_e_label>0){
        AliAODMCParticle* mcXic0 = (AliAODMCParticle*) fMC->GetTrack(mother_e_label);
        if(TMath::Abs(mcXic0->GetPdgCode())==4132){
          Int_t lab_mother_of_Xic0 =  mcXic0->GetMother();
          if(lab_mother_of_Xic0>0){
            AliAODMCParticle* mother_of_Xic0 = (AliAODMCParticle*) fMC->GetTrack(lab_mother_of_Xic0);
            if((TMath::Abs(mother_of_Xic0->GetPdgCode())==5132) || (TMath::Abs(mother_of_Xic0->GetPdgCode())==5232)) b_flag = kTRUE;
            else c_flag = kTRUE;
          }
        }
      }
    }
  }

  nSigmaTOF = fPIDResponse->NumberOfSigmasTOF(etrk,AliPID::kElectron);

  if((FillHistosFlag==100) && StandardCutFlag(etrk,casc,1,0,0,0)) fHistos->FillTH2("nSigmaTOFvsPt",etrk->Pt(),nSigmaTOF);
  if(fabs(fPIDResponse->NumberOfSigmasTOF(etrk,AliPID::kElectron))>3) return kFALSE;

  if(IsMC && FillHistosFlag==100 && c_flag) fHistos->FillTH1("e_c_flag","TOF_c",1);
  if(IsMC && FillHistosFlag==100 && b_flag) fHistos->FillTH1("e_b_flag","TOF_b",1);

  Double_t e_pt = etrk->Pt();
  Double_t cut_tpc = -4.3+(1.17*e_pt)-(0.094*e_pt*e_pt);
  nSigmaTPC = fPIDResponse->NumberOfSigmasTPC(etrk,AliPID::kElectron);

  if((FillHistosFlag==100) && StandardCutFlag(etrk,casc,1,0,0,0)) fHistos->FillTH2("nSigmaTPCvsPt",etrk->Pt(),nSigmaTPC);
  if(fPIDResponse->NumberOfSigmasTPC(etrk,AliPID::kElectron)>3) return kFALSE;
  if(fPIDResponse->NumberOfSigmasTPC(etrk,AliPID::kElectron)<cut_tpc) return kFALSE;
  if(e_pt>5 && fPIDResponse->NumberOfSigmasTPC(etrk,AliPID::kElectron)<(-4.3+(1.17*5)-(0.094*5*5))) return kFALSE;
  if(IsMC && FillHistosFlag==100 && c_flag && StandardCutFlag(etrk,casc,1,1,0,0)) fHistos->FillTH1("e_c_flag","TPC_c",1);
  if(IsMC && FillHistosFlag==100 && b_flag && StandardCutFlag(etrk,casc,1,1,0,0)) fHistos->FillTH1("e_b_flag","TPC_b",1);

  if((FillHistosFlag==100) && StandardCutFlag(etrk,casc,1,1,0,0)) fHistos->FillTH1("NumOfe",fRunNumber-fRunOffset);

  Int_t trkid = etrk->GetID();
  Double_t px1 = etrk->Px();
  Double_t py1 = etrk->Py();
  Double_t pz1 = etrk->Pz();
  Double_t fE1 = sqrt(px1*px1+py1*py1+pz1*pz1+0.000510998928*0.000510998928);

  Double_t Pt = 9999.;
  Double_t Pt_ss = 9999.;

  auto nTracks = fEvt->GetNumberOfTracks();

  for(Int_t it=0; it<nTracks; it++){
    AliAODTrack *trk = (AliAODTrack*) fEvt->GetTrack(it); //////trk = loose cut
    if(!trk) continue;
    if(!((AliAODTrack*)trk)->TestFilterMask(AliAODTrack::kTrkGlobalNoDCA)) continue;
    if(fabs(fPIDResponse->NumberOfSigmasTPC(trk,AliPID::kElectron))>5) continue;

    Int_t trkid2 = trk->GetID();
    if(fabs(trkid)==fabs(trkid2)) continue;

    Double_t px2 = trk->Px();
    Double_t py2 = trk->Py();
    Double_t pz2 = trk->Pz();
    Double_t fE2 = sqrt(px2*px2+py2*py2+pz2*pz2+0.000510998928*0.000510998928);
    Double_t mass = sqrt(pow(fE1+fE2,2)-pow(px1+px2,2)-pow(py1+py2,2)-pow(pz1+pz2,2));
    Double_t tmp_pt = sqrt(pow(px1+px2,2)+pow(py1+py2,2));

    if((FillHistosFlag==100) && StandardCutFlag(etrk,casc,1,1,0,0) && trk->Charge()*etrk->Charge()>0) fHistos->FillTH1("SSElectronPair",mass);
    if((FillHistosFlag==100) && StandardCutFlag(etrk,casc,1,1,0,0) && trk->Charge()*etrk->Charge()<0) fHistos->FillTH1("DSElectronPair",mass);

    if(trk->Charge()*etrk->Charge()>0 && mass<minmass_ss) { minmass_ss = mass; Pt_ss = tmp_pt; }
    if(trk->Charge()*etrk->Charge()<0 && mass<minmass) { minmass = mass; Pt = tmp_pt; }
  }

  if(IsMC && (FillHistosFlag==100) && c_flag && minmass>0.05 && StandardCutFlag(etrk,casc,1,1,0,0)) fHistos->FillTH1("e_c_flag","prefilter_c",1);
  if(IsMC && (FillHistosFlag==100) && b_flag && minmass>0.05 && StandardCutFlag(etrk,casc,1,1,0,0)) fHistos->FillTH1("e_b_flag","prefilter_b",1);

  if(!IsLoose && !IsSameSign) return kTRUE; ///0.05 is Conversion Mass Max.
  if(!IsLoose && IsSameSign) return kTRUE;
  if(IsLoose) return kTRUE;

  return kFALSE;
}

Bool_t AliAnalysisTaskSEXic0SemileptonicNew2::FilterCascade(AliAODcascade *casc){
  Bool_t isparticle = kTRUE;
  if(casc->ChargeXi()>0) isparticle = kFALSE;

  AliAODTrack *pion =  (AliAODTrack*)(casc->GetDaughter(0));  //positive
  AliAODTrack *proton =  (AliAODTrack*)(casc->GetDaughter(1));  //negative
  AliAODTrack *b_pion =  (AliAODTrack*)(casc->GetDecayVertexXi()->GetDaughter(0));

	if(!pion||!proton||!b_pion) return kFALSE;

	if(pion->Charge()<0 && proton->Charge()>0) {
		pion = (AliAODTrack*) casc->GetDaughter(1);
		proton = (AliAODTrack*) casc->GetDaughter(0);
	}

  Double_t pxxi = casc->MomXiX();
  Double_t pyxi = casc->MomXiY();
  Double_t ptxi = sqrt(pxxi*pxxi+pyxi*pyxi);
  if(ptxi<0.|| ptxi>9999.) return kFALSE;

  Double_t momegaPDG =  TDatabasePDG::Instance()->GetParticle(3334)->Mass();
  Double_t massOmega = casc->MassOmega();
  if(TMath::Abs(massOmega-momegaPDG)<0.0) return kFALSE;

  /*if(pion->GetTPCClusterInfo(2,1)<fNClusterTPCMinXi) return kFALSE;
  if(proton->GetTPCClusterInfo(2,1)<fNClusterTPCMinXi) return kFALSE;
  if(b_pion->GetTPCClusterInfo(2,1)<fNClusterTPCMinXi) return kFALSE;*/

  if(isparticle){
    if(fabs(fPIDResponse->NumberOfSigmasTPC(pion,AliPID::kProton))>4) return kFALSE; //4
    if(fabs(fPIDResponse->NumberOfSigmasTPC(proton,AliPID::kPion))>4) return kFALSE; //4
    if(fabs(fPIDResponse->NumberOfSigmasTPC(b_pion,AliPID::kPion))>4) return kFALSE; //4
  }else{
    if(fabs(fPIDResponse->NumberOfSigmasTPC(proton,AliPID::kProton))>4) return kFALSE; //4
    if(fabs(fPIDResponse->NumberOfSigmasTPC(pion,AliPID::kPion))>4) return kFALSE; //4
    if(fabs(fPIDResponse->NumberOfSigmasTPC(b_pion,AliPID::kPion))>4) return kFALSE; //4
  }

  Double_t mLPDG =  TDatabasePDG::Instance()->GetParticle(3122)->Mass();
  Double_t mxiPDG =  TDatabasePDG::Instance()->GetParticle(3312)->Mass();
  Double_t massLambda = casc->MassLambda();
  Double_t massAntiLambda = casc->MassAntiLambda();
  Double_t massXi = casc->MassXi();
  if(TMath::Abs(massLambda-mLPDG)>MassTolLambda && TMath::Abs(massAntiLambda-mLPDG)>MassTolLambda){
		return kFALSE;
	}

  Double_t lPosXi[3];
  lPosXi[0] = casc->DecayVertexXiX();
  lPosXi[1] = casc->DecayVertexXiY();
  lPosXi[2] = casc->DecayVertexXiZ();
  Double_t decayvertXi = TMath::Sqrt(lPosXi[0]*lPosXi[0]+lPosXi[1]*lPosXi[1]);
  Double_t lPosV0[3];
  lPosV0[0] = casc->DecayVertexV0X();
  lPosV0[1] = casc->DecayVertexV0Y();
  lPosV0[2] = casc->DecayVertexV0Z();
  Double_t decayvertV0 = TMath::Sqrt(lPosV0[0]*lPosV0[0]+lPosV0[1]*lPosV0[1]);
  if(decayvertV0>9999.) return kFALSE;
  if(decayvertXi>9999.) return kFALSE;

  const AliVVertex* Vtx = fEvt->GetPrimaryVertex();
  Double_t primvert[3];
  Vtx->GetXYZ(primvert);
  Double_t ptotxi = TMath::Sqrt(pow(casc->MomXiX(),2)+pow(casc->MomXiY(),2)+pow(casc->MomXiZ(),2));
  Double_t properdl = casc->DecayLengthXi(primvert[0],primvert[1],primvert[2])*mxiPDG/ptotxi;
  if(properdl>9999.) return kFALSE;

	//MC
	bool bMC_e = false, bMC_Xi = false;
	bool bMCXib = false, bMCXic = false;
	float XicY = -9999, XicPt = -9999;
	
	if ( IsMC ){
		Int_t Xic0_label = MatchToMCXic0(casc);
		if ( Xic0_label!=-1 ){
			AliAODMCParticle* mcXic0 = (AliAODMCParticle*) fMC->GetTrack(Xic0_label);

			for (Int_t idau=mcXic0->GetDaughterFirst(); idau<mcXic0->GetDaughterLast()+1; idau++){
				if( idau<0 ) break;
				AliAODMCParticle* mcdau = (AliAODMCParticle*) fMC->GetTrack(idau);
				if( !mcdau ) continue;
				if( TMath::Abs(mcdau->GetPdgCode())==11 ) bMC_e = kTRUE;
				if( TMath::Abs(mcdau->GetPdgCode())==3312 ) bMC_Xi = kTRUE;
			}//idau

			if( bMC_e && bMC_Xi ){
				XicY = mcXic0->Y();
				XicPt = mcXic0->Pt();

				Int_t Xic0_moter_label =  mcXic0->GetMother();

				if( Xic0_moter_label>0 ){
					AliAODMCParticle* mother_of_Xic0 = (AliAODMCParticle*)fMC->GetTrack(Xic0_moter_label);
					if( ((TMath::Abs(mother_of_Xic0->GetPdgCode()))==5132) || ((TMath::Abs(mother_of_Xic0->GetPdgCode()))==5232) ) bMCXib = kTRUE;
					else bMCXic = kTRUE;
				} //Xic0_mother_label
			}//bMC_e && bMC_Xi

		}//Xic0_label
	}//IsMC

	if ( fabs(XicY)<0.5 ){
		if ( bMCXic ){
			fHistos->FillTH2("hTrueXiCharmSPD0",XicPt,fEventTreeVariable[5]);
		}else if ( bMCXib ){
			fHistos->FillTH2("hTrueXiBottomSPD0",XicPt,fEventTreeVariable[5]);
		}
	}

  Double_t lDcaXiDaughters = casc->DcaXiDaughters();
  Double_t lDcaV0Daughters = casc->DcaV0Daughters();
  if(lDcaXiDaughters > 1.68) return kFALSE;
  if(lDcaV0Daughters > 1.68) return kFALSE;

	if ( fabs(XicY)<0.5 ){
		if ( bMCXic ){
			fHistos->FillTH2("hTrueXiCharmSPD1",XicPt,fEventTreeVariable[5]);
		}else if ( bMCXib ){
			fHistos->FillTH2("hTrueXiBottomSPD1",XicPt,fEventTreeVariable[5]);
		}
	}

  FillXiHistFromPromptNonPrompt(IsMC,casc);

  Double_t lDcaPosToPrimVertex = casc->DcaPosToPrimVertex();
  Double_t lDcaNegToPrimVertex = casc->DcaNegToPrimVertex();
  Double_t lDcaBachToPrimVertex = casc->DcaBachToPrimVertex();
  Double_t lDcaV0ToPrimVertex = casc->DcaV0ToPrimVertex();
  Double_t lXiCosineOfPointingAngle = casc->CosPointingAngleXi(primvert[0],primvert[1],primvert[2]);
  Double_t lV0CosineOfPointingAngleXi = casc->CosPointingAngle(lPosXi);

  if(isparticle){
    if(lDcaPosToPrimVertex < DCAV0PrToPrimVertexMin) return kFALSE;
    if(lDcaNegToPrimVertex < DCAV0PiToPrimVertexMin) return kFALSE;
  }else{
    if(lDcaPosToPrimVertex < DCAV0PiToPrimVertexMin) return kFALSE;
    if(lDcaNegToPrimVertex < DCAV0PrToPrimVertexMin) return kFALSE;
  }

	if ( fabs(XicY)<0.5 ){
		if ( bMCXic ){
			fHistos->FillTH2("hTrueXiCharmSPD2",XicPt,fEventTreeVariable[5]);
		}else if ( bMCXib ){
			fHistos->FillTH2("hTrueXiBottomSPD2",XicPt,fEventTreeVariable[5]);
		}
	}

  if(lDcaBachToPrimVertex < DCABachToPrimVertexMin) return kFALSE;
  if(lDcaV0ToPrimVertex < DCAV0ToPrimVertexMin) return kFALSE;

	if ( fabs(XicY)<0.5 ){
		if ( bMCXic ){
			fHistos->FillTH2("hTrueXiCharmSPD3",XicPt,fEventTreeVariable[5]);
		}else if ( bMCXib ){
			fHistos->FillTH2("hTrueXiBottomSPD3",XicPt,fEventTreeVariable[5]);
		}
	}

  if(lXiCosineOfPointingAngle < V0CosineOfPoiningAngleXiMin) return kFALSE;
  if(lV0CosineOfPointingAngleXi < V0CosineOfPoiningAngleXiMin) return kFALSE;

	if ( fabs(XicY)<0.5 ){
		if ( bMCXic ){
			fHistos->FillTH2("hTrueXiCharmSPD4",XicPt,fEventTreeVariable[5]);
		}else if ( bMCXib ){
			fHistos->FillTH2("hTrueXiBottomSPD4",XicPt,fEventTreeVariable[5]);
		}
	}

  if (decayvertV0< DecayLengthV0) return kFALSE;
  if(decayvertXi < CascDecayLengthMin) return kFALSE;

	if ( fabs(XicY)<0.5 ){
		if ( bMCXic ){
			fHistos->FillTH2("hTrueXiCharmSPD5",XicPt,fEventTreeVariable[5]);
		}else if ( bMCXib ){
			fHistos->FillTH2("hTrueXiBottomSPD5",XicPt,fEventTreeVariable[5]);
		}
	}

  if((fabs(massXi-mxiPDG)<0.025) &&StandardCutFlag(pion,casc,0,0,1,1)) fHistos->FillTH1("NumOfXi",fRunNumber-fRunOffset);  //dummy track

  if(StandardCutFlag(pion,casc,0,0,1,1)){
  	Double_t px = casc->MomXiX();
  	Double_t py = casc->MomXiY();
  	fHistos -> FillTH1 ("hXimass_total",casc->MassXi());
  	fHistos -> FillTH1("hXimass",casc->MassXi());
  	fHistos -> FillTH2("hXimassvsPt",casc->MassXi(),sqrt(px*px+py*py));
  }

  if(fabs(massXi-mxiPDG)>MassTolXi) return kFALSE;

	if ( fabs(XicY)<0.5 ){
		if ( bMCXic ){
			fHistos->FillTH2("hTrueXiCharmSPD6",XicPt,fEventTreeVariable[5]);
		}else if ( bMCXib ){
			fHistos->FillTH2("hTrueXiBottomSPD6",XicPt,fEventTreeVariable[5]);
		}
	}

  return kTRUE;
}

void AliAnalysisTaskSEXic0SemileptonicNew2::FillMCXic0(AliAODMCParticle *mcpart){
  if(!(TMath::Abs(mcpart->GetPdgCode())==4132)) return;

  Bool_t e_flag = kFALSE; //electron
  Bool_t xi_flag = kFALSE; //Xi-
  AliAODMCParticle *MCe = 0;
  AliAODMCParticle *MCcasc = 0;
  for(Int_t idau=mcpart->GetDaughterFirst(); idau<mcpart->GetDaughterLast()+1; idau++){
    if(idau<0) break;
    AliAODMCParticle* mcdau = (AliAODMCParticle*) fMC->GetTrack(idau);
    if(!mcdau) continue;
    if(TMath::Abs(mcdau->GetPdgCode())==11) { e_flag = kTRUE; MCe = mcdau; }
    if(TMath::Abs(mcdau->GetPdgCode())==3312) { xi_flag = kTRUE; MCcasc = mcdau; }
  }

  if(e_flag&&xi_flag) fHistos->FillTH1("hMCXic0Decays","e&Xi",1);
  if(!e_flag&&xi_flag) fHistos->FillTH1("hMCXic0Decays","!e&Xi",1);
  if(e_flag&&!xi_flag) fHistos->FillTH1("hMCXic0Decays","e&!Xi",1);
  if(!e_flag&&!xi_flag) fHistos->FillTH1("hMCXic0Decays","!e&!Xi",1);

  Int_t motherxic = mcpart->GetMother();
  if(motherxic>0 && e_flag && xi_flag){
    AliAODMCParticle* MCMother = (AliAODMCParticle*) fMC->GetTrack(motherxic);
    if(((TMath::Abs(MCMother->GetPdgCode()))==5132) || ((TMath::Abs(MCMother->GetPdgCode()))==5232)){  //Xib
      if(MCe->Charge()>0 && MCcasc->Charge()<0 && fabs(mcpart->Y())<0.5){
				fHistos->FillTH2("hXic0PtFromBottom1",mcpart->Pt(),fEventTreeVariable[2]);
				fHistos->FillTH2("hXic0PtFromBottom1SPD",mcpart->Pt(),fEventTreeVariable[5]);
			}
      if(MCe->Charge()<0 && MCcasc->Charge()>0 && fabs(mcpart->Y())<0.5){
				fHistos->FillTH2("hXic0PtFromBottom2",mcpart->Pt(),fEventTreeVariable[2]);
				fHistos->FillTH2("hXic0PtFromBottom2SPD",mcpart->Pt(),fEventTreeVariable[5]);
			}
      fHistos->FillTH1("hNonPromptXicRap",mcpart->Y());
      }
    else{
			if(MCe->Charge()>0 && MCcasc->Charge()<0 && fabs(mcpart->Y())<0.5){
				fHistos->FillTH2("hXic0PtFromCharm1",mcpart->Pt(),fEventTreeVariable[2]);
				fHistos->FillTH2("hXic0PtFromCharm1SPD",mcpart->Pt(),fEventTreeVariable[5]);
			}
			if(MCe->Charge()<0 && MCcasc->Charge()>0 && fabs(mcpart->Y())<0.5){
				fHistos->FillTH2("hXic0PtFromCharm2",mcpart->Pt(),fEventTreeVariable[2]);
				fHistos->FillTH2("hXic0PtFromCharm2SPD",mcpart->Pt(),fEventTreeVariable[5]);
			}
      fHistos->FillTH1("hPromptXicRap",mcpart->Y());
    }
  }

  fHistos->FillTH1("hMCXic0AllRap",mcpart->Pt());

  if(e_flag&&xi_flag){
    Double_t pxe = MCe->Px(); Double_t pye = MCe->Py();
    Double_t pxv = MCcasc->Px(); Double_t pyv = MCcasc->Py();
    Double_t eXi = sqrt(pow(pxe+pxv,2)+pow(pye+pyv,2));
    fHistos->FillTH1("hXicRap",mcpart->Y());
    //fHistos->FillTH1("hXicPtRap",mcpart->Pt(),mcpart->Y());

    if(fabs(mcpart->Y())<0.5){
      fHistos->FillTH2("hMCXic0vsPair",mcpart->Pt(),eXi);
      fHistos->FillTH1("hTruePaireXi",eXi);
      fHistos->FillTH2("hTrueXic0",mcpart->Pt(),fEventTreeVariable[2]);
      fHistos->FillTH1("hTrueXic0_oldbin",mcpart->Pt());
      fHistos->FillTH2("hTrueXic0W",mcpart->Pt(),fEventTreeVariable[2],fWeightFit->Eval(mcpart->Pt()));
      fHistos->FillTH1("hTrueXic0W_oldbin",mcpart->Pt(),fWeightFit->Eval(mcpart->Pt()));
      fHistos->FillTH1("hElectronFromXic0",MCe->Pt());
      fHistos->FillTH1("hCascadeFromXic0",MCcasc->Pt());

			fHistos->FillTH3("hTrueXi",mcpart->Pt(),MCcasc->Pt(),MCcasc->Y());
			fHistos->FillTH3("hTrueEe",mcpart->Pt(),MCe->Pt(),MCe->Y());

			if ( fEventTreeVariable[5]<20 ){
				fHistos->FillProfile("hprofTrueXic0PtSPD0", mcpart->Pt(), mcpart->Pt());
			}else if ( fEventTreeVariable[5]<40 ){
				fHistos->FillProfile("hprofTrueXic0PtSPD1", mcpart->Pt(), mcpart->Pt());
			}else if ( fEventTreeVariable[5]<60 ){
				fHistos->FillProfile("hprofTrueXic0PtSPD2", mcpart->Pt(), mcpart->Pt());
			}

    }//

		fHistos->FillTH3("hTrueXic0SPD",mcpart->Pt(),fabs(mcpart->Y()),fEventTreeVariable[5]);
		fHistos->FillTH3("hTrueXic0WSPD",mcpart->Pt(),fabs(mcpart->Y()),fEventTreeVariable[5],fWeightFit->Eval(mcpart->Pt()));

    if(fabs(mcpart->Y())<0.8){
      fHistos->FillTH1("hTrueXic0_rap8",mcpart->Pt());
      fHistos->FillTH1("hTrueXic0_oldbin_rap8",mcpart->Pt());
      fHistos->FillTH1("hTrueXic0W_rap8",mcpart->Pt(),fWeightFit->Eval(mcpart->Pt()));
      fHistos->FillTH1("hTrueXic0W_oldbin_rap8",mcpart->Pt(),fWeightFit->Eval(mcpart->Pt()));
    }
  }
  return;
}

Bool_t AliAnalysisTaskSEXic0SemileptonicNew2::FillMCXib(AliAODMCParticle *mcpart){
  if((TMath::Abs(mcpart->GetPdgCode())==5132) || (TMath::Abs(mcpart->GetPdgCode())==5232)){  ///Xib- Xib0
    Bool_t e_flag = kFALSE;
    Bool_t xic_flag = kFALSE;
    Bool_t xi_flag = kFALSE;
    AliAODMCParticle *MCe = 0;
    AliAODMCParticle *MCXic = 0; //Xic0 Xic+
    AliAODMCParticle *MCXi = 0; //Xi-
    for(Int_t idau=mcpart->GetDaughterFirst(); idau<mcpart->GetDaughterLast()+1; idau++){
      if(idau<0) break;
      AliAODMCParticle *mcdau = (AliAODMCParticle*) fMC->GetTrack(idau);
      if(!mcdau) continue;
      if(TMath::Abs(mcdau->GetPdgCode())==4132 || TMath::Abs(mcdau->GetPdgCode())==4232 ){ xic_flag = kTRUE; MCXic = mcdau; }
     if(TMath::Abs(mcdau->GetPdgCode())==11) { e_flag = kTRUE; MCe = mcdau; }
   }

    if(xic_flag){
      for(Int_t idau=MCXic->GetDaughterFirst(); idau<MCXic->GetDaughterLast()+1; idau++){
        if(idau<0) break;
        AliAODMCParticle *mcdau = (AliAODMCParticle*) fMC->GetTrack(idau);
        if(!mcdau) continue;
        if(TMath::Abs(mcdau->GetPdgCode())==3312) { xi_flag = kTRUE; MCXi = mcdau; }
      }
    }

    if(e_flag && xi_flag){
      Double_t pxe = MCe->Px(); Double_t pye = MCe->Py();
      Double_t pxv = MCXi->Px(); Double_t pyv = MCXi->Py();
      Double_t eXi = sqrt(pow(pxe+pxv,2)+pow(pye+pyv,2));
      fHistos->FillTH2("XibvseXiRPMGen",mcpart->Pt(), eXi);
      fHistos->FillTH1("XibGen",mcpart->Pt());
      if(fabs(mcpart->Y())<0.5) fHistos->FillTH1("XibGen05",mcpart->Pt());
      fHistos->FillTH1("eXiFromXibGen",eXi);
    }
    return kTRUE;
  }

  return kFALSE;
}

void AliAnalysisTaskSEXic0SemileptonicNew2::FillBottomContribution(AliAODMCParticle *mcpart, AliAODcascade *casc, AliAODTrack *trk){
  Double_t pxe = trk->Px(); Double_t pye = trk->Py();
  Double_t pxv = casc->MomXiX(); Double_t pyv = casc->MomXiY();
  Double_t eXi = sqrt(pow(pxe+pxv,2)+pow(pye+pyv,2));
  fHistos->FillTH2("XibvseXiRPM",mcpart->Pt(), eXi);
  fHistos->FillTH1("Xib",mcpart->Pt());
  fHistos->FillTH1("eXiFromXib",eXi);

  return;
}

void AliAnalysisTaskSEXic0SemileptonicNew2::FillPairEleXi(AliAODcascade *casc, AliAODTrack *trk){

  for(Int_t i=0; i<38; i++) fPaireXiTreeVariable[i] = -9999.;
  for(Int_t i=0; i<13; i++) fMCTreeVariable[i] = -9999.;
  Double_t mcpxe = -9999.; Double_t mcpye = -9999.; Double_t mcpxv = -9999.; Double_t mcpyv = -9999.; Double_t mcPt = -9999.;
  Int_t c_flag = 0; Int_t b_flag = 0;
  Double_t mass; Double_t mass_ss;

  Double_t pxe = trk->Px();
  Double_t pye = trk->Py();
  Double_t pze = trk->Pz();
  Double_t mome = sqrt(pxe*pxe+pye*pye+pze*pze);
  Double_t Ee = sqrt(mome*mome+0.000510998928*0.000510998928);
  Double_t pxv = casc->MomXiX();
  Double_t pyv = casc->MomXiY();
  Double_t pzv = casc->MomXiZ();
  Double_t momv = sqrt(pxv*pxv+pyv*pyv+pzv*pzv);
  Double_t Ev = sqrt(momv*momv+1.32171*1.32171);
  Double_t cosoa = (pxe*pxv+pye*pyv+pze*pzv)/mome/momv;
  Double_t echarge = trk->Charge();
  Double_t vcharge = casc->ChargeXi();
  Double_t In_Mass = sqrt(pow(Ee+Ev,2)-pow(pxe+pxv,2)-pow(pye+pyv,2)-pow(pze+pzv,2));
  Double_t Pt = sqrt(pow(pxe+pxv,2)+pow(pye+pyv,2));

  AliAODTrack *pion = (AliAODTrack*) casc->GetDaughter(0);
  AliAODTrack *proton = (AliAODTrack*) casc->GetDaughter(1);
  AliAODTrack *b_pion = (AliAODTrack*) casc->GetDecayVertexXi()->GetDaughter(0);

  Bool_t isparticle = kTRUE;
  if(vcharge>0) isparticle = kFALSE;
  if(pion->Charge()<0 && proton->Charge()>0) {
    pion = (AliAODTrack*) casc->GetDaughter(1);
    proton = (AliAODTrack*) casc->GetDaughter(0);
  }

  Double_t lDcaPosToPrimVertex = casc->DcaPosToPrimVertex();
  Double_t lDcaNegToPrimVertex = casc->DcaNegToPrimVertex();

  Double_t lPosXi[3];
  lPosXi[0] = casc->DecayVertexXiX();
  lPosXi[1] = casc->DecayVertexXiY();
  lPosXi[2] = casc->DecayVertexXiZ();
  Double_t decayvertXi = TMath::Sqrt(lPosXi[0]*lPosXi[0]+lPosXi[1]*lPosXi[1]);
  Double_t lPosV0[3];
  lPosV0[0] = casc->DecayVertexV0X();
  lPosV0[1] = casc->DecayVertexV0Y();
  lPosV0[2] = casc->DecayVertexV0Z();
  Double_t decayvertV0 = TMath::Sqrt(lPosV0[0]*lPosV0[0]+lPosV0[1]*lPosV0[1]);
  Double_t V0CosineOfPointingAngleXi = casc->CosPointingAngle(lPosXi);

  const AliVVertex* Vtx = fEvt->GetPrimaryVertex();
  Double_t primvert[3];
  Vtx->GetXYZ(primvert);
  Double_t XiCosineOfPointingAngle = casc->CosPointingAngleXi(primvert[0],primvert[1],primvert[2]);

  if(FilterElectron(trk,mass,mass_ss,0,1,1)){
	  fPaireXiTreeVariable[ 0] = pxe*pxe+pye*pye;
    fPaireXiTreeVariable[ 1] = echarge;
    fPaireXiTreeVariable[ 2] = fPIDResponse->NumberOfSigmasTOF(trk,AliPID::kElectron);
    fPaireXiTreeVariable[ 3] = fPIDResponse->NumberOfSigmasTPC(trk,AliPID::kElectron);
    fPaireXiTreeVariable[ 4] = trk->GetTPCsignalN();
    fPaireXiTreeVariable[ 5] = trk->GetITSNcls();
    fPaireXiTreeVariable[ 6] = trk->GetTPCNCrossedRows();
    fPaireXiTreeVariable[ 7] = trk->GetTPCNclsF();
    fPaireXiTreeVariable[ 8] = trk->Phi();
    fPaireXiTreeVariable[ 9] = trk->Y();
    fPaireXiTreeVariable[10] = mass;
    fPaireXiTreeVariable[11] = mass_ss;
    fPaireXiTreeVariable[12] = pxv*pxv+pyv*pyv;
    fPaireXiTreeVariable[13] = vcharge;
    fPaireXiTreeVariable[14] = casc->MassXi();
    fPaireXiTreeVariable[15] = casc->MassLambda();
    fPaireXiTreeVariable[16] = casc->MassAntiLambda();
    fPaireXiTreeVariable[17] = decayvertV0;
    fPaireXiTreeVariable[18] = decayvertXi;
    fPaireXiTreeVariable[19] = casc->DcaBachToPrimVertex();
    if(isparticle){
      fPaireXiTreeVariable[21] = lDcaPosToPrimVertex;
      fPaireXiTreeVariable[20] = lDcaNegToPrimVertex;
    }
    else{
      fPaireXiTreeVariable[20] = lDcaPosToPrimVertex;
      fPaireXiTreeVariable[21] = lDcaNegToPrimVertex;
    }
    fPaireXiTreeVariable[22] = V0CosineOfPointingAngleXi;
    fPaireXiTreeVariable[23] = XiCosineOfPointingAngle;
    fPaireXiTreeVariable[24] = casc->DcaV0ToPrimVertex();
    fPaireXiTreeVariable[25] = casc->RapXi();
    fPaireXiTreeVariable[26] = pion->GetTPCNCrossedRows();
    fPaireXiTreeVariable[27] = pion->GetTPCNclsF();
    fPaireXiTreeVariable[28] = proton->GetTPCNCrossedRows();
    fPaireXiTreeVariable[29] = proton->GetTPCNclsF();
    fPaireXiTreeVariable[30] = b_pion->GetTPCNCrossedRows();
    fPaireXiTreeVariable[31] = b_pion->GetTPCNclsF();
    fPaireXiTreeVariable[32] = pion->Pt();
    fPaireXiTreeVariable[33] = proton->Pt();
    fPaireXiTreeVariable[34] = b_pion->Pt();
    fPaireXiTreeVariable[35] = cosoa;
    fPaireXiTreeVariable[36] = In_Mass;
    fPaireXiTreeVariable[37] = Pt;
    if(!IsMC){
			fEventTree->Fill();
			fPaireXiTree->Fill();
		}
    if(IsMC){
      Int_t MCXiblab = MatchToMCXib(casc, trk);
      if(MCXiblab>-1){
        AliAODMCParticle* mcXib = (AliAODMCParticle*) fMC->GetTrack(MCXiblab);
        if(StandardCutFlag(trk,casc,1,1,1,1)) FillBottomContribution(mcXib,casc,trk);
        fMCTreeVariable[9] = mcXib->Pt();
        fMCTreeVariable[10] = Pt;
        fMCTreeVariable[11] = mcXib->GetCalcMass();
      }
	Int_t MCXic0lab = MatchToMCXic0(casc, trk);
      if(MCXic0lab>-1){
        AliAODMCParticle* mcXic0 = (AliAODMCParticle*) fMC->GetTrack(MCXic0lab);
        Double_t mcXic0_Pt = mcXic0->Pt();

        Int_t lab_mother_of_Xic0 =  mcXic0->GetMother();
        AliAODMCParticle* mother_of_Xic0 = mcXic0;
	if(lab_mother_of_Xic0>=0) mother_of_Xic0 = (AliAODMCParticle*) fMC->GetTrack(lab_mother_of_Xic0);

        Int_t elab = MatchToMCele(trk);
        Int_t Xilab = MatchToMCXi(casc);

        if(elab>0 && Xilab>0){
          AliAODMCParticle* mcXi = (AliAODMCParticle*) fMC->GetTrack(Xilab);
          AliAODMCParticle* mce = (AliAODMCParticle*) fMC->GetTrack(elab);
          Double_t eCharge = mce->Charge();
          Double_t XiCharge = mcXi->Charge();

          mcpxe = mce->Px();
          mcpye = mce->Py();
          mcpxv = mcXi->Px();
          mcpyv = mcXi->Py();
          mcPt = sqrt(pow(mcpxe+mcpxv,2)+pow(mcpye+mcpyv,2));
          Double_t eXi = sqrt(pow(pxe+pxv,2)+pow(pye+pyv,2));

          fMCTreeVariable[ 0] = mcpxe*mcpxe+mcpye*mcpye;
          fMCTreeVariable[ 1] = eCharge;
          fMCTreeVariable[ 2] = mcpxv*mcpxv+mcpyv*mcpyv;
          fMCTreeVariable[ 3] = XiCharge;
          fMCTreeVariable[ 4] = mcXic0->Pt();
          fMCTreeVariable[ 5] = mcPt;
          fMCTreeVariable[ 6] = mcXic0->GetCalcMass();
          fMCTreeVariable[12] = mcXic0->Y();

          if(In_Mass<=2.5 && cosoa>0 && StandardCutFlag(trk,casc,1,1,1,1)){
            fHistos->FillTH2("hXic0vseXiRPM",mcXic0_Pt,eXi);
            //fHistos->FillTH2("hXic0vseXiRPM_2",mcXic0_Pt,eXi);
            fHistos->FillTH1("hGenXic0Pt",mcXic0_Pt); //MC Pt of Xic0
            fHistos->FillTH1("hRecoPairPt",eXi); //Reco Pt of eXi
            //fHistos->FillTH1("hGenXic0Pt_2",mcXic0_Pt); //MC Pt of Xic0
            //fHistos->FillTH1("hRecoPairPt_2",eXi); //Reco Pt of eXi
            if(eCharge>0 && XiCharge<0) fHistos->FillTH1("hGenXic0Pt1",mcXic0_Pt);
            if(eCharge<0 && XiCharge>0) fHistos->FillTH1("hGenXic0Pt2",mcXic0_Pt);

            if((TMath::Abs(mother_of_Xic0->GetPdgCode())==5132) || (TMath::Abs(mother_of_Xic0->GetPdgCode())==5232)) {
              fHistos->FillTH1("hGenXic0PtFromXib",mcXic0_Pt);
              b_flag = 1;
            } else {
              fHistos->FillTH1("hGenXic0PtFromXic",mcXic0_Pt);
              c_flag = 1;
            }

            fMCTreeVariable[ 7] = c_flag;
            fMCTreeVariable[ 8] = b_flag;
          } //fill histo
        } // e_flag && Xi_flag
      } //Xic0
      fPaireXiTree->Fill();
      fMCTree->Fill();
			fEventTree->Fill();
    } //IsMC

    if(cosoa>0 && echarge*vcharge<0 && StandardCutFlag(trk,casc,1,1,1,1)){
      fHistos->FillTH1("hEleXiMassRS",In_Mass);
      if(In_Mass<=2.5) fHistos->FillTH1("hEleXiPtRS",Pt);
    }
    if(cosoa>0 && echarge*vcharge>0 && StandardCutFlag(trk,casc,1,1,1,1)){
      fHistos->FillTH1("hEleXiMassWS",In_Mass);
      if(In_Mass<=2.5) fHistos->FillTH1("hEleXiPtWS",Pt);
    }
  } // FilterElectron

  if(FilterElectron(trk,mass,mass_ss,1,0,1) && StandardCutFlag(trk,casc,1,1,1,1)){  //same sign prefilter
    if(echarge*vcharge<0 && In_Mass<=2.5 && cosoa>=0) fHistos->FillTH1("hEleXiPtRS_SameSign",Pt);
    if(echarge*vcharge>0 && In_Mass<=2.5 && cosoa>=0) fHistos->FillTH1("hEleXiPtWS_SameSign",Pt);
  }
  if(FilterElectron(trk,mass,mass_ss,0,1,1) && StandardCutFlag(trk,casc,1,1,1,1)){  //no prefilter
    if(cosoa>0 && echarge*vcharge<0 && In_Mass<=2.5){
      fHistos->FillTH1("hLooseEleXiPtRS",Pt);
      fHistos->FillTH1("hLooseEleXiPtWS",Pt);
    }
  }

  return;
}

void AliAnalysisTaskSEXic0SemileptonicNew2::FillXiHistFromPromptNonPrompt(Bool_t IsMC, AliAODcascade *casc){
  if(!IsMC) return;
  Bool_t isparticle = kTRUE;
  if(casc->ChargeXi()>0) isparticle = kFALSE;

  AliAODTrack *pion =  (AliAODTrack*)(casc->GetDaughter(0));  //positive
  AliAODTrack *proton =  (AliAODTrack*)(casc->GetDaughter(1));  //negative
  AliAODTrack *b_pion =  (AliAODTrack*)(casc->GetDecayVertexXi()->GetDaughter(0));

  if(pion->Charge()<0 && proton->Charge()>0) {
    pion = (AliAODTrack*) casc->GetDaughter(1);
    proton = (AliAODTrack*) casc->GetDaughter(0);
  }

  Double_t lPosXi[3];
  lPosXi[0] = casc->DecayVertexXiX();
  lPosXi[1] = casc->DecayVertexXiY();
  lPosXi[2] = casc->DecayVertexXiZ();
  Double_t decayvertXi = TMath::Sqrt(lPosXi[0]*lPosXi[0]+lPosXi[1]*lPosXi[1]);
  Double_t lPosV0[3];
  lPosV0[0] = casc->DecayVertexV0X();
  lPosV0[1] = casc->DecayVertexV0Y();
  lPosV0[2] = casc->DecayVertexV0Z();
  Double_t decayvertV0 = TMath::Sqrt(lPosV0[0]*lPosV0[0]+lPosV0[1]*lPosV0[1]);

  const AliVVertex* Vtx = fEvt->GetPrimaryVertex();
  Double_t primvert[3];
  Vtx->GetXYZ(primvert);

  Double_t lDcaXiDaughters = casc->DcaXiDaughters();
  Double_t lDcaV0Daughters = casc->DcaV0Daughters();

  Bool_t Xib_flag = kFALSE;
  Bool_t Xic_flag = kFALSE;
  Bool_t Total_Xic0_flag = kFALSE;

  Double_t Xic0_label = MatchToMCXic0(casc);
  if(Xic0_label==-1) return;
  AliAODMCParticle* mcXic0 = (AliAODMCParticle*) fMC->GetTrack(Xic0_label);

  Total_Xic0_flag = kTRUE;
  Bool_t e_flag = kFALSE; //electron
  Bool_t xi_flag = kFALSE; //Xi-

  for(Int_t idau=mcXic0->GetDaughterFirst(); idau<mcXic0->GetDaughterLast()+1; idau++){
    if(idau<0) break;
    AliAODMCParticle* mcdau = (AliAODMCParticle*) fMC->GetTrack(idau);
    if(!mcdau) continue;
    if(TMath::Abs(mcdau->GetPdgCode())==11) e_flag = kTRUE;
    if(TMath::Abs(mcdau->GetPdgCode())==3312) xi_flag = kTRUE;
  }

  if(e_flag && xi_flag){
    Int_t Xic0_moter_label =  mcXic0->GetMother();
    if(Xic0_moter_label>0){
      AliAODMCParticle* mother_of_Xic0 = (AliAODMCParticle*) fMC->GetTrack(Xic0_moter_label);
      if(((TMath::Abs(mother_of_Xic0->GetPdgCode()))==5132) || ((TMath::Abs(mother_of_Xic0->GetPdgCode()))==5232)) Xib_flag = kTRUE;
      else Xic_flag = kTRUE;
    } //Xic0_mother_label
  } //e_flag && Xi_flag

  Double_t lDcaPosToPrimVertex = casc->DcaPosToPrimVertex();
  if(Total_Xic0_flag) fHistos->FillTH1("hDCAV0PrToPrimVertex",lDcaPosToPrimVertex);
  if(Xib_flag) fHistos->FillTH1("hDCAV0PrToPrimVertex_b",lDcaPosToPrimVertex);
  if(Xic_flag) fHistos->FillTH1("hDCAV0PrToPrimVertex_c",lDcaPosToPrimVertex);

  Double_t lDcaNegToPrimVertex = casc->DcaNegToPrimVertex();
  if(Total_Xic0_flag) fHistos->FillTH1("hDCAV0PiToPrimVertex",lDcaNegToPrimVertex);
  if(Xib_flag) fHistos->FillTH1("hDCAV0PiToPrimVertex_b",lDcaNegToPrimVertex);
  if(Xic_flag) fHistos->FillTH1("hDCAV0PiToPrimVertex_c",lDcaNegToPrimVertex);

  Double_t lDcaBachToPrimVertex = casc->DcaBachToPrimVertex();
  if(Total_Xic0_flag) fHistos->FillTH1("hDCABachToPrimVertex",lDcaBachToPrimVertex);
  if(Xib_flag) fHistos->FillTH1("hDCABachToPrimVertex_b",lDcaBachToPrimVertex);
  if(Xic_flag) fHistos->FillTH1("hDCABachToPrimVertex_c",lDcaBachToPrimVertex);

  Double_t lDcaV0ToPrimVertex = casc->DcaV0ToPrimVertex();
  if(Total_Xic0_flag) fHistos->FillTH1("hDCAV0ToPrimVertex",lDcaV0ToPrimVertex);
  if(Xib_flag) fHistos->FillTH1("hDCAV0ToPrimVertex_b",lDcaV0ToPrimVertex);
  if(Xic_flag) fHistos->FillTH1("hDCAV0ToPrimVertex_c",lDcaV0ToPrimVertex);

  Double_t lXiCosineOfPointingAngle = casc->CosPointingAngleXi(primvert[0],primvert[1],primvert[2]);
  Double_t lV0CosineOfPointingAngleXi = casc->CosPointingAngle(lPosXi);

  if(Total_Xic0_flag) fHistos->FillTH1("hV0CosineOfPoiningAngleXi",lXiCosineOfPointingAngle);
  if(Xib_flag) fHistos->FillTH1("hV0CosineOfPoiningAngleXi_b",lXiCosineOfPointingAngle);
  if(Xic_flag) fHistos->FillTH1("hV0CosineOfPoiningAngleXi_c",lXiCosineOfPointingAngle);

  if(Total_Xic0_flag) fHistos->FillTH1("hV0CosineOfPoiningAngleV0Xi",lV0CosineOfPointingAngleXi);
  if(Xib_flag) fHistos->FillTH1("hV0CosineOfPoiningAngleV0Xi_b",lV0CosineOfPointingAngleXi);
  if(Xic_flag) fHistos->FillTH1("hV0CosineOfPoiningAngleV0Xi_c",lV0CosineOfPointingAngleXi);

  if(Total_Xic0_flag) fHistos->FillTH1("hCascDecayLength",decayvertXi);
  if(Xib_flag) fHistos->FillTH1("hCascDecayLength_b",decayvertXi);
  if(Xic_flag) fHistos->FillTH1("hCascDecayLength_c",decayvertXi);

  if(Total_Xic0_flag) fHistos->FillTH1("hDecayLengthV0",decayvertV0);
  if(Xib_flag) fHistos->FillTH1("hDecayLengthV0_b",decayvertV0);
  if(Xic_flag) fHistos->FillTH1("hDecayLengthV0_c",decayvertV0);

  if(Xib_flag) fHistos->FillTH1("B_flag","all",1);
  if(Xic_flag) fHistos->FillTH1("C_flag","all",1);
  if(Xib_flag) fHistos->FillTH1("Bcut_flag","all",1);
  if(Xic_flag) fHistos->FillTH1("Ccut_flag","all",1);
  if(isparticle){
    if(lDcaPosToPrimVertex > 0.073){
      if(Xib_flag) fHistos->FillTH1("B_flag","DCAV0Pr_b",1);
      if(Xic_flag) fHistos->FillTH1("C_flag","DCAV0Pr_c",1);
      if(Xib_flag) fHistos->FillTH1("Bcut_flag","DCAV0Pr_b",1);
      if(Xic_flag) fHistos->FillTH1("Ccut_flag","DCAV0Pr_c",1);
    }
    if(lDcaNegToPrimVertex > 0.073){
      if(Xib_flag) fHistos->FillTH1("B_flag","DCAV0Pi_b",1);
      if(Xic_flag) fHistos->FillTH1("C_flag","DCAV0Pi_c",1);
      if(Xib_flag) fHistos->FillTH1("Bcut_flag","DCAV0Pi_b",1);
      if(Xic_flag) fHistos->FillTH1("Ccut_flag","DCAV0Pi_c",1);
    }
  }
  else{
    if(lDcaPosToPrimVertex > 0.073){
      if(Xib_flag) fHistos->FillTH1("B_flag","DCAV0Pi_b",1);
      if(Xic_flag) fHistos->FillTH1("C_flag","DCAV0Pi_c",1);
      if(Xib_flag) fHistos->FillTH1("Bcut_flag","DCAV0Pi_b",1);
      if(Xic_flag) fHistos->FillTH1("Ccut_flag","DCAV0Pi_c",1);
    }
    if(lDcaNegToPrimVertex > 0.073){
      if(Xib_flag) fHistos->FillTH1("B_flag","DCAV0Pr_b",1);
      if(Xic_flag) fHistos->FillTH1("C_flag","DCAV0Pr_c",1);
      if(Xib_flag) fHistos->FillTH1("Bcut_flag","DCAV0Pr_b",1);
      if(Xic_flag) fHistos->FillTH1("Ccut_flag","DCAV0Pr_c",1);
    }
  }
  if(lDcaBachToPrimVertex > 0.0204){
    if(Xib_flag) fHistos->FillTH1("B_flag","DCABach_b",1);
    if(Xic_flag) fHistos->FillTH1("C_flag","DCABach_c",1);
    if(Xib_flag) fHistos->FillTH1("Bcut_flag","DCABach_b",1);
    if(Xic_flag) fHistos->FillTH1("Ccut_flag","DCABach_c",1);
  }
  if(lDcaV0ToPrimVertex > 0.03){
    if(Xib_flag) fHistos->FillTH1("B_flag","DCAV0_b",1);
    if(Xic_flag) fHistos->FillTH1("C_flag","DCAV0_c",1);
    if(Xib_flag) fHistos->FillTH1("Bcut_flag","DCAV0_b",1);
    if(Xic_flag) fHistos->FillTH1("Ccut_flag","DCAV0_c",1);
  }
  if(lXiCosineOfPointingAngle > 0.983){
    if(Xib_flag) fHistos->FillTH1("B_flag","COS1_b",1);
    if(Xic_flag) fHistos->FillTH1("C_flag","COS1_c",1);
    if(Xib_flag) fHistos->FillTH1("Bcut_flag","COS1_b",1);
    if(Xic_flag) fHistos->FillTH1("Ccut_flag","COS1_c",1);
  }
  if(lV0CosineOfPointingAngleXi > 0.983){
    if(Xib_flag) fHistos->FillTH1("B_flag","COS2_b",1);
    if(Xic_flag) fHistos->FillTH1("C_flag","COS2_c",1);
    if(Xib_flag) fHistos->FillTH1("Bcut_flag","COS2_b",1);
    if(Xic_flag) fHistos->FillTH1("Ccut_flag","COS2_c",1);
  }
  if(decayvertXi > 0.38){
    if(Xib_flag) fHistos->FillTH1("B_flag","DLXi_b",1);
    if(Xic_flag) fHistos->FillTH1("C_flag","DLXi_c",1);
    if(Xib_flag) fHistos->FillTH1("Bcut_flag","DLXi_b",1);
    if(Xic_flag) fHistos->FillTH1("Ccut_flag","DLXi_c",1);
  }
  if (decayvertV0 > 2.67){
    if(Xib_flag) fHistos->FillTH1("B_flag","DLV0_b",1);
    if(Xic_flag) fHistos->FillTH1("C_flag","DLV0_c",1);
    if(Xib_flag) fHistos->FillTH1("Bcut_flag","DLV0_b",1);
    if(Xic_flag) fHistos->FillTH1("Ccut_flag","DLV0_c",1);
  }

  return;
}

Int_t AliAnalysisTaskSEXic0SemileptonicNew2::MatchToMCXib(AliAODcascade *casc, AliAODTrack *trk){
  Int_t Xi_label = MatchToMCXi(casc); if(!Xi_label) return -1;
  AliAODMCParticle* mcXi = (AliAODMCParticle*) fMC->GetTrack(Xi_label);

  Int_t e_label = MatchToMCele(trk); if(!e_label) return -1;
  AliAODMCParticle* mc_e = (AliAODMCParticle*) fMC->GetTrack(e_label);

  Int_t mother_Xi_label = mcXi->GetMother();
  Int_t mother_e_label = mc_e->GetMother();
  if(mother_Xi_label<0) return -1;
  if(mother_e_label<0) return -1;
  AliAODMCParticle* mcXic = (AliAODMCParticle*) fMC->GetTrack(mother_Xi_label);
  if((TMath::Abs(mcXic->GetPdgCode())==4132) == (TMath::Abs(mcXic->GetPdgCode())==4232)) return -1;
  Int_t mother_Xic_label = mcXic->GetMother();
  if(mother_Xic_label<0) return -1;
  AliAODMCParticle* mcXib_Xi = (AliAODMCParticle*) fMC->GetTrack(mother_Xic_label);
  if((TMath::Abs(mcXib_Xi->GetPdgCode())==5132) == (TMath::Abs(mcXib_Xi->GetPdgCode())==5232)) return -1;
  AliAODMCParticle* mcXib_e = (AliAODMCParticle*) fMC->GetTrack(mother_e_label);
  if(!(mother_e_label == mother_Xic_label)) return -1;
  if((TMath::Abs(mcXib_e->GetPdgCode())==5132) || (TMath::Abs(mcXib_e->GetPdgCode())==5232)) return mother_e_label;

  return -1;
}

Int_t AliAnalysisTaskSEXic0SemileptonicNew2::MatchToMCXic0(AliAODcascade *casc, AliAODTrack *trk){
  Int_t Xi_label = MatchToMCXi(casc); if(!Xi_label) return -1;
  AliAODMCParticle* mcXi = (AliAODMCParticle*) fMC->GetTrack(Xi_label);

  Int_t e_label = MatchToMCele(trk); if(!e_label) return -1;
  AliAODMCParticle* mc_e = (AliAODMCParticle*) fMC->GetTrack(e_label);

  Int_t mother_Xi_label = mcXi->GetMother();  //Xic0
  Int_t mother_e_label = mc_e->GetMother();   //Xic0
  if(mother_Xi_label<0) return -1;
  if(!(mother_e_label==mother_Xi_label)) return -1;
  AliAODMCParticle* mcXic0 = (AliAODMCParticle*) fMC->GetTrack(mother_Xi_label);
  if(TMath::Abs(mcXic0->GetPdgCode())==4132) return mother_Xi_label;

  return -1;
}

Int_t AliAnalysisTaskSEXic0SemileptonicNew2::MatchToMCXic0(AliAODcascade *casc){
  Int_t Xi_label = MatchToMCXi(casc); if(!Xi_label) return -1;
  AliAODMCParticle* mcXi = (AliAODMCParticle*) fMC->GetTrack(Xi_label);

  Int_t mother_Xi_label = mcXi->GetMother();  //Xic0
  if(mother_Xi_label<0) return -1;
  AliAODMCParticle* mcXic0 = (AliAODMCParticle*) fMC->GetTrack(mother_Xi_label);
  if(TMath::Abs(mcXic0->GetPdgCode())==4132) return mother_Xi_label;

  return -1;
}

Int_t AliAnalysisTaskSEXic0SemileptonicNew2::MatchToMCXi(AliAODcascade* casc){
  AliAODTrack *pion = (AliAODTrack*) casc->GetDaughter(0); if(!pion) return 0;
  AliAODTrack *proton = (AliAODTrack*) casc->GetDaughter(1); if(!proton) return 0;
  AliAODTrack *b_pion = (AliAODTrack*) casc->GetDecayVertexXi()->GetDaughter(0); if(!b_pion) return 0;
  Int_t b_pion_label = TMath::Abs(b_pion->GetLabel());  if(b_pion_label<0) return 0;
  Int_t pion_label = TMath::Abs(pion->GetLabel()); if(pion_label<0) return 0;
  Int_t proton_label = TMath::Abs(proton->GetLabel()); if(proton_label<0) return 0;

  AliAODMCParticle* mc_b_pion = (AliAODMCParticle*) fMC->GetTrack(b_pion_label);
  AliAODMCParticle* mc_pion = (AliAODMCParticle*) fMC->GetTrack(pion_label);
  AliAODMCParticle* mc_proton = (AliAODMCParticle*) fMC->GetTrack(proton_label);

  //cout <<"bachelor (211): "<< TMath::Abs(mc_b_pion->GetPdgCode()) <<" 211 or 2212 : "<< TMath::Abs(mc_proton->GetPdgCode()) << " 211 or 2212 : " <<TMath::Abs(mc_pion->GetPdgCode()) <<endl;

  if(TMath::Abs(mc_b_pion->GetPdgCode())!=211) return 0;
  if((TMath::Abs(mc_proton->GetPdgCode())==211) == (TMath::Abs(mc_proton->GetPdgCode())==2212)) return 0;
  if((TMath::Abs(mc_pion->GetPdgCode())==211) == (TMath::Abs(mc_pion->GetPdgCode())==2212)) return 0;

  Int_t mother_b_pion_label = mc_b_pion->GetMother();
  Int_t mother_pion_label = mc_pion->GetMother();
  Int_t mother_proton_label = mc_proton->GetMother();
  if(mother_pion_label!=mother_proton_label) return 0;
  if(mother_b_pion_label==mother_pion_label) return 0;
  if(mother_b_pion_label<0) return 0;
  if(mother_proton_label<0) return 0;

  AliAODMCParticle* mcXi = (AliAODMCParticle*) fMC->GetTrack(mother_b_pion_label);
  AliAODMCParticle* mother_proton = (AliAODMCParticle*) fMC->GetTrack(mother_proton_label);
  if(TMath::Abs(mcXi->GetPdgCode())!=3312) return 0;
  Int_t mother_lambda_label = mother_proton->GetMother();
  if(mother_lambda_label<0) return 0;
  if(mother_lambda_label != mother_b_pion_label) return 0;

  return mother_b_pion_label;
}

Int_t AliAnalysisTaskSEXic0SemileptonicNew2::MatchToMCele(AliAODTrack* trk){
  Int_t e_label = trk->GetLabel(); if(e_label<0) return 0;
  AliAODMCParticle* mc_e = (AliAODMCParticle*) fMC->GetTrack(e_label);
  //if(!(TMath::Abs(mc_e->GetPdgCode())==11)) return 0;

  return e_label;
}

Bool_t AliAnalysisTaskSEXic0SemileptonicNew2::StandardCutFlag(AliAODTrack *track, AliAODcascade *casc, Bool_t e_reco, Bool_t e_pid, Bool_t Xi_reco, Bool_t Xi_pid){
  //-------------------------------------eletron-------------------------------------
  if(e_reco){
    AliESDtrackCuts* miniTrackCuts = new AliESDtrackCuts();
    //miniTrackCuts->SetMinNClustersTPC(e_cut[0]);  //tpc cluster
    miniTrackCuts->SetMinNClustersITS(3);  //its cluster

    AliAODTrack *aodt = dynamic_cast<AliAODTrack*>(track);
    AliESDtrack copyTrack(aodt);
      copyTrack.SetTPCClusterMap(aodt->GetTPCClusterMap());
      copyTrack.SetTPCSharedMap(aodt->GetTPCSharedMap());
      copyTrack.SetTPCPointsF(aodt->GetTPCNclsF());
    if (!(miniTrackCuts->IsSelected(&copyTrack))) return kFALSE;
    if(track->GetTPCsignalN()<=50) return kFALSE; // number of TPC PID cluster

    if(!(track->GetTPCNclsF()==0) && track->GetTPCNCrossedRows()/track->GetTPCNclsF()<=0.8) return kFALSE;
    if(track->GetTPCNCrossedRows()<=70) return kFALSE;

    delete miniTrackCuts;
  }

  Double_t e_pt = track->Pt();

  if(e_pid){ //stand
    Double_t cut_tpc = -3.9+(1.17*e_pt)-(0.094*e_pt*e_pt);
    if(fPIDResponse->NumberOfSigmasTPC(track,AliPID::kElectron)<cut_tpc) return kFALSE;
    if(e_pt>5 && fPIDResponse->NumberOfSigmasTPC(track,AliPID::kElectron)<(-3.9+(1.17*5)-(0.094*5*5))) return kFALSE;
  }
  //-------------------------------------cascade-------------------------------------

  if(Xi_reco){
    if(!casc) return kFALSE;
    if(!(casc->GetSecondaryVtx())) return kFALSE;
    if(!(casc->GetDecayVertexXi())) return kFALSE;

    AliAODTrack *pion =  (AliAODTrack*)(casc->GetDaughter(0));  //positive
    AliAODTrack *proton =  (AliAODTrack*)(casc->GetDaughter(1));  //negative
    AliAODTrack *b_pion =  (AliAODTrack*)(casc->GetDecayVertexXi()->GetDaughter(0));

    if(!pion||!proton||!b_pion) return kFALSE;

    if(pion->GetTPCNCrossedRows()<=70) return kFALSE;
    if(proton->GetTPCNCrossedRows()<=70) return kFALSE;
    if(b_pion->GetTPCNCrossedRows()<=70) return kFALSE;
    if(!(pion->GetTPCNclsF()==0) && pion->GetTPCNCrossedRows()/pion->GetTPCNclsF()<=0.77) return kFALSE;
    if(!(proton->GetTPCNclsF()==0) && proton->GetTPCNCrossedRows()/proton->GetTPCNclsF()<=0.77) return kFALSE;
    if(!(b_pion->GetTPCNclsF()==0) && b_pion->GetTPCNCrossedRows()/b_pion->GetTPCNclsF()<=0.77) return kFALSE;
  }

  if(Xi_pid){
    if(!casc) return kFALSE;
    if(!(casc->GetSecondaryVtx())) return kFALSE;
    if(!(casc->GetDecayVertexXi())) return kFALSE;

    AliAODTrack *pion =  (AliAODTrack*)(casc->GetDaughter(0));  //positive
    AliAODTrack *proton =  (AliAODTrack*)(casc->GetDaughter(1));  //negative
    AliAODTrack *b_pion =  (AliAODTrack*)(casc->GetDecayVertexXi()->GetDaughter(0));

    if(!pion||!proton||!b_pion) return kFALSE;

    if(casc->DcaPosToPrimVertex() <= 0.073) return kFALSE;
    if(casc->DcaNegToPrimVertex() <= 0.073) return kFALSE;
    if(casc->DcaBachToPrimVertex() <= 0.0204) return kFALSE;
    if(casc->DcaV0ToPrimVertex() <= 0.03) return kFALSE;

    const AliVVertex* Vtx = fEvt->GetPrimaryVertex();
    Double_t primvert[3];
    Vtx->GetXYZ(primvert);

    Double_t lPosXi[3];
    lPosXi[0] = casc->DecayVertexXiX();
    lPosXi[1] = casc->DecayVertexXiY();
    lPosXi[2] = casc->DecayVertexXiZ();
    Double_t decayvertXi = TMath::Sqrt(lPosXi[0]*lPosXi[0]+lPosXi[1]*lPosXi[1]);
    Double_t lPosV0[3];
    lPosV0[0] = casc->DecayVertexV0X();
    lPosV0[1] = casc->DecayVertexV0Y();
    lPosV0[2] = casc->DecayVertexV0Z();
    Double_t decayvertV0 = TMath::Sqrt(lPosV0[0]*lPosV0[0]+lPosV0[1]*lPosV0[1]);

    if(decayvertXi <=0.38) return kFALSE;
    if(decayvertV0 <= 2.67) return kFALSE;

    Double_t lV0CosineOfPointingAngleXi = casc->CosPointingAngle(lPosXi);
    Double_t lXiCosineOfPointingAngle = casc->CosPointingAngleXi(primvert[0],primvert[1],primvert[2]);
    if(lXiCosineOfPointingAngle <= 0.983) return kFALSE;
    if(lV0CosineOfPointingAngleXi <= 0.983) return kFALSE;
  }

  return kTRUE;
}

//___________________________________________________________________
void AliAnalysisTaskSEXic0SemileptonicNew2::FinishTaskOutput() {}
                //fOutput->Write();
//___________________________________________________________________
void AliAnalysisTaskSEXic0SemileptonicNew2::Terminate(Option_t*) {}

//___________________________________________________________________
//_____________________Define Tree Valuable___________________________
//___________________________________________________________________

void AliAnalysisTaskSEXic0SemileptonicNew2::DefineMCCutTree(){
  fMCCutTree = new TTree("MCCutTree","MCCutTree");
  vector <TString> fTreeVariableName = {"e_TPC","e_TPCPID","e_ITS","e_TPCInfo","e_nTOF","e_nTPC","pion_TPC","proton_TPC","bpion_TPC","pion_TPCPID",
  "proton_TPCPID","bpion_TPCPID","pion_TPCInfo","proton_TPCInfo","bpion_TPCInfo","proton_nTPC_proton","pion_nTPC_pion","proton_nTPC_pion","pion_nTPC_proton","bpion_nTPC_pion",
  "Ximass","DLV0","DCAbach","DCAV0","COS","DLXi","DCAPos","DCANeg","IsParticle","Xic0Pt",
  "b_flag","c_flag"};
  fMCCutTreeVariable = new Float_t [fTreeVariableName.size()];

  for (Int_t ivar=0; ivar<(Float_t)fTreeVariableName.size(); ivar++) fMCCutTree->Branch(fTreeVariableName[ivar].Data(),&fMCCutTreeVariable[ivar],Form("%s/f",fTreeVariableName[ivar].Data()));

  return;
}

void AliAnalysisTaskSEXic0SemileptonicNew2::DefinePaireXiTree(){
  fPaireXiTree = new TTree("eXiTree","eXiTree");
  vector <TString> fTreeVariableName = {"pTe","echarge","TOFnSigma","TPCnSigma","TPCPID","ITS","e_crossedrows","e_findable","phi","erap",
  "e_minmass","e_minmass_ss","pTv","vcharge","Massv","MassLambda","MassAntiLambda","V0DecayLength","CascDecayLength","DCABachToPrimVertex",
  "DCAV0NegToPrimVertex","DCAV0PosToPrimVertex","V0CosineOfPoiningAngleXi","XiCosineOfPoiningAngle","DCAV0ToPrimVertex","Xirap","pion_crossedrows","pion_findable","proton_crossedrows","proton_findable",
  "bpion_crossedratio","bpion_findable","pTpion","pTproton","pTbach","cosoa","In_Mass","eXiPt"};
  fPaireXiTreeVariable = new Float_t [fTreeVariableName.size()];

  for (Int_t ivar=0; ivar<(Float_t)fTreeVariableName.size(); ivar++) fPaireXiTree->Branch(fTreeVariableName[ivar].Data(),&fPaireXiTreeVariable[ivar],Form("%s/f",fTreeVariableName[ivar].Data()));

  return;
}

void AliAnalysisTaskSEXic0SemileptonicNew2::DefineMCPaireXiTree(){
  fMCTree = new TTree("MCTree","MCTree");
  vector <TString> fTreeVariableName = {"mcpTe","mcecharge","mcpTv","mcvcharge","mcpTXic0","mcpTeXi","mcXicMass","c_flag","b_flag","mcpTXib","mceXipTb","mcXibMass","mcYXic0"};
  fMCTreeVariable = new Float_t [fTreeVariableName.size()];

  for (Int_t ivar=0; ivar<(Float_t)fTreeVariableName.size(); ivar++) fMCTree->Branch(fTreeVariableName[ivar].Data(),&fMCTreeVariable[ivar],Form("%s/f",fTreeVariableName[ivar].Data()));

  return;
}

void AliAnalysisTaskSEXic0SemileptonicNew2::DefineMCeTree(){
	fMCeTree = new TTree("MCeTree","MCeTree");
	vector <TString> fTreeVariableName = {
		"pT","eta","mcpTe","mcYe","mcecharge",
		"mcpTXic0","mcYXic0","ITSClusterMap","SPDValue","IsSelected"};
  fMCeTreeVariable = new Float_t [fTreeVariableName.size()];

  for (Int_t ivar=0; ivar<(Float_t)fTreeVariableName.size(); ivar++) fMCeTree->Branch(fTreeVariableName[ivar].Data(),&fMCeTreeVariable[ivar],Form("%s/f",fTreeVariableName[ivar].Data()));

  return;
}

void AliAnalysisTaskSEXic0SemileptonicNew2::DefineEventTree(){
  fEventTree = new TTree("EventTree","EventTree");
  Int_t nVar = 7;
  fEventTreeVariable = new Float_t [nVar];
  TString * fTreeVariableNames = new TString[nVar];

	fTreeVariableNames[ 0]="fRunNumber";
	fTreeVariableNames[ 1]="fEventID";
	fTreeVariableNames[ 2]="fV0MCentrality";
	fTreeVariableNames[ 3]="fSPDCentrality";
	fTreeVariableNames[ 4]="fV0MValue";
	fTreeVariableNames[ 5]="fSPDValue";
	fTreeVariableNames[ 6]="fVertexZ";

  for (Int_t ivar=0; ivar<nVar; ivar++) fEventTree->Branch(fTreeVariableNames[ivar].Data(),&fEventTreeVariable[ivar],Form("%s/f",fTreeVariableNames[ivar].Data()));

  return;
}

unsigned int AliAnalysisTaskSEXic0SemileptonicNew2::GetEvID() {
                //TString* currentfilename = (TObject*)((AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler()->GetTree()->GetCurrentFile()))->GetName();
                //if(!fFileName.EqualTo(currentfilename)) {
                unsigned int fEventNumber = 0;
                //TString* fFileName = (TString*) currentfilename;
                //TObjArray *path = fFileName->Tokenize("/");
                //TString s = ((TObjString*)path->At( ((path->GetLast())-1) ))->GetString();
                //unsigned int fDirNumber = (unsigned int)s.Atoi();
                //delete path;
                //}
                Long64_t ev_number = Entry();
                if(IsMC) {
                                ev_number = fEventNumber;
                }
                unsigned int evID = (unsigned int)ev_number;// + (unsigned int)(fDirNumber<<17);
                fEventNumber++;
                return evID;
}