#include "G4VModularPhysicsList.hh"
/**
 *  * Enable physics lists.
 *   * Physics lists have to be enabled when Geant4 is at PreInit state. All UI
 *    * commands defined here have to be put before /run/Initialize in a mac file.
 *     */
#include "G4UImessenger.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAString.hh"
class Physics: public G4VModularPhysicsList, public G4UImessenger
{
       public:
         Physics();
         ~Physics() { delete fCmd;  }
         void SetNewValue(G4UIcommand* cmd, G4String value); ///< for G4UI
       private:
         G4UIcmdWithAString* fCmd;

};
