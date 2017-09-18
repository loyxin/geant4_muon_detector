/**
 * @file muonDetectorConstruction.hh
 * @brief Detector Construction
 * @author loyxin
 * @version 1.0
 * @date 2017-09-10
 */
#ifndef MUONDETECTOR_CONSTRUCTION_HH
#define MUONDETECTOR_CONSTRUCTION_HH

#include <G4VUserDetectorConstruction.hh>
#include <G4SystemOfUnits.hh>
#include "muonMaterial.hh"
class G4LogicalVolume;
<<<<<<< HEAD
class G4Trd;
/**
 * @brief Detector Construction
 */
=======
/// Detector construction class to define materials and geometry.

>>>>>>> parent of 1c568a5... add doxygen
class muonDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    /**
     * @brief constructor
     * @details 初始化材料对象
     */
    muonDetectorConstruction();
    virtual ~muonDetectorConstruction();
    /**
     * @brief Detector construction
     * @details define  geometry
     * @return world physical volume
     */
    virtual G4VPhysicalVolume* Construct() override;
<<<<<<< HEAD
    /**
     * @brief Construct muondetector
     * @param world parent volume 为 world logical volume, 构建探测器 tree
     */
    void Constructmuondetector(G4LogicalVolume* world);
    /**
     * @brief Construct PMT
     * @param world parent volume 为 world logical volume, 构建探测器 tree
     */
    void ConstructPMT(G4LogicalVolume* world);
    /**
     * @brief [brief description]
     * @details [long description]
     * 
     * @param world parent volume 为 world logical volume, 构建探测器 tree
     * @param detector muon detector 形状，用于构建发射层的形状
     */
    void ConstructReflection(G4LogicalVolume* world , G4Trd* detector);

    /**
     * @brief 注册敏感探测器
     * @details 注册 pmt(PMTSD) muon detector(EnergyTimeSD) 敏感探测器
     */
=======
    void Constructmuondetector(G4LogicalVolume*, G4VPhysicalVolume* );
    void ConstructPMT(G4LogicalVolume*);
    // if Register some of the detector's volumes as "sensitive"
>>>>>>> parent of 1c568a5... add doxygen
    void ConstructSDandField() override;

  private:
    //一些物理常数
    G4double c_light   = 2.99792458e+8 * m/s;
<<<<<<< HEAD
    G4double h_Planck      = 6.62606896e-34 * joule*s;

    
    //world 形状参数 
    G4double world_sizeXY = 1*m, world_sizeZ  = 0.2*m;

    // detector 形状参数
    // 为了正面对着 gun rotation y axies 90 deg
    G4double shape_x1 =  20./2.*mm, 
    shape_x2 = 20./2.*mm, 
    shape_y1=84./2.*mm, 
    shape_y2=143.5/2.*mm, 
    shape_z=338.5/2.0*mm;

    G4double phi=90.*deg;
    G4RotationMatrix* rotm = 
    new G4RotationMatrix(G4ThreeVector(std::cos(phi),0., -std::sin(phi)), 
    G4ThreeVector(0.,1., 0.), G4ThreeVector( std::sin(phi),0., std::cos(phi)));

    // detector 位置参数
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

=======
    G4int   lambda_min = 200*nm ; 
    G4int lambda_max = 700*nm ;  
    G4double h_Planck      = 6.62606896e-34 * joule*s;
>>>>>>> parent of 1c568a5... add doxygen
    G4bool checkOverlaps = true;
    // 材料信息存在 fMaterial
    muonMaterial* fMaterial;
};

#endif
