//
#include "G4VModularPhysicsList.hh"
#include "Physics.hh"
/**
 * Enable physics lists.
 * Physics lists have to be enabled when Geant4 is at PreInit state. All UI
 * commands defined here have to be put before /run/Initialize in a mac file.
 */
//______________________________________________________________________________
//
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
Physics::Physics() : G4VModularPhysicsList(), G4UImessenger()
{
   fCmd = new G4UIcmdWithAString("/physics_lists/enable",this);
   fCmd->SetGuidance("Enable a certain physics list");
   fCmd->SetParameterName("name of a physics list", false);
   fCmd->SetCandidates("Optical HadronElastic HadronInelastic");
   fCmd->AvailableForStates(G4State_PreInit);

   RegisterPhysics(new G4DecayPhysics()); // defined many particles
   RegisterPhysics(new G4RadioactiveDecayPhysics());
   RegisterPhysics(new G4EmStandardPhysics()); // must be after RadioactiveDecay
}
//______________________________________________________________________________
//
#include "G4OpticalPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh" // won't work for Geant4 version<10
void Physics::SetNewValue(G4UIcommand* cmd, G4String value)
{
   if (cmd==fCmd) {
      if (value=="Optical") RegisterPhysics(new G4OpticalPhysics());
      else if (value=="HadronElastic")
         RegisterPhysics(new G4HadronElasticPhysicsHP());
      else if (value=="HadronInelastic")
         RegisterPhysics(new G4HadronPhysicsFTFP_BERT_HP());
   }
}
