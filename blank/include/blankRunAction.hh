

#ifndef blankRunAction_h
#define blankRunAction_h 1

#include "G4UserRunAction.hh"

#include "globals.hh"

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class blankRunAction : public G4UserRunAction
{
  public:
    blankRunAction();
    virtual ~blankRunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

};

#endif

