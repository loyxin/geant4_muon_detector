#include "muonSpecialCuts.hh"
#include "G4VParticleChange.hh"
#include "G4Track.hh"
#include "G4Step.hh"

muonSpecialCuts::muonSpecialCuts(const G4String& aName)
  : G4VProcess(aName)// 初始化 private 变量
{
  // verboseLevel 默认为0；
   if (verboseLevel>1) {
     G4cout << GetProcessName() << " is created "<< G4endl;
   }
}

muonSpecialCuts::~muonSpecialCuts()
{
}

G4VParticleChange* muonSpecialCuts::PostStepDoIt(
                             const G4Track& aTrack,
                             const G4Step&
                            )
//
// Stop the current particle, if requested by G4UserLimits
//
{
   aParticleChange.Initialize(aTrack);
   aParticleChange.ProposeEnergy(0.) ;
   aParticleChange.ProposeLocalEnergyDeposit (aTrack.GetKineticEnergy()) ;
   aParticleChange.ProposeTrackStatus(fStopButAlive);
   return &aParticleChange;
}

G4double muonSpecialCuts::PostStepGetPhysicalInteractionLength(
                             const G4Track&,
                             G4double,
                             G4ForceCondition*
                            )
{
  return DBL_MAX;
}
