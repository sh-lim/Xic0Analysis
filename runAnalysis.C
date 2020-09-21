// include the header of your analysis task here! for classes already compiled by aliBuild,
// precompiled header files (with extension pcm) are available, so that you do not need to
// specify includes for those. for your own task however, you (probably) have not generated a
// pcm file, so we need to include it explicitly
//#include "AliMultSelectionTask.h"
//#include "AliAnalysisTaskPIDResponse.h"
//#include "AliPhysicsSelectionTask.h"
#include "AliAnalysisTaskSEXic0SemileptonicNew2.h"
//#include "AliAnalysisTaskSEXic0SemileptonicEvent.h"

void runAnalysis(
		const char *taskname = "XiSHLNew2B"
		//,const char *option = "LHC17MC3" // when scanning AOD, add "AOD"
		,const char *option = "LHC17m" // when scanning AOD, add "AOD"
		,const char *mode = "full" //full, termiante, merge
		)
{
	// set if you want to run the analysis locally (kTRUE), or on grid (kFALSE)
	Bool_t local = kFALSE;
	// if you run on grid, specify test mode (kTRUE) or full grid model (kFALSE)
	Bool_t gridTest = kFALSE;

	TString foption = option;
	bool ismc = false;
	if(foption.Contains("MC")) ismc = true;

	ifstream frun;
	char fname[300];
	sprintf(fname,"runlist/runlist_%s.lst",option);
	frun.open(fname);
	vector<int> vec_run;
	int tmp_run;
	while ( frun >> tmp_run ) vec_run.push_back(tmp_run);

	// since we will compile a class, tell root where to look for headers  
	gInterpreter->ProcessLine(".include $ROOTSYS/include");
	gInterpreter->ProcessLine(".include $ALICE_ROOT/include");
	gInterpreter->ProcessLine(".include $ALICE_PHYSICS/include");

	// create the analysis manager
	AliAnalysisManager *mgr = new AliAnalysisManager(Form("%s%s",taskname,option));
	AliAODInputHandler *aodH = new AliAODInputHandler();
	mgr->SetInputEventHandler(aodH);

	// compile the class and load the add task macro
	// here we have to differentiate between using the just-in-time compiler
	// from root6, or the interpreter of root5
	AliPhysicsSelectionTask *physSelTask = reinterpret_cast<AliPhysicsSelectionTask *>(gInterpreter->ProcessLine(Form(".x %s(%d,%d)", gSystem->ExpandPathName("$ALICE_PHYSICS/OADB/macros/AddTaskPhysicsSelection.C"),ismc,1)));
	if(!physSelTask) { Printf("no physSelTask"); return; }
	//gROOT->LoadMacro("$ALICE_PHYSICS/OADB/macros/AddTaskPhysicsSelection.C");
	//AliPhysicsSelectionTask *physSelTask = AddTaskPhysicsSelection(ismc,1);    //1=pp,pPb, 0=PbPb

	AliMultSelectionTask *multTask = reinterpret_cast<AliMultSelectionTask *>(gInterpreter->ProcessLine(Form(".x %s(%d)", gSystem->ExpandPathName("$ALICE_PHYSICS/OADB/COMMON/MULTIPLICITY/macros/AddTaskMultSelection.C"),1)));
	if(!multTask) { Printf("no multTask"); return; }
	//gROOT->LoadMacro( "$ALICE_PHYSICS/OADB/COMMON/MULTIPLICITY/macros/AddTaskMultSelection.C");
	//AliMultSelectionTask* multtask = AddTaskMultSelection(kTRUE);

	AliAnalysisTaskPIDResponse *pidResponseTask = reinterpret_cast<AliAnalysisTaskPIDResponse *>(gInterpreter->ProcessLine(Form(".x %s(%d)", gSystem->ExpandPathName("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C"),ismc)));
	if(!pidResponseTask) { Printf("no pidResponseTask"); return; }
	//gROOT->LoadMacro("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C");
	//AliAnalysisTaskPIDResponse *pidResponseTask = AddTaskPIDResponse(ismc);

	//gInterpreter->LoadMacro("AliAnalysisTaskSEXic0SemileptonicEvent.cxx++g"); 
	//AliAnalysisTaskSEXic0SemileptonicEvent *task = reinterpret_cast<AliAnalysisTaskSEXic0SemileptonicEvent *>(gInterpreter->ProcessLine(Form(".x AddMyTaskXic0Event.C(\"%s\",\"%s%s\")",taskname,taskname,option)));
	//gROOT->LoadMacro("AliAnalysisTaskSEXic0SemileptonicEvent.cxx++g");
	//gROOT->LoadMacro("AddMyTaskXic0Event.C");
	//AliAnalysisTaskSEXic0SemileptonicEvent *task = AddMyTaskXic0Event(taskname, Form("%s%s",taskname,option));

	gInterpreter->LoadMacro("AliAnalysisTaskSEXic0SemileptonicNew2.cxx++g"); 
	AliAnalysisTaskSEXic0SemileptonicNew2 *task = reinterpret_cast<AliAnalysisTaskSEXic0SemileptonicNew2 *>(gInterpreter->ProcessLine(Form(".x AddMyTaskXic0New2.C(\"%s\",\"%s%s\")",taskname,taskname,option)));
	//gROOT->LoadMacro("AddMyTaskXic0New2.C");
	//AliAnalysisTaskSEXic0SemileptonicNew2 *task = AddMyTaskXic0New2(taskname, Form("%s%s",taskname,option));
	
	if(!task) { Printf("no mytask"); return; }
	task->IsPP(true);
	task->SetMC(ismc);
	if(foption.Contains("LHC16MCk")){ task->SetRunOffset(256941); }
	else if(foption.Contains("LHC16MCl")){ task->SetRunOffset(256941); }
	else if(foption.Contains("LHC16MC1")){ task->SetRunOffset(252235); }
	else if(foption.Contains("LHC16MC2")){ task->SetRunOffset(262424); }
	else if(foption.Contains("LHC16MC5")){ task->SetRunOffset(265309); }
	else if(foption.Contains("LHC17MC1")){ task->SetRunOffset(270581); }
	else if(foption.Contains("LHC17MC2")){ task->SetRunOffset(274690); }
	else if(foption.Contains("LHC17MC3")){ task->SetRunOffset(278914); }
	else if(foption.Contains("LHC18MC1")){ task->SetRunOffset(285009); }
	else if(
			foption.Contains("LHC18MC2")
			|| foption.Contains("LHC18b")
			|| foption.Contains("LHC18d")
			){ task->SetRunOffset(285009); }
	else if(foption.Contains("LHC18MC3")){ task->SetRunOffset(290323); }	

	if(!mgr->InitAnalysis()) return;
	mgr->SetDebugLevel(2);
	mgr->PrintStatus();
	mgr->SetUseProgressBar(1, 25);

	if(local) {
		// if you want to run locally, we need to define some input
		TChain* chain = new TChain("aodTree");
		// add a few files to the chain (change this so that your local files are added)
		if(ismc){
			chain->Add("AliAOD-279000-MC.root");
		}else{
			chain->Add("AliAOD-279000.root");
		}
		// start the analysis locally, reading the events from the tchain
		mgr->StartAnalysis("local", chain);
	} else {
		// if we want to run on grid, we create and configure the plugin
		AliAnalysisAlien *alienHandler = new AliAnalysisAlien();
		// also specify the include (header) paths on grid
		alienHandler->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_PHYSICS/include");
		// make sure your source files get copied to grid
		//alienHandler->SetAdditionalLibs("AliAnalysisTaskSEXic0SemileptonicEvent.cxx AliAnalysisTaskSEXic0SemileptonicEvent.h");
		//alienHandler->SetAnalysisSource("AliAnalysisTaskSEXic0SemileptonicEvent.cxx");
		alienHandler->SetAdditionalLibs("AliAnalysisTaskSEXic0SemileptonicNew2.cxx AliAnalysisTaskSEXic0SemileptonicNew2.h");
		alienHandler->SetAnalysisSource("AliAnalysisTaskSEXic0SemileptonicNew2.cxx");
		//alienHandler->SetAdditionalLibs("AliAnalysisTaskSEXic0SemileptonicNew.cxx AliAnalysisTaskSEXic0SemileptonicNew.h");
		//alienHandler->SetAnalysisSource("AliAnalysisTaskSEXic0SemileptonicNew.cxx");
		// select the aliphysics version. all other packages
		// are LOADED AUTOMATICALLY!
		//alienHandler->SetAliPhysicsVersion("vAN-20200620_ROOT6-1");
		//alienHandler->SetAliPhysicsVersion("vAN-20200620-1");
		alienHandler->SetAliPhysicsVersion("vAN-20200322-1");
		// set the Alien API version
		alienHandler->SetAPIVersion("V1.1x");
		// select the input data
		if (foption.Contains("LHC18MC")){ 
			alienHandler->SetGridDataDir("/alice/sim/2018/LHC18l5b");
			alienHandler->SetDataPattern("/AOD/*/AliAOD.root");
		}else if (foption.Contains("LHC17MC")){ 
			alienHandler->SetGridDataDir("/alice/sim/2018/LHC18l5a");
			alienHandler->SetDataPattern("/AOD/*/AliAOD.root");
		}else if (foption.Contains("LHC16MCk") || foption.Contains("LHC16MCl")){ 
			alienHandler->SetGridDataDir("/alice/sim/2018/LHC18f4b");
			alienHandler->SetDataPattern("/*/AliAOD.root");
		}else if (foption.Contains("LHC16MC1") || foption.Contains("LHC16MC2")){ 
			alienHandler->SetGridDataDir("/alice/sim/2017/LHC17h8b"); //LHC16d
			alienHandler->SetDataPattern("/AOD/*/AliAOD.root");
		}else if (foption.Contains("LHC16MC5")){ 
			alienHandler->SetGridDataDir("/alice/sim/2017/LHC17d2b_cent_new");
			alienHandler->SetDataPattern("/AOD202/*/AliAOD.root");
		}else if (foption.Contains("LHC18m")){ 
			alienHandler->SetGridDataDir("/alice/data/2018/LHC18m");
			alienHandler->SetDataPattern("/pass1_withTRDtracking/AOD208/*/AliAOD.root");
		}else if (foption.Contains("LHC18b")
				|| foption.Contains("LHC18d")
				|| foption.Contains("LHC18e")
				|| foption.Contains("LHC18f")
				|| foption.Contains("LHC18g")
				|| foption.Contains("LHC18h")
				|| foption.Contains("LHC18i")
				|| foption.Contains("LHC18j")
				|| foption.Contains("LHC18k")
				|| foption.Contains("LHC18l")
				|| foption.Contains("LHC18n")
				|| foption.Contains("LHC18o")
				|| foption.Contains("LHC18p")
				){ 
			alienHandler->SetGridDataDir(Form("/alice/data/2018/%s",option));
			alienHandler->SetDataPattern("/pass1/AOD208/*/AliAOD.root");
		}else if (foption.Contains("LHC17c")
				|| foption.Contains("LHC17e")
				|| foption.Contains("LHC17f")
				|| foption.Contains("LHC17h")
				|| foption.Contains("LHC17i")
				|| foption.Contains("LHC17j")
				|| foption.Contains("LHC17k")
				|| foption.Contains("LHC17l")
				|| foption.Contains("LHC17m")
				|| foption.Contains("LHC17o")
				|| foption.Contains("LHC17r")
				){ 
			alienHandler->SetGridDataDir(Form("/alice/data/2017/%s",option));
			alienHandler->SetDataPattern("/pass1/AOD208/*/AliAOD.root");
		}else if (foption.Contains("LHC16k")
				|| foption.Contains("LHC16l")
				){
			alienHandler->SetGridDataDir(Form("/alice/data/2016/%s",option));
			alienHandler->SetDataPattern("/pass2/AOD208/*/AliAOD.root");
		}else if (foption.Contains("LHC16d")
				|| foption.Contains("LHC16e")
				|| foption.Contains("LHC16g")
				|| foption.Contains("LHC16h")
				|| foption.Contains("LHC16j")
				|| foption.Contains("LHC16o")
				|| foption.Contains("LHC16p")
				){
			alienHandler->SetGridDataDir(Form("/alice/data/2016/%s",option));
			alienHandler->SetDataPattern("/pass1/AOD208/*/AliAOD.root");
		}else if (foption.Contains("LHC16q")
				|| foption.Contains("LHC16t")
				){
			alienHandler->SetGridDataDir(Form("/alice/data/2016/%s",option));
			alienHandler->SetDataPattern("/pass1_CENT_wSDD/AOD190/*/AliAOD.root");
		}
		// MC has no prefix, data has prefix 000
		if(!ismc) alienHandler->SetRunPrefix("000");
		// runnumber
		for (unsigned int ii=0; ii<vec_run.size(); ii++){
		//for (unsigned int ii=0; ii<1; ii++){
			alienHandler->AddRunNumber(vec_run[ii]);
		}
		// number of files per subjob
		alienHandler->SetSplitMaxInputFileNumber(60);
		alienHandler->SetMasterResubmitThreshold(50);
		alienHandler->SetExecutable(Form("%s%s.sh",taskname,option));
		// specify how many seconds your job may take
		alienHandler->SetTTL(30000);
		alienHandler->SetJDLName(Form("%s%s.jdl",taskname,option));

		alienHandler->SetDropToShell(0);
		alienHandler->SetOutputToRunNo(kTRUE);
		alienHandler->SetKeepLogs(kTRUE);
		//alienHandler->SetDefaultOutputs(kFALSE);
		//alienHandler->SetOutputFiles("AnalysisResults.root");
		// merging: run with kTRUE to merge on grid
		// after re-running the jobs in SetRunMode("terminate") 
		// (see below) mode, set SetMergeViaJDL(kFALSE) 
		// to collect final results
		alienHandler->SetMaxMergeStages(1);
		//alienHandler->SetNrunsPerMaster(1);
		if ( strstr(mode,"full") || strstr(mode,"terminate") ){
			alienHandler->SetMergeViaJDL(kTRUE);
		}else{
			alienHandler->SetMergeViaJDL(kFALSE);
		}

		// define the output folders
		alienHandler->SetGridWorkingDir(Form("myWorkingDir%s%s",taskname,option));
		alienHandler->SetGridOutputDir("myOutputDir");
		//alienHandler->SetUseSubmitPolicy();

		// connect the alien plugin to the manager
		mgr->SetGridHandler(alienHandler);
		if(gridTest) {
			// speficy on how many files you want to run
			alienHandler->SetNtestFiles(1);
			// and launch the analysis
			alienHandler->SetRunMode("test");
			mgr->StartAnalysis("grid");
		} else {
			// else launch the full grid analysis
			if ( strstr(mode,"full") ){
				alienHandler->SetRunMode("full");
			}else{
				alienHandler->SetRunMode("terminate");
			}
			mgr->StartAnalysis("grid");
		}
	}
}
