#ifndef MUONSPECIALCUTS_HH
#define MUONSPECIALCUTS_HH

#include "G4ios.hh"
#include "globals.hh"
#include "G4VProcess.hh"


class muonSpecialCuts : public G4VProcess
{
  public:

     muonSpecialCuts(const G4String& processName ="muonSpecialCut" );

     virtual ~muonSpecialCuts();

     virtual G4double PostStepGetPhysicalInteractionLength(
                             const G4Track& track,
                             G4double   previousStepSize,
                             G4ForceCondition* condition
                            );

     virtual G4VParticleChange* PostStepDoIt(
                             const G4Track& ,
                             const G4Step&
                            );

     //  no operation in  AtRestGPIL
     virtual G4double AtRestGetPhysicalInteractionLength(
                             const G4Track& ,
                             G4ForceCondition*
                            ){ return -1.0; };

     //  no operation in  AtRestDoIt
     virtual G4VParticleChange* AtRestDoIt(
                             const G4Track& ,
                             const G4Step&
                            ){return NULL;};

     //  no operation in  AlongStepGPIL
     virtual G4double AlongStepGetPhysicalInteractionLength(
                             const G4Track&,
                             G4double  ,
                             G4double  ,
                             G4double& ,
                             G4GPILSelection*
                            ){ return -1.0; };

     //  no operation in  AlongStepDoIt
     virtual G4VParticleChange* AlongStepDoIt(
                             const G4Track& ,
                             const G4Step&
                            ) {return NULL;};

  private:
  // hide assignment operator as private
     muonSpecialCuts& operator=(const muonSpecialCuts&){return *this;};

};

#endif // MUONSPECIALCUTS_HH
