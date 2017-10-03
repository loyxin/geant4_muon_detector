
#ifndef WLSDetectorMessenger_h
#define WLSDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

#include "muonDetectorConstruction.hh"
#include <G4UIcmdWith3VectorAndUnit.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIcmdWithABool.hh>
class G4UIdirectory;

class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithABool;

class muonDetectorConstruction;

class muonDetectorMessenger : public G4UImessenger
{
  public:

    muonDetectorMessenger(muonDetectorConstruction*);
    virtual ~muonDetectorMessenger();
 
    virtual void SetNewValue(G4UIcommand*, G4String);

  private:

    muonDetectorConstruction*   fDetector;
 
    G4UIdirectory*             fDetDir;
  
    G4UIcmdWith3VectorAndUnit* f1Position;
    G4UIcmdWith3VectorAndUnit* f2Position;

    G4UIcmdWithADoubleAndUnit* f1x;
    G4UIcmdWithADoubleAndUnit* f2x;

    G4UIcmdWithABool*  SDflag;

};

#endif
