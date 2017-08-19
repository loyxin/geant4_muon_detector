
#include "SFLeptonPhysics.hh"

#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4VModularPhysicsList.hh"

// particle
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"
#include "G4TauMinus.hh"
#include "G4TauPlus.hh"
#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"
#include "G4NeutrinoMu.hh"
#include "G4AntiNeutrinoMu.hh"
#include "G4NeutrinoTau.hh"
#include "G4AntiNeutrinoTau.hh"
#include "G4HadronElastic.hh"



SFLeptonPhysics::SFLeptonPhysics() :  G4VUserPhysicsList()
{
  // defaultCutValue     = 1.0*micrometer;
  // cutForGamma         = defaultCutValue;
  // cutForElectron      = 1.0*nanometer;
  // cutForPositron      = defaultCutValue;
    SetVerboseLevel(1);
}

SFLeptonPhysics::~SFLeptonPhysics()
{;}

void SFLeptonPhysics::ConstructAllParticle()
{

  G4BosonConstructor BConstructor;
  BConstructor.ConstructParticle();
  G4LeptonConstructor LConstructor;
  LConstructor.ConstructParticle();
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

void SFLeptonPhysics::ConstructParticle()
{

  ConstructAllParticle();


  //These are needed for the mu- capture
    G4Neutron::Neutron();
    G4Proton::Proton();
    G4PionMinus::PionMinus();
    G4PionZero::PionZero();
    G4PionPlus::PionPlus();
}
// processes
#include "G4ProcessManager.hh"
#include "G4ProcessTable.hh"
#include "G4ProcessVector.hh"

#include "G4hMultipleScattering.hh"
#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4hIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"
#include "G4eplusAnnihilation.hh"
#include "G4ElectronNuclearProcess.hh"
#include "G4PositronNuclearProcess.hh"
#include "G4ElectroVDNuclearModel.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4MuonMinusCapture.hh"

#include "G4NeutronInelasticProcess.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4NeutronCaptureXS.hh"
#include "G4NeutronRadCapture.hh"
#include "G4AntiNeutronInelasticProcess.hh"

#include "G4LFission.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4HadronFissionProcess.hh"
#include "G4HadronElasticProcess.hh"
#include "G4HadronCaptureProcess.hh"

#include "G4BGGNucleonInelasticXS.hh"

void SFLeptonPhysics::ConstructProcess()
{

  AddTransportation();

  ConstructElectronProcess();
  ConstructPositronProcess();
  ConstructMuProcess();
  ConstructTauProcess();
  ConstructNeutronProcess();
  ConstructProtonProcess();
  ConstructPionProcess();

}


// Transportation ///////////////////////////////////////////////////////////
#include "muonMaxTimeCuts.hh"
#include "muonMinEkineCuts.hh"
#include "G4StepLimiter.hh"

void SFLeptonPhysics::AddTransportation()
{

  G4VUserPhysicsList::AddTransportation();

  auto particleIterator=GetParticleIterator();
  particleIterator->reset();
  while( (*particleIterator)() ){
    G4ParticleDefinition* particle = particleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    // time cuts for ONLY neutrons:
    if(particleName == "neutron")
      pmanager->AddDiscreteProcess(new muonMaxTimeCuts( ));
    // Energy cuts to kill charged (embedded in method) particles:
    pmanager->AddDiscreteProcess(new muonMinEkineCuts( ));

    // Step limit applied to all particles:
    pmanager->AddProcess(new G4StepLimiter,       -1,-1,1);

  }
}

void SFLeptonPhysics::ConstructElectronProcess()
{
  G4ProcessManager* pManager = 0;

  pManager = G4Electron::Electron()->GetProcessManager();
  pManager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4eIonisation(),        -1, 2, 2);
  pManager->AddProcess(new G4eBremsstrahlung(),    -1, 3, 3);

  G4ElectroVDNuclearModel* theElectroReaction = new G4ElectroVDNuclearModel();
  G4ElectronNuclearProcess* theElectronNuclearProcess = new G4ElectronNuclearProcess();
  theElectronNuclearProcess->RegisterMe(theElectroReaction);
  pManager->AddDiscreteProcess(theElectronNuclearProcess);


}

void SFLeptonPhysics::ConstructPositronProcess()
{
  G4ProcessManager* pManager = 0;

  //Positron physics
  pManager = G4Positron::Positron()->GetProcessManager();
  pManager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4eIonisation(),        -1, 2, 2);
  pManager->AddProcess(new G4eBremsstrahlung(),    -1, 3, 3);
  pManager->AddProcess(new G4eplusAnnihilation(),   0,-1, 4);

  G4ElectroVDNuclearModel* theElectroReaction = new G4ElectroVDNuclearModel();
  G4PositronNuclearProcess* thePositronNuclearProcess = new G4PositronNuclearProcess();
  thePositronNuclearProcess->RegisterMe(theElectroReaction);
  pManager->AddDiscreteProcess(thePositronNuclearProcess);

}
#include "G4MuMinusCapturePrecompound.hh"
void SFLeptonPhysics::ConstructMuProcess()
{
  G4ProcessManager* pManager = 0;
  //mu
  G4MuIonisation* fMuPlusIonisation = new G4MuIonisation();
  G4MuMultipleScattering* fMuPlusMultipleScattering = new G4MuMultipleScattering();
  G4MuBremsstrahlung* fMuPlusBremsstrahlung= new G4MuBremsstrahlung();
  G4MuPairProduction* fMuPlusPairProduction= new G4MuPairProduction();

  G4MuIonisation* fMuMinusIonisation = new G4MuIonisation();
  G4MuMultipleScattering* fMuMinusMultipleScattering = new G4MuMultipleScattering();
  G4MuBremsstrahlung* fMuMinusBremsstrahlung = new G4MuBremsstrahlung();
  G4MuPairProduction* fMuMinusPairProduction = new G4MuPairProduction();
  G4MuonMinusCapture* fMuMinusCaptureAtRest = new G4MuonMinusCapture(new G4MuMinusCapturePrecompound());

  // Muon Plus Physics
  pManager = G4MuonPlus::MuonPlus()->GetProcessManager();

  pManager->AddProcess(fMuPlusMultipleScattering,-1,  1, 1);
  pManager->AddProcess(fMuPlusIonisation,        -1,  2, 2);
  pManager->AddProcess(fMuPlusBremsstrahlung,    -1,  3, 3);
  pManager->AddProcess(fMuPlusPairProduction,    -1,  4, 4);

  // Muon Minus Physics
  pManager = G4MuonMinus::MuonMinus()->GetProcessManager();

  pManager->AddProcess(fMuMinusMultipleScattering,-1,  1, 1);
  pManager->AddProcess(fMuMinusIonisation,        -1,  2, 2);
  pManager->AddProcess(fMuMinusBremsstrahlung,    -1,  3, 3);
  pManager->AddProcess(fMuMinusPairProduction,    -1,  4, 4);

  pManager->AddRestProcess(fMuMinusCaptureAtRest);

}

void SFLeptonPhysics::ConstructTauProcess()
{
  G4ProcessManager* pManager = 0;

  // Tau-
  G4ParticleDefinition* particle=G4TauMinus::TauMinusDefinition();
  pManager = particle->GetProcessManager();
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // Tau+
  //
  pManager = G4TauPlus::TauPlus()->GetProcessManager();
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

}

void SFLeptonPhysics::ConstructNeutronProcess()
{
  G4ProcessManager* pManager = 0;
  pManager = G4Neutron::Neutron()->GetProcessManager();
  G4ParticleDefinition* neutron = G4Neutron::Neutron();
  G4ProcessTable* processTable = G4ProcessTable::GetProcessTable();
  G4VProcess* process = 0;
  process = processTable->FindProcess("hadElastic", neutron);
  if (process) pManager->RemoveProcess(process);

  process = processTable->FindProcess("neutronInelastic", neutron);
  if (process) pManager->RemoveProcess(process);

  process = processTable->FindProcess("nCapture", neutron);
  if (process) pManager->RemoveProcess(process);

  process = processTable->FindProcess("nFission", neutron);
  if (process) pManager->RemoveProcess(process);

}

void SFLeptonPhysics::ConstructProtonProcess()
{
  G4ProcessManager* pManager = 0;

  pManager =  G4Proton::Proton()->GetProcessManager();
  pManager->AddProcess(new G4hIonisation(),     -1, 2, 2);
  pManager->AddProcess(new G4hBremsstrahlung(), -1, 3, 3);
  pManager->AddProcess(new G4hPairProduction(), -1, 4, 4);
}

void SFLeptonPhysics::ConstructPionProcess()
{
  G4ProcessManager* pManager = 0;
  // pi+
  pManager = G4PionPlus::PionPlus()->GetProcessManager();
  pManager->AddProcess(new G4hIonisation(),     -1, 2, 2);
  pManager->AddProcess(new G4hBremsstrahlung(), -1, 3, 3);
  pManager->AddProcess(new G4hPairProduction(), -1, 4, 4);

  // pi-
  pManager =  G4PionMinus::PionMinus()->GetProcessManager();
  pManager->AddProcess(new G4hIonisation(),     -1, 2, 2);
  pManager->AddProcess(new G4hBremsstrahlung(), -1, 3, 3);
  pManager->AddProcess(new G4hPairProduction(), -1, 4, 4);
}


void SFLeptonPhysics::SetCuts()
{
  SetCutsWithDefault();
}
