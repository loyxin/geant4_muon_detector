
#include "muonDetectorConstruction.hh"


#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
// #include "G4Cons.hh"
// #include "G4Orb.hh"
// #include "G4Tubs.hh"
// #include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4RotationMatrix.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4SDManager.hh"
//#include "G4UnitDefinition.hh"


muonDetectorConstruction::muonDetectorConstruction()
: G4VUserDetectorConstruction()
{ Construct();}


muonDetectorConstruction::~muonDetectorConstruction()
{ }


G4VPhysicalVolume* muonDetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  //define material
  G4String name,symbol;
  G4double a,z,density;
  G4int ncomponents,natoms;

  //G4UnitDefinition::BuildUnitsTable();
  //define material we use
  // C_10 H_14
  a=1.01*g/mole;
  G4Element* elH=new G4Element(name="Hydrogen",symbol="H",z=1.,a);

  a=12.01*g/mole;
  G4Element* elC=new G4Element(name="Carbon",symbol="C",z=6.,a);

  density=1.25*g/cm3;
  G4Material* anth=new G4Material(name="anthracene",density,ncomponents=2);
  anth->AddElement(elH,natoms=10);
  anth->AddElement(elC,natoms=14);
  //shape material
  G4Material* shape_mat = anth;

  G4bool checkOverlaps = true;

  // world size 1 m x 1 m x 2 m box material air
  // name "world" point solidWorld logicWorld physWorld
  G4double world_sizeXY = 1*m;
  G4double world_sizeZ  = 2*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld = new G4Box("World",0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");

  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", NULL, false, 0, checkOverlaps);

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

  // point solidShape logicShape no physical point
  G4Trd* solidShape = new G4Trd("muondector", shape_x1, shape_x2,shape_y1,shape_y2, shape_z);
  G4LogicalVolume* logicShape = new G4LogicalVolume(solidShape, shape_mat, "muondector");

  G4ThreeVector pos1 = G4ThreeVector(0, 0, -15.*mm);

  new G4PVPlacement(rotm, pos1, logicShape, "muondector1", logicWorld, false, 0, checkOverlaps);

  G4ThreeVector pos2 = G4ThreeVector(0., 0., 15.*mm);

  new G4PVPlacement(rotm, pos2, logicShape, "muondector2", logicWorld, false, 1, checkOverlaps);

  return physWorld;
}
