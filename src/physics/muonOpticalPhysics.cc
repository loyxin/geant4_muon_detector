

#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"

#include "muonOpticalPhysics.hh"

#include "G4PhotoElectricEffect.hh"
#include "G4LivermorePhotoElectricModel.hh"
muonOpticalPhysics::muonOpticalPhysics(G4bool toggle)
    : G4VPhysicsConstructor("Optical")
{
  fWLSProcess                = NULL;
  fScintProcess              = NULL;
  fCerenkovProcess           = NULL;
  fBoundaryProcess           = NULL;
  fAbsorptionProcess         = NULL;
  fRayleighScattering        = NULL;
  fMieHGScatteringProcess    = NULL;

  fAbsorptionOn              = toggle;
}

muonOpticalPhysics::~muonOpticalPhysics() { }

#include "G4OpticalPhoton.hh"

void muonOpticalPhysics::ConstructParticle()
{
  G4OpticalPhoton::OpticalPhotonDefinition();
}

#include "G4ProcessManager.hh"

void muonOpticalPhysics::ConstructProcess()
{
    G4cout << "muonOpticalPhysics:: Add Optical Physics Processes"
           << G4endl;

  fWLSProcess = new G4OpWLS();

  fScintProcess = new G4Scintillation();
  fScintProcess->SetScintillationYieldFactor(1.);
  fScintProcess->SetTrackSecondariesFirst(true);

  fCerenkovProcess = new G4Cerenkov();
  fCerenkovProcess->SetMaxNumPhotonsPerStep(300);
  fCerenkovProcess->SetTrackSecondariesFirst(true);

  fAbsorptionProcess      = new G4OpAbsorption();
  fRayleighScattering     = new G4OpRayleigh();
  fMieHGScatteringProcess = new G4OpMieHG();
  fBoundaryProcess        = new G4OpBoundaryProcess();

  G4ProcessManager* pManager =
                G4OpticalPhoton::OpticalPhoton()->GetProcessManager();

  if (!pManager) {
     std::ostringstream o;
     o << "Optical Photon without a Process Manager";
     G4Exception("WLSOpticalPhysics::ConstructProcess()","",
                  FatalException,o.str().c_str());
  }

  if (fAbsorptionOn) pManager->AddDiscreteProcess(fAbsorptionProcess);

  pManager->AddDiscreteProcess(fRayleighScattering);
  pManager->AddDiscreteProcess(fMieHGScatteringProcess);

  pManager->AddDiscreteProcess(fBoundaryProcess);
  G4PhotoElectricEffect* thePhotoElectricEffect = new G4PhotoElectricEffect();
  thePhotoElectricEffect->SetEmModel(new G4LivermorePhotoElectricModel());
  pManager->AddDiscreteProcess(thePhotoElectricEffect);
  
  fWLSProcess->UseTimeProfile("delta");
  //fWLSProcess->UseTimeProfile("exponential");

  pManager->AddDiscreteProcess(fWLSProcess);

  fScintProcess->SetScintillationYieldFactor(1.);
  fScintProcess->SetScintillationExcitationRatio(0.0);
  fScintProcess->SetTrackSecondariesFirst(true);

  // Use Birks Correction in the Scintillation process

  G4EmSaturation* emSaturation = G4LossTableManager::Instance()->EmSaturation();
  fScintProcess->AddSaturation(emSaturation);

  auto particleIterator=GetParticleIterator();
  particleIterator->reset();
  while ( (*particleIterator)() ){

    G4ParticleDefinition* particle = particleIterator->value();
    G4String particleName = particle->GetParticleName();

    pManager = particle->GetProcessManager();
    if (!pManager) {
       std::ostringstream o;
       o << "Particle " << particleName << "without a Process Manager";
       G4Exception("muonOpticalPhysics::ConstructProcess()","",
                    FatalException,o.str().c_str());
    }

    if(fCerenkovProcess->IsApplicable(*particle)){
      pManager->AddProcess(fCerenkovProcess);
      pManager->SetProcessOrdering(fCerenkovProcess,idxPostStep);
    }
    if(fScintProcess->IsApplicable(*particle)){
      pManager->AddProcess(fScintProcess);
      pManager->SetProcessOrderingToLast(fScintProcess,idxAtRest);
      pManager->SetProcessOrderingToLast(fScintProcess,idxPostStep);
    }

  }
}

void muonOpticalPhysics::SetNbOfPhotonsCerenkov(G4int maxNumber)
{
  fCerenkovProcess->SetMaxNumPhotonsPerStep(maxNumber);
}
