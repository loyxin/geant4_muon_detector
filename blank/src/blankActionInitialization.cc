

#include "blankActionInitialization.hh"
#include "blankPrimaryGeneratorAction.hh"
#include "blankRunAction.hh"

blankActionInitialization::blankActionInitialization()
 : G4VUserActionInitialization()
{}



blankActionInitialization::~blankActionInitialization()
{}



void blankActionInitialization::BuildForMaster() const
{
  blankRunAction* runAction = new blankRunAction;
  SetUserAction(runAction);
}


void blankActionInitialization::Build() const
{
  SetUserAction(new blankPrimaryGeneratorAction);

  blankRunAction* runAction = new blankRunAction;
  SetUserAction(runAction);
  
}  

