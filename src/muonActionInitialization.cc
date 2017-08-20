
#include "muonActionInitialization.hh"
#include "muonPrimaryGeneratorAction.hh"
#include "muonRunAction.hh"
#include "muonEventAction.hh"

muonActionInitialization::muonActionInitialization()
 : G4VUserActionInitialization()
{}

muonActionInitialization::~muonActionInitialization()
{}

void muonActionInitialization::BuildForMaster() const
{

}


void muonActionInitialization::Build() const
{
  SetUserAction(new muonPrimaryGeneratorAction());
  muonRunAction* runAction = new muonRunAction;
  SetUserAction(runAction);
  SetUserAction(new muonEventAction(runAction));

}
