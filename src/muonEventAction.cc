#include "muonEventAction.hh"

#include <G4SDManager.hh>
#include <G4THitsMap.hh>
#include <G4SystemOfUnits.hh>
#include <G4Event.hh>

#include "Analysis.hh"
#include "EnergyTimeHit.hh"
using namespace std;

muonEventAction::muonEventAction(muonRunAction* runAction) : G4UserEventAction(),frunAction(runAction){}

muonEventAction::~muonEventAction()
{}

void muonEventAction::EndOfEventAction(const G4Event* event)
{
    G4SDManager* sdm = G4SDManager::GetSDMpointer();
    G4AnalysisManager* analysis = G4AnalysisManager::Instance();

    G4HCofThisEvent* hcofEvent = event->GetHCofThisEvent();

    if(!hcofEvent) return;


}
