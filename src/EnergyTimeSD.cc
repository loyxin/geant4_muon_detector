#include "EnergyTimeSD.hh"

#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>

EnergyTimeSD::EnergyTimeSD(G4String name) :
  G4VSensitiveDetector(name)
{
    collectionName.insert("energy_time");
}
#include <G4OpticalPhoton.hh>
#include <G4MuonPlus.hh>
#include <G4MuonMinus.hh>
G4bool EnergyTimeSD::ProcessHits(G4Step* aStep, G4TouchableHistory* /*ROhist*/)
{
    if (aStep == NULL) return false;
    G4Track* theTrack = aStep->GetTrack();
  

    if(theTrack->GetDefinition()
       !=G4MuonMinus::MuonMinus() && theTrack->GetDefinition()
       !=G4MuonPlus::MuonPlus() ) return false;
    
    G4double aDep = aStep->GetTotalEnergyDeposit();
    G4double time = aStep->GetPostStepPoint()->GetGlobalTime();
    G4ThreeVector position = aStep->GetPostStepPoint()->GetPosition();
    G4String name = aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName();

    EnergyTimeHit* hit = new EnergyTimeHit();
    hit->SetTime(time);
    hit->SetDeltaEnergy(aDep);
    hit->SetPosition(position);
    hit->SetName(name);

    fHitsCollection->insert(hit);

    return true;
}

void EnergyTimeSD::Initialize(G4HCofThisEvent* hcof)
{
    fHitsCollection = new EnergyTimeHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fHitsCollectionId < 0)
    {
        fHitsCollectionId = G4SDManager::GetSDMpointer()->GetCollectionID(GetName() + "/" + collectionName[0]);
    }
    hcof->AddHitsCollection(fHitsCollectionId, fHitsCollection);
}
