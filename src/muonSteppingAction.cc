#include "muonSteppingAction.hh"
#include "muonEventAction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include <G4StepPoint.hh>
#include "globals.hh"
muonSteppingAction::muonSteppingAction(muonEventAction* eventAction)
: G4UserSteppingAction(), fEventAction(eventAction)
{}

muonSteppingAction::~muonSteppingAction()
{

}
#include <G4Track.hh>
#include <G4AntiNeutrinoE.hh>
#include <G4VPhysicalVolume.hh>
#include <G4MuonMinus.hh>
void muonSteppingAction::UserSteppingAction(const G4Step* theStep)
{

}
