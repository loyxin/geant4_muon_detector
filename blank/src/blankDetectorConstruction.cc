

#include "blankDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"



blankDetectorConstruction::blankDetectorConstruction()
: G4VUserDetectorConstruction()
{ }



blankDetectorConstruction::~blankDetectorConstruction()
{ }


G4VPhysicalVolume* blankDetectorConstruction::Construct()
{
  G4bool checkOverlaps = true;

  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  G4double world_sizeXY = 1.*m, world_sizeZ = 3.*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4double Zn_sizeXY = 0.8*m, Zn_sizeZ = 3.*cm;
  G4Material* Zn_mat = nist->FindOrBuildMaterial("G4_Zn");


  G4Box* solidWorld =
          new G4Box("World",                       //its name
                    0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
          new G4LogicalVolume(solidWorld,          //its solid
                              world_mat,           //its material
                              "World");            //its name

  G4VPhysicalVolume* physWorld =
          new G4PVPlacement(0,                     //no rotation
                            G4ThreeVector(),       //at (0,0,0)
                            logicWorld,            //its logical volume
                            "World",               //its name
                            0,                     //its mother  volume
                            false,                 //no boolean operation
                            0,                     //copy number
                            checkOverlaps);        //overlaps checking

  G4Box* solidZn = new G4Box("Zincsolid", 0.5*Zn_sizeXY, 0.5*Zn_sizeXY, 0.5*Zn_sizeZ);
  G4LogicalVolume* logicalZn = new G4LogicalVolume(solidZn,Zn_mat,"zinc");
  new G4PVPlacement(0,G4ThreeVector(),logicalZn,"zinc",logicWorld, false,0,checkOverlaps);
  return physWorld;
}


