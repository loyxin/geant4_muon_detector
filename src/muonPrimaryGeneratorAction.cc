
#include "muonPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//#include "G4GeneralParticleSource.hh"

using namespace std;

muonPrimaryGeneratorAction::muonPrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction(), fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;

  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="mu-");

  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,-1.));
  // G4double sigma = 2;
	// TRandom3 r(0);
  // G4double energySpd = 1E-3;
	G4double energy = 4.*GeV;
	fParticleGun->SetParticleEnergy(energy);
  // fParticleGun->SetParticleEnergy(4.*GeV);
}


muonPrimaryGeneratorAction::~muonPrimaryGeneratorAction()
{
  delete fParticleGun;
}


void muonPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event

  G4double x0=0.,y0=0.;

  // G4double size = 0.7;
  // G4double x0 = size * envSizeXY * (G4UniformRand()-0.5);
  // G4double y0 = size * envSizeXY * (G4UniformRand()-0.5);
  G4double z0 = 0.5 * 2 * m;

  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  // vertex 顶点
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
