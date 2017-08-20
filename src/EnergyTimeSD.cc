#include "EnergyTimeSD.hh"

#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>

EnergyTimeSD::EnergyTimeSD(G4String name) :
  G4VSensitiveDetector(name)
{
    collectionName.insert("energy_time");
}

G4bool EnergyTimeSD::ProcessHits(G4Step* aStep, G4TouchableHistory* /*ROhist*/)
{
    G4double aDep = aStep->GetTotalEnergyDeposit();
    G4double time = aStep->GetPostStepPoint()->GetGlobalTime();
    G4ThreeVector position = aStep->GetPostStepPoint()->GetPosition();

    EnergyTimeHit* hit = new EnergyTimeHit();
    hit->SetTime(time);
    hit->SetDeltaEnergy(aDep);
    hit->SetPosition(position);

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
