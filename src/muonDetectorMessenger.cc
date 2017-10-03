
#include "muonDetectorMessenger.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"


muonDetectorMessenger::muonDetectorMessenger(muonDetectorConstruction* det)
  : fDetector(det),G4UImessenger()
{
  fDetDir = new G4UIdirectory("/muondetector/");
  fDetDir->SetGuidance(" Geometry Setup ");


  f1Position = new G4UIcmdWith3VectorAndUnit("/muondetector/setDet1Position",this);
  f1Position->SetGuidance("Set the position of muondetector1");
  f1Position->SetParameterName( "PositionX", "PositionY", "PositionZ",false);
  f1Position->SetDefaultUnit("mm");
  f1Position->AvailableForStates(G4State_PreInit,G4State_Idle);


  f2Position = new G4UIcmdWith3VectorAndUnit("/muondetector/setDet2Position",this);
  f2Position->SetGuidance("Set the position of muondetector2");
  f2Position->SetParameterName( "PositionX", "PositionY", "PositionZ",false);
  f2Position->SetDefaultUnit("mm");
  f2Position->AvailableForStates(G4State_PreInit,G4State_Idle);

  f1x = new G4UIcmdWithADoubleAndUnit("/muondetector/setDet1thick",this);
  f1x->SetGuidance("Set the thickness of muondetector1");
  f1x->SetParameterName("x",false);
  f1x->SetRange("x>0.");
  f1x->SetUnitCategory("Length");
  f1x->SetDefaultUnit("mm");
  f1x->AvailableForStates(G4State_PreInit,G4State_Idle);


  f2x = new G4UIcmdWithADoubleAndUnit("/muondetector/setDet2thick",this);
  f2x->SetGuidance("Set the thickness of muondetector");
  f2x->SetParameterName("x",false);
  f2x->SetRange("x>0.");
  f2x->SetUnitCategory("Length");
  f2x->SetDefaultUnit("mm");
  f2x->AvailableForStates(G4State_PreInit,G4State_Idle);

  SDflag = new G4UIcmdWithABool("/muondetector/SD",this);
  SDflag->AvailableForStates(G4State_PreInit,G4State_Idle);
}

muonDetectorMessenger::~muonDetectorMessenger()
{
  delete fDetDir;

  delete f1Position;
  delete f2Position;


  delete f2x;
  delete f1x;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void muonDetectorMessenger::SetNewValue(G4UIcommand* command,G4String val)
{
  if( command == f1Position ) {
    fDetector->SetDetector1Position(G4UIcmdWith3VectorAndUnit::GetNew3VectorValue(val));
  }
  else if( command == f2Position ) {
    fDetector->SetDetector2Position(G4UIcmdWith3VectorAndUnit::GetNew3VectorValue(val));    
  }
  else if( command == f1x ) {
    fDetector->SetDetector1Thick(G4UIcmdWithADoubleAndUnit::GetNewDoubleValue( val ) );
  }
  else if( command == f2x ) {
    fDetector->SetDetector2Thick(G4UIcmdWithADoubleAndUnit::GetNewDoubleValue( val ) );    
  }
  else if(command == SDflag){
    fDetector->SetSD(G4UIcmdWithABool::GetNewBoolValue(val));
  }
}
