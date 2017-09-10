/**
 * @file muonRunAction.cc
 * @brief 打开 csv 文件，文件名，声明哪些数据被保存
 * @author loyxin
 * @version 1.0
 * @date 2017-09-10
 */
#include "muonRunAction.hh"


#include <G4AccumulableManager.hh>
#include <G4SystemOfUnits.hh>

#include "Analysis.hh"

muonRunAction::muonRunAction(){

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	analysisManager->OpenFile("muon");

	analysisManager->SetVerboseLevel(1);
	analysisManager->SetFirstNtupleId(1);
	analysisManager->SetFirstHistoId(1);

	//   EnergyDeposit, Time, X, Y & Z id = 1
	analysisManager->CreateNtuple("pmt", "Energy and time");
	analysisManager->CreateNtupleDColumn("EnergyDeposit/Mev");
	analysisManager->CreateNtupleDColumn("Time/ns");
	analysisManager->CreateNtupleDColumn("PMT");
	analysisManager->CreateNtupleDColumn("EventID");
	analysisManager->FinishNtuple(1);
	// id = 2
	analysisManager->CreateNtuple("detector", "Energy and time ");
	analysisManager->CreateNtupleDColumn("EnergyDeposit/Mev");
	analysisManager->CreateNtupleDColumn("z/mm");
	analysisManager->CreateNtupleDColumn("detector");
	analysisManager->CreateNtupleDColumn("EventID");
	analysisManager->FinishNtuple(2);




}

void muonRunAction::EndOfRunAction(const G4Run* run)
{
	G4int nofEvents = run->GetNumberOfEvent();
  	if (nofEvents == 0) return;
 if(IsMaster())
  {
  	G4cout
     << "\n--------------------End of Global Run-----------------------"
     << " \n The run was " << nofEvents << " events " << G4endl;

  }
 else
  {
    G4cout<<"no"<<G4endl;
  }

}

muonRunAction::~muonRunAction()
{
	G4AnalysisManager* man = G4AnalysisManager::Instance();
	  man->Write();
	  man->CloseFile();
}
