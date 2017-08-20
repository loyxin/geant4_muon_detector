#include "muonEventAction.hh"

#include <G4SDManager.hh>
#include <G4THitsMap.hh>
#include <G4SystemOfUnits.hh>
#include <G4Event.hh>

#include "Analysis.hh"
#include "EnergyTimeHit.hh"
using namespace std;

muonEventAction::muonEventAction() : G4UserEventAction(){}

muonEventAction::~muonEventAction()
{}

void muonEventAction::EndOfEventAction(const G4Event* event)
{
    G4cout << "--------------End of EventAction--------------"<<G4endl;
    G4SDManager* sdm = G4SDManager::GetSDMpointer();
    G4AnalysisManager* analysis = G4AnalysisManager::Instance();

    G4HCofThisEvent* hcofEvent = event->GetHCofThisEvent();

    if(!hcofEvent) return;

    if(muondetectorETId < 0)
    {
      muondetectorETId = sdm->GetCollectionID("muondectorET/energy_time");
      G4cout << "EventAction: muonDetector energy/time scorer ID: " << muondetectorETId << G4endl;
    }

    G4int histogramId = 1;

    EnergyTimeHitsCollection* hitCollection =
    dynamic_cast<EnergyTimeHitsCollection*>(hcofEvent->GetHC(muondetectorETId));

    if (hitCollection)
    {
        for (auto hit: *hitCollection->GetVector())
        {

            analysis->FillNtupleDColumn(0, hit->GetDeltaEnergy() / MeV);
            analysis->FillNtupleDColumn(1, hit->GetTime() / ns);
            G4ThreeVector position = hit->GetPosition();
            analysis->FillNtupleDColumn(2, position.getX() / mm);
            analysis->FillNtupleDColumn(3, position.getY() / mm);
            analysis->FillNtupleDColumn(4, position.getZ() / mm);


            analysis->AddNtupleRow();
        }
    }
}
