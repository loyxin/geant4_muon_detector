
#include "blankPrimaryGeneratorAction.hh"


#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

blankPrimaryGeneratorAction::blankPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="gamma");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,-1.));
  fParticleGun->SetParticleEnergy(100*MeV);
}



blankPrimaryGeneratorAction::~blankPrimaryGeneratorAction()
{
  delete fParticleGun;
}



void blankPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  fParticleGun->SetParticlePosition(G4ThreeVector(0,0,1.*m));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}


