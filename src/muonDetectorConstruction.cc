
#include "muonDetectorConstruction.hh"
#include "muonDetectorMessenger.hh"

muonDetectorConstruction::muonDetectorConstruction()
: G4VUserDetectorConstruction()
{ 
  fMaterial = new muonMaterial();
  fMessenger = new muonDetectorMessenger(this);
}

#include "EnergyTimeSD.hh"
#include "PMTSD.hh"
// 设置敏感探测器 记录 能量沉积 位置
#include <G4SDManager.hh>
#include <G4MultiFunctionalDetector.hh>
#include <G4PSEnergyDeposit.hh>
#include <G4VPrimitiveScorer.hh>

muonDetectorConstruction::~muonDetectorConstruction()
{ 
  delete fMaterial;
  delete fMessenger;
}


#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4OpticalSurface.hh>
#include <G4MaterialPropertiesTable.hh>
#include <G4LogicalBorderSurface.hh>
#include <G4LogicalSkinSurface.hh>

// Construct physics World; 
G4VPhysicalVolume* muonDetectorConstruction::Construct()
{

  // world size 1 m x 1 m x 2 m box material air
  // name "world" point solidWorld logicalWorld physWorld
  G4Material* world_mat = fMaterial->GetfAir();

  G4Box* solidWorld = new G4Box("World",0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);
  G4LogicalVolume* logicalWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicalWorld, "World", NULL, false, 0, checkOverlaps);
  
  Constructmuondetector(logicalWorld,physWorld);
  ConstructPMT(logicalWorld);

    
  return physWorld;
}


#include <G4Trd.hh>
#include <G4RotationMatrix.hh>


#include <G4SubtractionSolid.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>
#include "G4NistManager.hh"
#include "G4Tubs.hh"


void muonDetectorConstruction::Constructmuondetector(G4LogicalVolume* logicalWorld, G4VPhysicalVolume* physWorld )
{

  //shape material
  G4Material* shape_mat = fMaterial->Getfdetector();

  // point solidDector logicShape no physical point
  G4Trd* solidDetector1 = 
  new G4Trd("muondector1", shape_x1, shape_x1,shape_y1,shape_y2, shape_z);
  G4LogicalVolume* logicShape1 = 
  new G4LogicalVolume(solidDetector1, shape_mat, "muondector1");
  new G4PVPlacement(rotm, pos1, logicShape1, "muondector1", 
  logicalWorld, false, 1, checkOverlaps);


  G4Trd* solidDetector2 = 
  new G4Trd("muondector2", shape_x2, shape_x2,shape_y1,shape_y2, shape_z);
  G4LogicalVolume* logicShape2 = 
  new G4LogicalVolume(solidDetector2, shape_mat, "muondector2");
  new G4PVPlacement(rotm, pos2, logicShape2, "muondector2", 
  logicalWorld, false, 2, checkOverlaps);


  G4Colour red (1.0, 0.0, 0.0) ; // red
  G4VisAttributes* ShapeVisAtt= new G4VisAttributes(red);
  logicShape1->SetVisAttributes(ShapeVisAtt);
  logicShape2->SetVisAttributes(ShapeVisAtt);

  G4SDManager* sdManager = G4SDManager::GetSDMpointer();
  sdManager->SetVerboseLevel(2);

  EnergyTimeSD* muondectorEn = new EnergyTimeSD("muondectorEn");
  logicShape1->SetSensitiveDetector(muondectorEn);
  logicShape2->SetSensitiveDetector(muondectorEn);
  sdManager->AddNewDetector(muondectorEn);
  
  ConstructReflection(logicalWorld,solidDetector1,solidDetector2,physWorld);
}
#include <G4LogicalBorderSurface.hh>
#include <G4LogicalSkinSurface.hh>
void muonDetectorConstruction::ConstructReflection(G4LogicalVolume* logicalWorld, G4Trd* solidDetector1,G4Trd* solidDetector2,G4VPhysicalVolume* physWorld )
{
  // Al2O3
  G4Material* Al2O3 = fMaterial->Getfreflect();

  G4Trd* solid1 = new G4Trd("Al2O3", rshape_x1, rshape_x1,rshape_y1,rshape_y2, rshape_z);
  G4SubtractionSolid* Al2O3solid1 = new G4SubtractionSolid("Trd-Trd",solid1,solidDetector1,0,G4ThreeVector(-0.0*mm,-0.*mm,-1.*mm) );
  G4LogicalVolume* logic1Al2O3 = new G4LogicalVolume(Al2O3solid1, Al2O3, "Al2O31");
  G4PVPlacement* physi1 =  new G4PVPlacement(rotm, rpos1, logic1Al2O3, "Al2O31", logicalWorld, false, 0, checkOverlaps);
  
  G4Trd* solid2 = new G4Trd("Al2O3", rshape_x2, rshape_x2,rshape_y1,rshape_y2, rshape_z);
  G4SubtractionSolid* Al2O3solid2 = new G4SubtractionSolid("Trd-Trd",solid2,solidDetector2,0,G4ThreeVector(-0.0*mm,-0.*mm,-1.*mm) );
  G4LogicalVolume* logic2Al2O3 = new G4LogicalVolume(Al2O3solid2, Al2O3, "Al2O32");
  G4PVPlacement* physi2 = new G4PVPlacement(rotm, rpos2, logic2Al2O3, "Al2O32", logicalWorld, false, 1, checkOverlaps);
  
  //设置光学性质

  G4OpticalSurface* Al2O3Surface = new G4OpticalSurface("PhotonDetSurface",glisur,ground,dielectric_metal);

  new G4LogicalSkinSurface("Al2O3Surface",logic1Al2O3,Al2O3Surface);
  new G4LogicalSkinSurface("Al2O3Surface",logic2Al2O3,Al2O3Surface);
  // new G4LogicalBorderSurface("Al2O3Surface",physWorld,physi1,Al2O3Surface);
  // new G4LogicalBorderSurface("Al2O3Surface",physWorld,physi2,Al2O3Surface);
}

void muonDetectorConstruction::ConstructPMT(G4LogicalVolume* logicalWorld)
{

  G4Material* Quartz = fMaterial->GetfPMT();

  G4Box* solidPMT1 = new G4Box("PMT_solid",PMT_x1,PMT_y,PMT_thick);
  G4LogicalVolume* logicalPMT1 = new G4LogicalVolume(solidPMT1,Quartz,"PMT_log1",0,0,0);
  
  G4Box* solidPMT2 = new G4Box("PMT_solid",PMT_x2,PMT_y,PMT_thick);
  G4LogicalVolume* logicalPMT2 = new G4LogicalVolume(solidPMT2,Quartz,"PMT_log2",0,0,0);
  
  G4Colour green (0.0, 1.0, 0.0) ; // green
  G4VisAttributes* PMTVisAtt= new G4VisAttributes(green);
  logicalPMT1->SetVisAttributes(PMTVisAtt);
  logicalPMT2->SetVisAttributes(PMTVisAtt);

  new G4PVPlacement(rotm,PMTpos1,logicalPMT1,"PMT1",logicalWorld,false,0,checkOverlaps);
  new G4PVPlacement(rotm,PMTpos2,logicalPMT2,"PMT2",logicalWorld,false,1,checkOverlaps);
  
  
  G4Material* windows_mat = fMaterial->GetfPMMA();
  
  G4Trd* solidwindows1 = new G4Trd("windows1", windows_x1, windows_x1, windows_y1, windows_y2, windows_z); 
  G4Trd* solidwindows2 = new G4Trd("windows2", windows_x2, windows_x2, windows_y1, windows_y2, windows_z); 
       
  // Set two logical volume;
  G4LogicalVolume* logicwin1 = new G4LogicalVolume(solidwindows1, windows_mat, "Windows1");
  G4LogicalVolume* logicwin2 = new G4LogicalVolume(solidwindows2, windows_mat, "Windows1");
  logicwin1->SetVisAttributes(PMTVisAtt);
  logicwin2->SetVisAttributes(PMTVisAtt);

  new G4PVPlacement(rotm, pos_win1, logicwin1, "Windows1", logicalWorld, false, 0,  checkOverlaps);
  new G4PVPlacement(rotm, pos_win2, logicwin2, "Windows2", logicalWorld, false, 1,  checkOverlaps); 
  
  // Al2O3
  G4Material* Al2O3 = fMaterial->Getfreflect();

  G4Trd* solid1 = new G4Trd("Al2O3", wshape_x1, wshape_x1,wshape_y1,wshape_y2, wshape_z);
  G4SubtractionSolid* Al2O3solid1 = new G4SubtractionSolid("Trd-Trd",solid1,solidwindows1,0,G4ThreeVector(-0.0*mm,-0.*mm,0.*mm) );
  G4LogicalVolume* logic1Al2O3 = new G4LogicalVolume(Al2O3solid1, Al2O3, "Al2O31");
  new G4PVPlacement(rotm, wpos1, logic1Al2O3, "Al2O31", logicalWorld, false, 2, checkOverlaps);
  
  G4Trd* solid2 = new G4Trd("Al2O3", wshape_x2, wshape_x2,wshape_y1,wshape_y2, wshape_z);
  G4SubtractionSolid* Al2O3solid2 = new G4SubtractionSolid("Trd-Trd",solid2,solidwindows2,0,G4ThreeVector(-0.0*mm,-0.*mm,0.*mm) );
  G4LogicalVolume* logic2Al2O3 = new G4LogicalVolume(Al2O3solid2, Al2O3, "Al2O32");
  new G4PVPlacement(rotm, wpos2, logic2Al2O3, "Al2O32", logicalWorld, false, 3, checkOverlaps);
  

  //设置光学性质

  G4OpticalSurface* Al2O3Surface = new G4OpticalSurface("PhotonDetSurface",glisur,ground,dielectric_metal);

  new G4LogicalSkinSurface("Al2O3Surface",logic1Al2O3,Al2O3Surface);
  new G4LogicalSkinSurface("Al2O3Surface",logic2Al2O3,Al2O3Surface);

  G4SDManager* sdManager = G4SDManager::GetSDMpointer();
  sdManager->SetVerboseLevel(2);

  PMTSD*  PMT_ET = new PMTSD("PMT_ET");
  logicalPMT1->SetSensitiveDetector(PMT_ET);
  logicalPMT2->SetSensitiveDetector(PMT_ET);
  sdManager->AddNewDetector(PMT_ET);

  //设置光学性质

  G4double fReflectivity = 0.;
  
  G4OpticalSurface* Surface = new G4OpticalSurface("PhotonDetSurface",glisur,ground,dielectric_metal);
  
  G4MaterialPropertiesTable* SurfaceProperty = new G4MaterialPropertiesTable();
  
  G4double p_mppc[] = {1.70*eV, 3.47*eV};
  const G4int nbins = sizeof(p_mppc)/sizeof(G4double);
  G4double refl_mppc[] = {fReflectivity,fReflectivity};
  assert(sizeof(refl_mppc) == sizeof(p_mppc));
  G4double effi_mppc[] = {1, 1};
  assert(sizeof(effi_mppc) == sizeof(p_mppc));
  
  SurfaceProperty->AddProperty("REFLECTIVITY",p_mppc,refl_mppc,nbins);
  SurfaceProperty->AddProperty("EFFICIENCY",p_mppc,effi_mppc,nbins);
  
  Surface->SetMaterialPropertiesTable(SurfaceProperty);
  
  new G4LogicalSkinSurface("PMTSurface",logicalPMT1,Surface);
  new G4LogicalSkinSurface("PMTSurface",logicalPMT2,Surface);

}


void muonDetectorConstruction::ConstructSDandField()
{

}
