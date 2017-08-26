#include "muonEventAction.hh"

#include <G4SDManager.hh>
#include <G4THitsMap.hh>
#include <G4SystemOfUnits.hh>
#include <G4Event.hh>

#include "Analysis.hh"
#include "EnergyTimeHit.hh"
#include "PMThit.hh"
using namespace std;

muonEventAction::muonEventAction() : G4UserEventAction(){}

muonEventAction::~muonEventAction()
{}

void muonEventAction::EndOfEventAction(const G4Event* event)
{
    G4int eventID = event->GetEventID();
    G4cout << "--------------End of EventAction--------------"<<eventID<<G4endl;
    G4SDManager* sdm = G4SDManager::GetSDMpointer();
    G4AnalysisManager* analysis = G4AnalysisManager::Instance();

    G4HCofThisEvent* hcofEvent = event->GetHCofThisEvent();

    if(!hcofEvent) return;

    if(muondetectorEnId < 0)
    {
      muondetectorEnId = sdm->GetCollectionID("muondectorEn/energy_time");
      G4cout << "EventAction: muonDetector energy scorer ID: " << muondetectorEnId << G4endl;

    }

    if( PMT_Id < 0)
    {
      PMT_Id = sdm->GetCollectionID("PMT_ET/pmt_energy_time");
      G4cout << "EventAction: PMT pmt_energy_time scorer ID: " << PMT_Id << G4endl;
    }

    EnergyTimeHitsCollection* muhitCollection =
    dynamic_cast<EnergyTimeHitsCollection*>(hcofEvent->GetHC(muondetectorEnId));

    if (muhitCollection)
    {
        for (auto hit: *muhitCollection->GetVector())
        {
            analysis->FillNtupleDColumn(2, 0, hit->GetDeltaEnergy() / MeV);
            analysis->FillNtupleDColumn(2,1, hit->GetTime() / ns);
            analysis->FillNtupleDColumn(2,3, eventID);
            if(hit->GetName()=="muondector1")
                analysis->FillNtupleDColumn(2,2,1);
            if(hit->GetName()=="muondector2")
                analysis->FillNtupleDColumn(2,2,2);
            analysis->AddNtupleRow(2);
        }
    }


    pmtHitsCollection* hitCollection =
    dynamic_cast<pmtHitsCollection*>(hcofEvent->GetHC(PMT_Id));

    if (hitCollection)
    {
        for (auto hit: *hitCollection->GetVector())
        {

            analysis->FillNtupleDColumn(1, 0, hit->GetDeltaEnergy() / MeV);
            analysis->FillNtupleDColumn(1,1, hit->GetTime() / ns);
            if(hit->GetName()=="PMT1") // value 1
                analysis->FillNtupleDColumn(1,2,1);
            if(hit->GetName()=="PMT2") //value 2
                analysis->FillNtupleDColumn(1,2,2);

            analysis->FillNtupleDColumn(1,3, eventID);
            analysis->AddNtupleRow(1);
        }
    }
   


}
