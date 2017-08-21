// 作用：建造 muonDetector

#ifndef MUONDETECTOR_CONSTRUCTION_HH
#define MUONDETECTOR_CONSTRUCTION_HH

#include <G4VUserDetectorConstruction.hh>
#include <G4SystemOfUnits.hh>
class G4LogicalVolume;
/// Detector construction class to define materials and geometry.

class muonDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    muonDetectorConstruction();
    virtual ~muonDetectorConstruction();

    virtual G4VPhysicalVolume* Construct() override;
    void Constructmuondetector(G4LogicalVolume*, G4VPhysicalVolume* );
    void ConstructPMT(G4LogicalVolume*);
    // if Register some of the detector's volumes as "sensitive"
    void ConstructSDandField() override;
    G4double c_light   = 2.99792458e+8 * m/s;
    G4int   lambda_min = 200*nm ; 
    G4int lambda_max = 700*nm ;  
    G4double h_Planck      = 6.62606896e-34 * joule*s;
};

#endif
