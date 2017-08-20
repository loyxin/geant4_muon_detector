#ifndef ENERGYTIMESD_HH
#define ENERGYTIMESD_HH

#include <G4VSensitiveDetector.hh>

#include "EnergyTimeHit.hh"

class EnergyTimeSD : public G4VSensitiveDetector
{
public:
    EnergyTimeSD(G4String name);

    void Initialize(G4HCofThisEvent*) override;

protected:
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist) override;

private:
    EnergyTimeHitsCollection* fHitsCollection { nullptr };
    G4int fHitsCollectionId { -1 };
};

#endif
