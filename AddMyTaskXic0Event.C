AliAnalysisTaskSEXic0SemileptonicEvent* AddMyTaskXic0Event(TString name = "name", TString option = "option")
{
    // get the manager via the static access member. since it's static, you don't need
    // to create an instance of the class here to call the function
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) {
        return 0x0;
    }

    // get the input event handler, again via a static method. 
    // this handler is part of the managing system and feeds events
    // to your task
    if (!mgr->GetInputEventHandler()) {
        return 0x0;
    }

		// now we create an instance of your task
		AliAnalysisTaskSEXic0SemileptonicEvent* task = new AliAnalysisTaskSEXic0SemileptonicEvent(name.Data(), Form("%s%s",name.Data(),option.Data()));   
		if(!task) return 0x0;
		// add your task to the manager
		mgr->AddTask(task);

		TString fileName = AliAnalysisManager::GetCommonFileName();

		// Create containers for input/output
		AliAnalysisDataContainer *cinput = mgr->GetCommonInputContainer();
		//AliAnalysisDataContainer *coutput1 = mgr->CreateContainer("histogram", TDirectory::Class(), AliAnalysisManager::kOutputContainer, fileName.Data());
		//AliAnalysisDataContainer *coutput2 = mgr->CreateContainer("cut", TList::Class(), AliAnalysisManager::kOutputContainer, fileName.Data());
		//AliAnalysisDataContainer *coutput3 = mgr->CreateContainer("MCCutTree", TTree::Class(), AliAnalysisManager::kOutputContainer, fileName.Data());
		//AliAnalysisDataContainer *coutput4 = mgr->CreateContainer("PairTree", TTree::Class(), AliAnalysisManager::kOutputContainer, fileName.Data());
		//AliAnalysisDataContainer *coutput5 = mgr->CreateContainer("MCPairTree", TTree::Class(), AliAnalysisManager::kOutputContainer, fileName.Data());
		AliAnalysisDataContainer *coutput6 = mgr->CreateContainer("EventTree", TTree::Class(), AliAnalysisManager::kOutputContainer, fileName.Data());
		//AliAnalysisDataContainer *coutput7 = mgr->CreateContainer("eleXiCounter", AliNormalizationCounter::Class(), AliAnalysisManager::kOutputContainer, fileName.Data()); //counter

		mgr->ConnectInput(task, 0, cinput);
		//mgr->ConnectOutput(task, 1, coutput1);
		//mgr->ConnectOutput(task, 2, coutput2);
		//mgr->ConnectOutput(task, 3, coutput3);
		//mgr->ConnectOutput(task, 4, coutput4);
		//mgr->ConnectOutput(task, 5, coutput5);
		mgr->ConnectOutput(task, 6, coutput6);
		//mgr->ConnectOutput(task, 7, coutput7);

    // in the end, this macro returns a pointer to your task. this will be convenient later on
    // when you will run your analysis in an analysis train on grid
    return task;
}
