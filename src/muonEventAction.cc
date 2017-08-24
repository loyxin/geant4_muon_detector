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

    if(muondetectorEnId < 0)
    {
      muondetectorEnId = sdm->GetCollectionID("muondectorEn/enerygy");
      G4cout << "EventAction: muonDetector energy scorer ID: " << muondetectorEnId << G4endl;

    }

    if( PMT_Id < 0)
    {
      PMT_Id = sdm->GetCollectionID("PMT_ET/energy_time");
      G4cout << "EventAction: PMT energy/time scorer ID: " << PMT_Id << G4endl;
    }

    G4THitsMap<G4double>* hitMap =
    dynamic_cast<G4THitsMap<G4double>*>(hcofEvent->GetHC(muondetectorEnId));

    if (hitMap)
    {
        for (auto pair : *(hitMap->GetMap()))
        {
              G4double energy = *(pair.second);
              G4double x =  pair.first;
              analysis->FillNtupleDColumn(1,0, energy / MeV);
              analysis->AddNtupleRow();
        }
    }
   EnergyTimeHitsCollection* hitCollection =
    dynamic_cast<EnergyTimeHitsCollection*>(hcofEvent->GetHC(PMT_Id));

    if (hitCollection)
    {
        for (auto hit: *hitCollection->GetVector())
        {

            analysis->FillNtupleDColumn(2, 0, hit->GetDeltaEnergy() / MeV);
            analysis->FillNtupleDColumn(2,1, hit->GetTime() / ns);
            G4ThreeVector position = hit->GetPosition();
            analysis->FillNtupleDColumn(2,2, position.getX() / mm);
            analysis->FillNtupleDColumn(2,3, position.getY() / mm);
            analysis->FillNtupleDColumn(2,4, position.getZ() / mm);


            analysis->AddNtupleRow();
        }
    }
   
}
