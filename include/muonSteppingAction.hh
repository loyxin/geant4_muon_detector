#ifndef MUONSTEPPINGACTION_h
#define MUONSTEPPINGACTION_h 1

#include <G4UserSteppingAction.hh>
#include <globals.hh>

class muonEventAction;

class muonSteppingAction : public G4UserSteppingAction
{
  public:
    muonSteppingAction(muonEventAction*  eventAction);
    virtual ~muonSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    muonEventAction*  fEventAction;
};

#endif