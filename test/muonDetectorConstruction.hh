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
#include <G4ThreeVector.hh>
#include <G4RotationMatrix.hh>

#include "muonMaterial.hh"
#include "muonDetectorMessenger.hh"

#include "G4RunManager.hh"

class G4LogicalVolume;
class G4Trd;
class muonDetectorMessenger;
/**
 * @brief Detector Construction
 */
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
    /**
     * @brief Construct muondetector
     * @param world parent volume 为 world logical volume, 构建探测器 tree
     */
    void Constructmuondetector(G4LogicalVolume* world,G4VPhysicalVolume* physWorld);
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
    void ConstructReflection(G4LogicalVolume* world , G4Trd* detector,G4Trd* detect,G4VPhysicalVolume* physWorlds);

    /**
     * @brief 注册敏感探测器
     * @details 注册 pmt(PMTSD) muon detector(EnergyTimeSD) 敏感探测器
     */
    void ConstructSDandField() override;
    
    G4double GetDetector1Thick(){return shape_x1;}
    void SetDetector1Thick(G4double x){
        shape_x1 = x/2.0;
        windows_x1 = shape_x1;
        rshape_x1 =  shape_x1 + 1.*mm;
        PMT_x1 = shape_x1;
        pos1 = G4ThreeVector(0, 0, -shape_x1-5.*mm);
        rpos1 = G4ThreeVector(pos1.getX()-1.*mm, pos1.getY(), pos1.getZ());
        PMTpos1 = G4ThreeVector(pos1.getX()+shape_z+PMT_thick,pos1.getY(),pos1.getZ());
        G4RunManager::GetRunManager()->ReinitializeGeometry();
    }

    G4double GetDetector2Thick(){return shape_x1;}
    void SetDetector2Thick(G4double x){
        shape_x2 = x/2.0;
        windows_x2 = shape_x2;
        rshape_x2 = shape_x2 +1.*mm;
        PMT_x2 = shape_x2;
        pos2 = G4ThreeVector(0., 0., shape_x2+5.*mm);
        rpos2 = G4ThreeVector(pos2.getX()-1.*mm, pos2.getY(), pos2.getZ());
        PMTpos2 = G4ThreeVector(pos2.getX()+shape_z+PMT_thick,pos2.getY(),pos2.getZ());
        G4RunManager::GetRunManager()->ReinitializeGeometry();
    }


    G4double GetDetectorPhi(){return phi;}
    void SetDetectorPhi(G4double p){
        phi = p;
        G4RunManager::GetRunManager()->ReinitializeGeometry();
    }

    G4ThreeVector GetDetector1Position(){return pos1;}
    void SetDetector1Position(G4ThreeVector vector){
        pos1 = vector;
        rpos1 = G4ThreeVector(pos1.getX()-1.*mm, pos1.getY(), pos1.getZ());
        PMTpos1 = G4ThreeVector(pos1.getX()+shape_z+PMT_thick,pos1.getY(),pos1.getZ());
        pos_win1 = G4ThreeVector((pos1.getX() + shape_z + windows_z), pos1.getY(), pos1.getZ());
        G4RunManager::GetRunManager()->ReinitializeGeometry();
    }

    G4ThreeVector GetDetector2Position(){return pos2;}
    void SetDetector2Position(G4ThreeVector vector){
        pos2 = vector;
        rpos2 = G4ThreeVector(pos2.getX()-1.*mm, pos2.getY(), pos2.getZ());
        PMTpos2 = G4ThreeVector(pos2.getX()+shape_z+PMT_thick,pos2.getY(),pos2.getZ());
        pos_win2 = G4ThreeVector((pos2.getX() + shape_z + windows_z), pos2.getY(), pos2.getZ());
        G4RunManager::GetRunManager()->ReinitializeGeometry();
    }

  private:

    //一些物理常数
    G4double c_light   = 2.99792458e+8 * m/s;
    G4double h_Planck      = 6.62606896e-34 * joule*s;

    
    //world 形状参数 
    G4double world_sizeXY = 1*m, world_sizeZ  = 0.2*m;

    // detector 形状参数
    // 为了正面对着 gun rotation y axies 90 deg
    G4double shape_x1 =  20./2.*mm,  
    shape_y1=84./2.*mm, 
    shape_y2=143.5/2.*mm, 
    shape_z=338.5/2.0*mm;

    G4double phi=90.*deg;
    G4RotationMatrix* rotm = 
    new G4RotationMatrix(G4ThreeVector(std::cos(phi),0., -std::sin(phi)), 
    G4ThreeVector(0.,1., 0.), G4ThreeVector( std::sin(phi),0., std::cos(phi)));
    // detector 2 thickness
    G4double shape_x2 = 20./2.*mm;

    // detector 位置参数
    G4ThreeVector pos1 = G4ThreeVector(0, 0, -shape_x1-5.*mm),
    pos2 = G4ThreeVector(0., 0., shape_x2+5.*mm);

    // Trapezoid shape       
    G4double windows_x1 = shape_x1,windows_x2= shape_x2;
    G4double windows_y1 = shape_x1, windows_y2 = shape_y1;
    G4double windows_z  = shape_y1;      

    // reflection 参数
    // 厚度 1 mm 
    G4double rshape_x1 =  shape_x1 + 1.*mm, 
    rshape_x2 = shape_x2 +1.*mm, 
    rshape_y1=shape_y1+1.*mm, 
    rshape_y2=shape_y2+1.*mm, 
    rshape_z=shape_z+1.*mm;

    G4double wshape_x1 = windows_x1 + 1.*mm, 
    wshape_x2 = windows_x2 +1.*mm, 
    wshape_y1=windows_y1+1.*mm, 
    wshape_y2=windows_y2+1.*mm, 
    wshape_z=windows_z;

    G4ThreeVector rpos1 = G4ThreeVector(pos1.getX()-1.*mm, pos1.getY(), pos1.getZ()),
    rpos2 = G4ThreeVector(pos2.getX()-1.*mm, pos2.getY(), pos2.getZ()),
    wpos2 = G4ThreeVector((pos1.getX() + shape_z + windows_z), pos1.getY(), pos1.getZ()),
    wpos1 = G4ThreeVector((pos2.getX() + shape_z + windows_z), pos2.getY(), pos2.getZ());


    // Set Position for windows;
    G4ThreeVector pos_win1 = G4ThreeVector((pos1.getX() + shape_z + windows_z), pos1.getY(), pos1.getZ());
    G4ThreeVector pos_win2 = G4ThreeVector((pos2.getX() + shape_z + windows_z), pos2.getY(), pos2.getZ());

    // pmt 参数
    G4double PMT_thick   =   1.0*mm; // Thickness of PMT window
    G4double PMT_x2    =  shape_x2, PMT_x1 = shape_x1, PMT_y=shape_x1; // Radius of curvature of PMT window
    G4ThreeVector PMTpos1 = G4ThreeVector(pos1.getX()+shape_z+2*windows_z+PMT_thick,pos1.getY(),pos1.getZ());
    G4ThreeVector PMTpos2 = G4ThreeVector(pos2.getX()+shape_z+2*windows_z+PMT_thick,pos2.getY(),pos2.getZ());
    G4bool checkOverlaps = true;
    // 材料信息存在 fMaterial
    muonMaterial* fMaterial;
    // 新建宏命令，设置探测器的结构
    muonDetectorMessenger* fMessenger;

};

#endif
