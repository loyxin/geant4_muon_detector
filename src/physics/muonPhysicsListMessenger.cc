
#include "globals.hh"

#include "muonPhysicsListMessenger.hh"
#include "muonPhysicsList.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

#include "G4PhaseSpaceDecayChannel.hh"
#include "G4PionRadiativeDecayChannel.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

muonPhysicsListMessenger::muonPhysicsListMessenger(muonPhysicsList* pPhys)
  : fPhysicsList(pPhys)
{

    fDirectory = new G4UIdirectory("/muon/phys/");
    fDirectory->SetGuidance("muonPhysicsList control");
 
    fSetAbsorptionCMD = new G4UIcmdWithABool("/muon/setAbsorption", this);
    fSetAbsorptionCMD->SetGuidance("Turn on or off absorption process");
    fSetAbsorptionCMD->AvailableForStates(G4State_Idle);

    fVerboseCmd = new G4UIcmdWithAnInteger("/muon/phys/verbose",this);
    fVerboseCmd->SetGuidance("set verbose for physics processes");
    fVerboseCmd->SetParameterName("verbose",true);
    fVerboseCmd->SetDefaultValue(1);
    fVerboseCmd->SetRange("verbose>=0");
    fVerboseCmd->AvailableForStates(G4State_Idle);
 
    fCerenkovCmd =
                new G4UIcmdWithAnInteger("/muon/phys/cerenkovMaxPhotons",this);
    fCerenkovCmd->SetGuidance("set max nb of photons per step");
    fCerenkovCmd->SetParameterName("MaxNumber",false);
    fCerenkovCmd->SetRange("MaxNumber>=0");
    fCerenkovCmd->AvailableForStates(G4State_Idle);

    fGammaCutCMD = new G4UIcmdWithADoubleAndUnit("/muon/phys/gammaCut",this);
    fGammaCutCMD->SetGuidance("Set gamma cut");
    fGammaCutCMD->SetParameterName("Gcut",false);
    fGammaCutCMD->SetUnitCategory("Length");
    fGammaCutCMD->SetRange("Gcut>0.0");
    fGammaCutCMD->SetDefaultUnit("mm");
    fGammaCutCMD->AvailableForStates(G4State_PreInit,G4State_Idle);

    fElectCutCMD = new G4UIcmdWithADoubleAndUnit("/muon/phys/electronCut",this);
    fElectCutCMD->SetGuidance("Set electron cut");
    fElectCutCMD->SetParameterName("Ecut",false);
    fElectCutCMD->SetUnitCategory("Length");
    fElectCutCMD->SetRange("Ecut>0.0");
    fElectCutCMD->SetDefaultUnit("mm");
    fElectCutCMD->AvailableForStates(G4State_PreInit,G4State_Idle);

    fPosCutCMD = new G4UIcmdWithADoubleAndUnit("/muon/phys/positronCut",this);
    fPosCutCMD->SetGuidance("Set positron cut");
    fPosCutCMD->SetParameterName("Pcut",false);
    fPosCutCMD->SetUnitCategory("Length");
    fPosCutCMD->SetRange("Pcut>0.0");
    fPosCutCMD->SetDefaultUnit("mm");
    fPosCutCMD->AvailableForStates(G4State_PreInit,G4State_Idle);

    fAllCutCMD = new G4UIcmdWithADoubleAndUnit("/muon/phys/allCuts",this);
    fAllCutCMD->SetGuidance("Set cut for all");
    fAllCutCMD->SetParameterName("cut",false);
    fAllCutCMD->SetUnitCategory("Length");
    fAllCutCMD->SetRange("cut>0.0");
    fAllCutCMD->SetDefaultUnit("mm");
    fAllCutCMD->AvailableForStates(G4State_PreInit,G4State_Idle);

    fStepMaxCMD = new G4UIcmdWithADoubleAndUnit("/muon/phys/stepMax",this);
    fStepMaxCMD->SetGuidance("Set max. step length in the detector");
    fStepMaxCMD->SetParameterName("mxStep",false);
    fStepMaxCMD->SetUnitCategory("Length");
    fStepMaxCMD->SetRange("mxStep>0.0");
    fStepMaxCMD->SetDefaultUnit("mm");
    fStepMaxCMD->AvailableForStates(G4State_PreInit,G4State_Idle);

    fClearPhysicsCMD =
                  new G4UIcmdWithoutParameter("/muon/phys/clearPhysics",this);
    fClearPhysicsCMD->SetGuidance("Clear the physics list");
    fClearPhysicsCMD->AvailableForStates(G4State_PreInit,G4State_Idle);

    fRemovePhysicsCMD = new G4UIcmdWithAString("/muon/phys/removePhysics",this);
    fRemovePhysicsCMD->
                     SetGuidance("Remove a physics process from Physics List");
    fRemovePhysicsCMD->SetParameterName("PList",false);
    fRemovePhysicsCMD->AvailableForStates(G4State_PreInit,G4State_Idle);

    fListCMD = new G4UIcmdWithoutParameter("/muon/phys/list",this);
    fListCMD->SetGuidance("Available Physics Lists");
    fListCMD->AvailableForStates(G4State_Idle);

    fDecayDirectory = new G4UIdirectory("/decay/");
    fDecayDirectory->SetGuidance("Decay chain control commands.");

    fPienuCMD = new G4UIcmdWithoutParameter("/decay/pienu", this);
    fPienuCMD->SetGuidance("Sets the pi+ to decay into e+, nu");

    fPimunuCMD = new G4UIcmdWithoutParameter("/decay/pimunu", this);
    fPimunuCMD->SetGuidance("Sets the pi+ to decay into mu+, nu");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

muonPhysicsListMessenger::~muonPhysicsListMessenger()
{
    delete fVerboseCmd;
    delete fCerenkovCmd;

    delete fSetAbsorptionCMD;

    delete fGammaCutCMD;
    delete fElectCutCMD;
    delete fPosCutCMD;
    delete fAllCutCMD;

    delete fClearPhysicsCMD;
    delete fRemovePhysicsCMD;

    delete fListCMD;

    delete fPienuCMD;
    delete fPimunuCMD;

    delete fDirectory;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void muonPhysicsListMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{
    if( command == fSetAbsorptionCMD ) {
       fPhysicsList->SetAbsorption(G4UIcmdWithABool::GetNewBoolValue(newValue));
    }

    else if( command == fVerboseCmd ) {
       fPhysicsList->SetVerbose(fVerboseCmd->GetNewIntValue(newValue));
    }

    else if( command == fCerenkovCmd ) {
       fPhysicsList->
           SetNbOfPhotonsCerenkov(fCerenkovCmd->GetNewIntValue(newValue));
    }

    else if (command == fPienuCMD) {
       G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
       G4ParticleDefinition* particleDef = particleTable->FindParticle("pi+");
       G4VDecayChannel* mode = 
                        new G4PhaseSpaceDecayChannel("pi+",1.0,2,"e+","nu_e");
       G4DecayTable* table = new G4DecayTable();
       table->Insert(mode);
      // mode = new G4PionRadiativeDecayChannel("pi+",0.000017);
      // table->Insert(mode);
       particleDef->SetDecayTable(table);
    }

    else if (command == fPimunuCMD) {
       G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
       G4ParticleDefinition* particleDef = particleTable->FindParticle("pi+");
       G4VDecayChannel* mode =
                     new G4PhaseSpaceDecayChannel("pi+",1.000,2,"mu+","nu_mu");
       G4DecayTable* table = new G4DecayTable();
       table->Insert(mode);
       particleDef->SetDecayTable(table);
    }

    else if (command == fGammaCutCMD) {
        fPhysicsList->SetCutForGamma(fGammaCutCMD
                                     ->GetNewDoubleValue(newValue));
    }
    else if (command == fElectCutCMD) {
        fPhysicsList->SetCutForElectron(fElectCutCMD
                                     ->GetNewDoubleValue(newValue));
    }
    else if (command == fPosCutCMD) {
        fPhysicsList->SetCutForPositron(fPosCutCMD
                                     ->GetNewDoubleValue(newValue));
    }
    else if (command == fAllCutCMD) {
        G4double cut = fAllCutCMD->GetNewDoubleValue(newValue);
        fPhysicsList->SetCutForGamma(cut);
        fPhysicsList->SetCutForElectron(cut);
        fPhysicsList->SetCutForPositron(cut);
    }
    else if (command == fStepMaxCMD) {
        fPhysicsList->SetStepMax(fStepMaxCMD
                                     ->GetNewDoubleValue(newValue));
    }
    else if (command == fClearPhysicsCMD) {
        fPhysicsList->ClearPhysics();
    }
    else if (command == fRemovePhysicsCMD) {
        G4String name = newValue;
        fPhysicsList->RemoveFromPhysicsList(name);
    }
}
