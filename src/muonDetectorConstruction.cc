
#include "muonDetectorConstruction.hh"

muonDetectorConstruction::muonDetectorConstruction()
: G4VUserDetectorConstruction()
{ }


muonDetectorConstruction::~muonDetectorConstruction()
{ }

#include <G4NistManager.hh>


#include <G4Box.hh>
#include <G4Material.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>


G4VPhysicalVolume* muonDetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  G4bool checkOverlaps = true;

  // world size 1 m x 1 m x 2 m box material air
  // name "world" point solidWorld logicalWorld physWorld
  G4double world_sizeXY = 1*m;
  G4double world_sizeZ  = 2*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld = new G4Box("World",0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);
  G4LogicalVolume* logicalWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicalWorld, "World", NULL, false, 0, checkOverlaps);
  
  Constructmuondetector(logicalWorld,physWorld);
  ConstructPMT(logicalWorld);

  return physWorld;
}


#include <G4Trd.hh>
#include <G4RotationMatrix.hh>
#include <G4Isotope.hh>
#include <G4Element.hh>
#include <G4SubtractionSolid.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>
#include <G4OpticalSurface.hh>
#include <G4LogicalBorderSurface.hh>
void muonDetectorConstruction::Constructmuondetector(G4LogicalVolume* logicalWorld, G4VPhysicalVolume* physWorld )
{
  G4bool checkOverlaps = true;
  
  //define material
  G4String name,symbol;
  G4double a,z,density;
  G4int ncomponents,natoms;

  //G4UnitDefinition::BuildUnitsTable();
  //define material we use
  // C_10 H_14
  G4Element* elH=new G4Element(name="Hydrogen",symbol="H",z=1.,a=1.01*g/mole);
  G4Element* elC=new G4Element(name="Carbon",symbol="C",z=6.,a=12.01*g/mole);
  G4Material* anth=new G4Material(name="anthracene",density=1.25*g/cm3,ncomponents=2);

  anth->AddElement(elH,natoms=10);
  anth->AddElement(elC,natoms=14);
  //shape material
  G4Material* shape_mat = anth;

  // 为了正面对着 gun
  //rotation y axies 90 deg
  // G4RotationMatrix* rotm  = 0;
  G4double phi=90.*deg;
  G4ThreeVector u = G4ThreeVector(std::cos(phi),0., -std::sin(phi));
  G4ThreeVector v = G4ThreeVector(0.,1., 0.);
  G4ThreeVector w = G4ThreeVector( std::sin(phi),0., std::cos(phi));
  G4RotationMatrix* rotm = new G4RotationMatrix(u, v, w);


  // 物体参数
  G4double shape_x1 =  20./2.*mm, shape_x2 = 20./2.*mm, shape_y1=84./2.*mm, shape_y2=143.5/2.*mm, shape_z=338.5/2.0*mm;

  // point solidDector logicShape no physical point
  G4Trd* solidDector = new G4Trd("muondector", shape_x1, shape_x2,shape_y1,shape_y2, shape_z);
  G4LogicalVolume* logicShape = new G4LogicalVolume(solidDector, shape_mat, "muondector");

  G4Colour red (1.0, 0.0, 0.0) ; // red
  G4VisAttributes* ShapeVisAtt= new G4VisAttributes(red);

  logicShape->SetVisAttributes(ShapeVisAtt);

  G4ThreeVector pos1 = G4ThreeVector(0, 0, -15.*mm);

  new G4PVPlacement(rotm, pos1, logicShape, "muondector1", logicalWorld, false, 0, checkOverlaps);

  G4ThreeVector pos2 = G4ThreeVector(0., 0., 15.*mm);

  new G4PVPlacement(rotm, pos2, logicShape, "muondector2", logicalWorld, false, 1, checkOverlaps);

  // Ag
  shape_x1 =  22./2.*mm, shape_x2 = 22./2.*mm, shape_y1=86./2.*mm, shape_y2=145.5/2.*mm, shape_z=338.5/2.0*mm;
  G4Trd* solid = new G4Trd("Ag", shape_x1, shape_x2,shape_y1,shape_y2, shape_z);

  G4SubtractionSolid* Agsolid = new G4SubtractionSolid("Trd-Trd",solid,solidDector);

  G4NistManager* nist = G4NistManager::Instance();
  G4Material* Ag = nist->FindOrBuildMaterial("G4_Al");
  G4LogicalVolume* logicAg = new G4LogicalVolume(Agsolid, Ag, "Ag");


  G4OpticalSurface *OpticalAirMirror = new G4OpticalSurface("AirMirrorSurface");
  OpticalAirMirror->SetModel(unified);
  OpticalAirMirror->SetType(dielectric_dielectric);
  OpticalAirMirror->SetFinish(polishedfrontpainted);

  const G4int NUM = 2;
  G4double XX[NUM] = {h_Planck*c_light/lambda_max, h_Planck*c_light/lambda_min} ; 
  G4double ICEREFLECTIVITY[NUM]      = { 0.99, 0.99 };

  G4MaterialPropertiesTable *AirMirrorMPT = new G4MaterialPropertiesTable();
  AirMirrorMPT->AddProperty("REFLECTIVITY", XX, ICEREFLECTIVITY,NUM);
  OpticalAirMirror->SetMaterialPropertiesTable(AirMirrorMPT);


  G4VPhysicalVolume* Ag1phy =  new G4PVPlacement(rotm, pos1, logicAg, "Ag1", logicalWorld, false, 0, checkOverlaps);

  G4VPhysicalVolume* Ag2phy = new G4PVPlacement(rotm, pos2, logicAg, "Ag2", logicalWorld, false, 1, checkOverlaps);
  
  new G4LogicalBorderSurface("Mirror Surface",physWorld,Ag1phy,OpticalAirMirror);
  new G4LogicalBorderSurface("Mirror Surface",physWorld,Ag2phy,OpticalAirMirror);
}

void muonDetectorConstruction::ConstructPMT(G4LogicalVolume* logicalWorld)
{
  G4bool checkOverlaps = true;
  
  G4String symbol,name;
  G4int nel;
  G4double z;
  G4double density = 2.64*g/cm3;  // crystalline quartz (c.f. PDG) 
  G4Material *Quartz = new G4Material(name="Quartz",density, nel=2);

  G4double a = 16.00*g/mole;
  G4Element* elO  = new G4Element(name="Oxygen",   symbol="O", z=8., a);
  a = 28.09*g/mole;
  G4Element* elSi = new G4Element(name="Silicon", symbol="Si", z=14., a);

  Quartz->AddElement(elSi, 1) ;
  Quartz->AddElement(elO , 2) ;

  const G4int N_RINDEX_QUARTZ = 2 ;
  G4double X_RINDEX_QUARTZ[N_RINDEX_QUARTZ] = {h_Planck*c_light/lambda_max, h_Planck*c_light/lambda_min} ; 
  G4double RINDEX_QUARTZ[N_RINDEX_QUARTZ] = {1.54, 1.54};

  G4MaterialPropertiesTable *MPT_PMT = new G4MaterialPropertiesTable();
  MPT_PMT->AddProperty("RINDEX", X_RINDEX_QUARTZ, RINDEX_QUARTZ, N_RINDEX_QUARTZ);

  Quartz->SetMaterialPropertiesTable(MPT_PMT);

  G4double PMT_thick   =   1.0*mm; // Thickness of PMT window
  G4double PMT_x    =  20./2.*mm, PMT_y=84./2.*mm; // Radius of curvature of PMT window

  G4Colour green (0.0, 1.0, 0.0) ; // green
  G4VisAttributes* PMTVisAtt= new G4VisAttributes(green);

  G4Box* solidPMT = new G4Box("PMT_solid",PMT_x,PMT_y,PMT_thick);
  G4LogicalVolume* logicalPMT = new G4LogicalVolume(solidPMT,Quartz,"PMT_log",0,0,0);
  logicalPMT->SetVisAttributes(PMTVisAtt);
  G4ThreeVector PMTpos1 = G4ThreeVector(342.0/2.0*mm,0.0*cm,15 *mm);
  G4ThreeVector PMTpos2 = G4ThreeVector(342.0/2.0*mm,0.0*cm,-15 *mm);

  G4double phi=90.*deg;
  G4ThreeVector u = G4ThreeVector(std::cos(phi),0., -std::sin(phi));
  G4ThreeVector v = G4ThreeVector(0.,1., 0.);
  G4ThreeVector w = G4ThreeVector( std::sin(phi),0., std::cos(phi));
  G4RotationMatrix* rotm = new G4RotationMatrix(u, v, w);
  
  new G4PVPlacement(rotm,PMTpos1,logicalPMT,"PMT1",logicalWorld,false,0,checkOverlaps);
  new G4PVPlacement(rotm,PMTpos2,logicalPMT,"PMT2",logicalWorld,false,1,checkOverlaps);

}

#include "EnergyTimeSD.hh"
// 设置敏感探测器 记录 能量沉积 位置
#include <G4SDManager.hh>
#include <G4MultiFunctionalDetector.hh>
#include <G4PSEnergyDeposit.hh>
#include <G4VPrimitiveScorer.hh>
void muonDetectorConstruction::ConstructSDandField()
{
  G4SDManager* sdManager = G4SDManager::GetSDMpointer();
  sdManager->SetVerboseLevel(2);

  G4MultiFunctionalDetector* muondectorEn = new G4MultiFunctionalDetector("muondectorEn");
  G4VPrimitiveScorer* primitive = new G4PSEnergyDeposit("enerygy");
  muondectorEn->RegisterPrimitive(primitive);
  SetSensitiveDetector("muondector",muondectorEn);
  sdManager->AddNewDetector(muondectorEn);

  EnergyTimeSD* PMT_ET = new EnergyTimeSD("PMT_ET");
  SetSensitiveDetector("PMT_log",PMT_ET);
  sdManager->AddNewDetector(PMT_ET);

}