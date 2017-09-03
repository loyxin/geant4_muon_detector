
#include "blankPhysics.hh"

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

blankPhysics::blankPhysics() : G4VUserPhysicsList()
{

    SetCuts();
}
blankPhysics::~blankPhysics(){

}
#include "G4ShortLivedConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
void blankPhysics::ConstructParticle()
{
    // pseudo-particles
    G4Geantino::GeantinoDefinition();
    G4ChargedGeantino::ChargedGeantinoDefinition();

    // gamma
    G4Gamma::GammaDefinition();

    //OpticalPhotons
    G4OpticalPhoton::OpticalPhotonDefinition();

    G4Electron::ElectronDefinition();
    G4Positron::PositronDefinition();
    G4MuonPlus::MuonPlusDefinition();
    G4MuonMinus::MuonMinusDefinition();

    G4NeutrinoE::NeutrinoEDefinition();
    G4AntiNeutrinoE::AntiNeutrinoEDefinition();
    G4NeutrinoMu::NeutrinoMuDefinition();
    G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();

    //  mesons
    G4MesonConstructor mConstructor;
    mConstructor.ConstructParticle();

    //  baryons
    G4BaryonConstructor bConstructor;
    bConstructor.ConstructParticle();

    //  ions
    G4IonConstructor iConstructor;
    iConstructor.ConstructParticle();

    G4ShortLivedConstructor slConstructor;
    slConstructor.ConstructParticle();

}

void blankPhysics::ConstructProcess()
{

    AddTransportation();

    ConstructEM();

    ConstructOp();

}


void blankPhysics::ConstructEM() {

}


void blankPhysics::ConstructOp()
{
    
}