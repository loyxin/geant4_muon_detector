

#ifndef muonPhysicsList_h
#define muonPhysicsList_h 1

#include "globals.hh"
#include "G4VModularPhysicsList.hh"

class G4VPhysicsConstructor;
class muonPhysicsListMessenger;

class muonStepMax;
class muonOpticalPhysics;

class muonPhysicsList: public G4VModularPhysicsList
{
  public:

    muonPhysicsList(G4String);
    virtual ~muonPhysicsList();

    void SetCuts();
    void SetCutForGamma(G4double);
    void SetCutForElectron(G4double);
    void SetCutForPositron(G4double);

    void SetStepMax(G4double);
    muonStepMax* GetStepMaxProcess();
    void AddStepMax();

    /// Remove specific physics from physics list.
    void RemoveFromPhysicsList(const G4String&);

    /// Make sure that the physics list is empty.
    void ClearPhysics();

    virtual void ConstructParticle();
    virtual void ConstructProcess();

    // Turn on or off the absorption process
    void SetAbsorption(G4bool);

    void SetNbOfPhotonsCerenkov(G4int);

    void SetVerbose(G4int);

private:

    G4double fCutForGamma;
    G4double fCutForElectron;
    G4double fCutForPositron;

    muonStepMax* fStepMaxProcess;

    muonOpticalPhysics* fOpticalPhysics;

    muonPhysicsListMessenger* fMessenger;

    G4bool fAbsorptionOn;
    
    G4VMPLData::G4PhysConstVectorData* fPhysicsVector;

};

#endif
