// 作用：建造 muonDetector

#ifndef MUONDETECTOR_CONSTRUCTION_HH
#define MUONDETECTOR_CONSTRUCTION_HH

#include <G4VUserDetectorConstruction.hh>
#include <G4SystemOfUnits.hh>
#include <G4ThreeVector.hh>
#include <G4RotationMatrix.hh>

#include "muonMaterial.hh"
class G4LogicalVolume;
class G4Trd;
/// Detector construction class to define materials and geometry.

class muonDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    muonDetectorConstruction();
    virtual ~muonDetectorConstruction();

    virtual G4VPhysicalVolume* Construct() override;

    void Constructmuondetector(G4LogicalVolume* );
    void ConstructPMT(G4LogicalVolume*);
    void ConstructReflection(G4LogicalVolume*, G4Trd*);

    // if Register some of the detector's volumes as "sensitive"
    void ConstructSDandField() override;
    
  private:
    G4double c_light   = 2.99792458e+8 * m/s;
    G4double h_Planck      = 6.62606896e-34 * joule*s;

    G4int   lambda_min = 200*nm ; 
    G4int lambda_max = 700*nm ;  

    
    //world 参数
    G4double world_sizeXY = 1*m, world_sizeZ  = 0.2*m;

    //detector 参数
    // 为了正面对着 gun
    //rotation y axies 90 deg
    // G4RotationMatrix* rotm  = 0;
    G4double phi=90.*deg;
    G4RotationMatrix* rotm = 
    new G4RotationMatrix(G4ThreeVector(std::cos(phi),0., -std::sin(phi)), 
    G4ThreeVector(0.,1., 0.), G4ThreeVector( std::sin(phi),0., std::cos(phi)));
    G4double shape_x1 =  20./2.*mm, 
    shape_x2 = 20./2.*mm, 
    shape_y1=84./2.*mm, 
    shape_y2=143.5/2.*mm, 
    shape_z=338.5/2.0*mm;

    G4ThreeVector pos1 = G4ThreeVector(0, 0, -15.*mm),
    pos2 = G4ThreeVector(0., 0., 15.*mm);

    // pmt 参数
    G4double PMT_thick   =   1.0*mm; // Thickness of PMT window
    G4double PMT_x    =  20./2.*mm, PMT_y=84./2.*mm; // Radius of curvature of PMT window
    G4ThreeVector PMTpos1 = G4ThreeVector(340.5/2.0*mm,0.0*cm,15 *mm);
    G4ThreeVector PMTpos2 = G4ThreeVector(340.5/2.0*mm,0.0*cm,-15 *mm);

    // reflection 参数
    G4double rshape_x1 =  22./2.*mm, 
    rshape_x2 = 22./2.*mm, 
    rshape_y1=86./2.*mm, 
    rshape_y2=145.5/2.*mm, 
    rshape_z=340.5/2.0*mm;
    G4ThreeVector rpos1 = G4ThreeVector(-1.*mm, 0, -15.*mm),
    rpos2 = G4ThreeVector(-1.*mm, 0., 15.*mm);

    G4bool checkOverlaps = true;
    muonMaterial* fMaterial;
};

#endif
