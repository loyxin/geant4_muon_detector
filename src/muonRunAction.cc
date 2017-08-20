#include "muonRunAction.hh"


#include <G4AccumulableManager.hh>
#include <G4SystemOfUnits.hh>

muonRunAction::muonRunAction(){}

void muonRunAction::EndOfRunAction(const G4Run* run)
{
	G4int nofEvents = run->GetNumberOfEvent();
  	if (nofEvents == 0) return;
 if(IsMaster())
  {
  	G4cout
     << "\n--------------------End of Global Run-----------------------"
     << " \n The run was " << nofEvents << " events " << G4endl;
  }
 else
  {
    G4cout<<"no"<<G4endl;
  }

}

muonRunAction::~muonRunAction()
{

}
