#include "PhysicsList.hh"

#include <G4SystemOfUnits.hh>

#include <G4EmStandardPhysics.hh>
#include <G4DecayPhysics.hh>
#include <G4EmExtraPhysics.hh>

#include <G4LossTableManager.hh>
#include <G4ProcessManager.hh>


PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
  G4LossTableManager::Instance();
  defaultCutValue = 0.01*micrometer;
  fCutForGamma     = defaultCutValue;
  fCutForElectron  = defaultCutValue;
  fCutForPositron  = defaultCutValue;

  SetVerboseLevel(1);
  SetCuts();

  RegisterPhysics(new G4EmStandardPhysics());
  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4EmExtraPhysics());
}


PhysicsList::~PhysicsList()
{

}

void PhysicsList::ConstructParticle()
{
  G4VModularPhysicsList::ConstructParticle();
}


void PhysicsList::ConstructProcess()
{
    G4VModularPhysicsList::ConstructProcess();
  // transportation
  AddTransportation();


  // step limitation (as a full process)
  AddStepMax();

}


#include <G4StepLimiter.hh>

void PhysicsList::AddStepMax()
{
  // Step limitation seen as a process

  fStepMaxProcess = new G4StepLimiter();

  auto particleIterator=GetParticleIterator();

  particleIterator->reset();

  while ((*particleIterator)()){
      G4ParticleDefinition* particle = particleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();

    if (fStepMaxProcess->IsApplicable(*particle) && pmanager)
      {
	pmanager ->AddDiscreteProcess(fStepMaxProcess);
      }
  }
}


void PhysicsList::SetCuts()
{

  if (verboseLevel >0){
    G4cout << "PhysicsList::SetCuts:";
    G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
  }

  SetCutValue(fCutForGamma, "gamma");
  SetCutValue(fCutForElectron, "e-");
  SetCutValue(fCutForPositron, "e+");

  if (verboseLevel>0) DumpCutValuesTable();
}

#include <G4Gamma.hh>

void PhysicsList::SetCutForGamma(G4double cut)
{
  fCutForGamma = cut;
  SetParticleCuts(fCutForGamma, G4Gamma::Gamma());
}

#include <G4Electron.hh>

void PhysicsList::SetCutForElectron(G4double cut)
{
  fCutForElectron = cut;
  SetParticleCuts(fCutForElectron, G4Electron::Electron());
}

#include <G4Positron.hh>

void PhysicsList::SetCutForPositron(G4double cut)
{
  fCutForPositron = cut;
  SetParticleCuts(fCutForPositron, G4Positron::Positron());
}
