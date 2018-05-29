#include "muonDetectorConstruction.hh"
#include "G4tgbVolumeMgr.hh"
#include "G4tgrMessenger.hh"

muonDetectorConstruction::muonDetectorConstruction()
: G4VUserDetectorConstruction()
{ 
  fMessenger = new G4tgrMessenger;
}


muonDetectorConstruction::~muonDetectorConstruction()
{ 
  delete fMessenger;
}

#include "TextDetectorBuilder.hh"
// Construct physics World; 
G4VPhysicalVolume* muonDetectorConstruction::Construct()
{

  G4String filename = "muon.tg";
  G4tgbVolumeMgr* volmgr = G4tgbVolumeMgr::GetInstance();
  volmgr->AddTextFile(filename);
  TextDetectorBuilder * gtb = new TextDetectorBuilder();
  volmgr->SetDetectorBuilder(gtb); 
  G4VPhysicalVolume* physWorld = volmgr->ReadAndConstructDetector();
  return physWorld;
}

#include "EnergyTimeSD.hh"
#include "PMTSD.hh"
// 设置敏感探测器 记录 能量沉积 位置
#include <G4SDManager.hh>
#include <G4MultiFunctionalDetector.hh>
#include <G4PSEnergyDeposit.hh>
#include <G4VPrimitiveScorer.hh>
#include <G4LogicalVolume.hh>


void muonDetectorConstruction::ConstructSDandField()
{
  G4SDManager* sdManager = G4SDManager::GetSDMpointer();
  sdManager->SetVerboseLevel(2);

  EnergyTimeSD* muondectorEn = new EnergyTimeSD("muondectorEn");
  SetSensitiveDetector("muondector",muondectorEn);
  sdManager->AddNewDetector(muondectorEn);


  PMTSD*  PMT_ET = new PMTSD("PMT_ET");
  SetSensitiveDetector("PMT",PMT_ET);
  sdManager->AddNewDetector(PMT_ET);
}
