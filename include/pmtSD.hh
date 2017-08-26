#ifndef PMTSD_HH
#define PMTSD_HH 1

#include <G4VSensitiveDetector.hh>

#include "PMThit.hh"

class pmtSD : public G4VSensitiveDetector
{
public:
    pmtSD(G4String name);

    void Initialize(G4HCofThisEvent*) override;

protected:
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist) override;

private:
    pmtHitsCollection* fHitsCollection { nullptr };
    G4int fHitsCollectionId { -1 };
};


#endif