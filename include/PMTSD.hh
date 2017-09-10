/**
 * @file PMTSD.hh
 * @brief pmt的敏感探测器类
 * @author loyxin
 * @version 1.0
 * @date 2017-09-10
 */
#ifndef PMTSD_HH
#define PMTSD_HH 1

#include <G4VSensitiveDetector.hh>

#include "PMThit.hh"
/**
 * @brief pmt的敏感探测器类
 */
class PMTSD : public G4VSensitiveDetector
{
public:
    PMTSD(G4String name);

    void Initialize(G4HCofThisEvent*) override;

protected:
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist) override;

private:
    pmtHitsCollection* fHitsCollection { nullptr };
    G4int fHitsCollectionId { -1 };
};


#endif