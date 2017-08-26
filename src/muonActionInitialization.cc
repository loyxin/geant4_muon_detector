
#include "muonActionInitialization.hh"
#include "muonPrimaryGeneratorAction.hh"
#include "muonRunAction.hh"
#include "muonEventAction.hh"
#include "muonSteppingAction.hh"
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
  muonEventAction* event = new muonEventAction();
  SetUserAction(event);

  SetUserAction(new muonSteppingAction(event));

}
