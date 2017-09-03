
#include "blankRunAction.hh"
#include "blankPrimaryGeneratorAction.hh"
#include "blankDetectorConstruction.hh"


#include "G4RunManager.hh"
#include "G4Run.hh"

blankRunAction::blankRunAction()
: G4UserRunAction()
{ 
}


blankRunAction::~blankRunAction()
{
}



void blankRunAction::BeginOfRunAction(const G4Run*)
{ 
}



void blankRunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
  
  G4cout
     << G4endl
     << " The run consists of " << nofEvents << " "
     << G4endl

     << "------------------------------------------------------------"
     << G4endl
     << G4endl;
}
