/**
 * @file muonSteppingAction.cc
 * @brief 暂时没有动作
 * @author loyxin
 * @version 1.0
 * @date 2017-09-10
 */
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
    G4Track* theTrack = theStep->GetTrack();
    G4StepPoint* thePrePoint  = theStep->GetPreStepPoint();
    G4StepPoint* thePostPoint = theStep->GetPostStepPoint();

    G4VPhysicalVolume* thePrePV  = thePrePoint->GetPhysicalVolume();
    G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();

    G4String thePrePVname  = " ";
    G4String thePostPVname = " ";

    if (thePostPV) {
        thePrePVname  = thePrePV->GetName();
        thePostPVname = thePostPV->GetName();
     }


    G4ThreeVector position =thePrePoint->GetPosition();
    // if(thePrePV->GetName()=="Al2O32" && 
    // theTrack->GetDefinition()==G4MuonMinus::MuonMinus()) 
    // G4cout<<"arrival time "<<"   "<< thePrePoint->GetGlobalTime()
    // <<G4endl;

    // if(theTrack->GetDefinition()==G4AntiNeutrinoE::AntiNeutrinoE()) 
    // G4cout<<"binggottttt---"<<"   "<<position.getX()<<"  volume "<<thePrePV->GetName()
    // << " time  "<< thePrePoint->GetGlobalTime()
    // <<G4endl;
}
