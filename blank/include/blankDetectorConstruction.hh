
#ifndef blankDetectorConstruction_h
#define blankDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class blankDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    blankDetectorConstruction();
    virtual ~blankDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    


};



#endif

