

#ifndef SFLeptonPhysics_hh
#define SFLeptonPhysics_hh

#include "G4VUserPhysicsList.hh"
#include "globals.hh"


class SFLeptonPhysics : public G4VUserPhysicsList
{
  public:
    SFLeptonPhysics();
    virtual ~SFLeptonPhysics();

    // This method will be invoked in the Construct() method.
    // each particle type will be instantiated
    void ConstructAllParticle();
    virtual void ConstructParticle();

    // This method will be invoked in the Construct() method.
    // each physics process will be instantiated and
    // registered to the process manager of each particle type
    virtual void ConstructProcess();
    void ConstructElectronProcess();
    void ConstructMuProcess();
    void ConstructPositronProcess();
    void ConstructTauProcess();
    void ConstructNeutronProcess();
    void ConstructProtonProcess();
    void ConstructPionProcess();
    void AddTransportation();
    virtual void SetCuts();
// private:
//   G4double defaultCutValue;
};

#endif
