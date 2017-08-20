// 作用：建造 muonDetector

#ifndef MUONDETECTOR_CONSTRUCTION_HH
#define MUONDETECTOR_CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class muonDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    // 调用 Construct() 函数建造 detector
    muonDetectorConstruction();
    virtual ~muonDetectorConstruction();

    virtual G4VPhysicalVolume* Construct() override;

    // if Register some of the detector's volumes as "sensitive"
    // void ConstructSDandField() override;
};

#endif
