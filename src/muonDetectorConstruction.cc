
#include "muonDetectorConstruction.hh"

muonDetectorConstruction::muonDetectorConstruction()
: G4VUserDetectorConstruction()
{ fMaterial = new muonMaterial();}


muonDetectorConstruction::~muonDetectorConstruction()
{ }


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
  G4double world_sizeXY = 1*m, world_sizeZ  = 0.2*m;
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

  // 为了正面对着 gun
  //rotation y axies 90 deg
  // G4RotationMatrix* rotm  = 0;
  G4double phi=90.*deg;
  G4RotationMatrix* rotm = 
  new G4RotationMatrix(G4ThreeVector(std::cos(phi),0., -std::sin(phi)), 
  G4ThreeVector(0.,1., 0.), G4ThreeVector( std::sin(phi),0., std::cos(phi)));


  // 物体参数
  G4double shape_z1 =  20./2.*mm, shape_z2 = 20./2.*mm, shape_y1=84./2.*mm, shape_y2=143.5/2.*mm, shape_x=338.5/2.0*mm;
  G4ThreeVector pos1 = G4ThreeVector(0, 0, -15.*mm),pos2 = G4ThreeVector(0., 0., 15.*mm);
 
  // point solidDector logicShape no physical point
  G4Trd* solidDector = 
  new G4Trd("muondector", shape_z1, shape_z2,shape_y1,shape_y2, shape_x);
  G4LogicalVolume* logicShape = 
  new G4LogicalVolume(solidDector, shape_mat, "muondector");

  G4Colour red (1.0, 0.0, 0.0) ; // red
  G4VisAttributes* ShapeVisAtt= new G4VisAttributes(red);
  logicShape->SetVisAttributes(ShapeVisAtt);

  new G4PVPlacement(rotm, pos1, logicShape, "muondector1", 
  logicalWorld, false, 0, checkOverlaps);
  new G4PVPlacement(rotm, pos2, logicShape, "muondector2", 
  logicalWorld, false, 1, checkOverlaps);
  
//  Set geometry for light guider;
  //
  // The Windows:  we will create 2 windows here, the same;
  //
  
  // Get nist material manager
  
  // Ready for PMMA;
  G4NistManager* nist = G4NistManager::Instance();
  
  // Prepare for PMMA;
  std::vector<G4int> natoms;
  std::vector<G4String> elements;
  
  elements.push_back("C");     natoms.push_back(5);
  elements.push_back("H");     natoms.push_back(8);
  elements.push_back("O");     natoms.push_back(2);
  
  G4Material* fPMMA = nist->ConstructNewMaterial("PMMA", elements, natoms, 1.190*g/cm3);

  // End of readying for PMMA;
  
  G4Material* windows_mat = fPMMA;

  // Trapezoid shape       
  G4double windows_dza = 20./2.*mm, windows_dzb = 20./2.*mm;
  G4double windows_dya = 20./2.*mm, windows_dyb = 84./2.*mm;
  G4double windows_dx  = 84./2.*mm;      
  
  // Set Position for windows;
  G4ThreeVector pos_win1 = G4ThreeVector((shape_x + windows_dx), 0, 15.*mm);
  G4ThreeVector pos_win2 = G4ThreeVector((shape_x + windows_dx), 0, -15.*mm);
  
  G4Trd* solidwindows =    
    new G4Trd("windows",                      //its name
              windows_dza, windows_dzb, 
              windows_dya, windows_dyb, windows_dx); //its size
                
  // Set two logical volume;
  G4LogicalVolume* logicwin =                         
    new G4LogicalVolume(solidwindows, windows_mat, "Windows");
               
  new G4PVPlacement(rotm, pos_win1, logicwin, "Windows1", logicalWorld, false, 0,  checkOverlaps);
  new G4PVPlacement(rotm, pos_win2, logicwin, "Windows2", logicalWorld, false, 0,  checkOverlaps); 
  
  //
  // The Guiders:  we will create 2 guiders here, the same;
  //   
  G4double guider_dza = 20./2.*mm, guider_dzb = 20./2.*mm;
  G4double guider_dya = 20./2.*mm, guider_dyb = 20./2.*mm;
  G4double guider_dx  = 12.*cm;  
  // Set guider material;
  G4Material* guider_mat = fMaterial->GetfPMT();
  
  // Set Position for guider;
  G4ThreeVector pos_Guider1 = G4ThreeVector((shape_x + 2*windows_dx + guider_dx), 0, 15.*mm);
  G4ThreeVector pos_Guider2 = G4ThreeVector((shape_x + 2*windows_dx + guider_dx), 0, -15.*mm);
  
  G4Trd* solidGuider =
    new G4Trd("guider",                      //its name
              guider_dza, guider_dzb, 
              guider_dya, guider_dyb, guider_dx); //its size
                
  // Set two logical volume;
  G4LogicalVolume* logicGuider = 
    new G4LogicalVolume(solidGuider, guider_mat, "Guider");
	
  // Place the guiders;
  new G4PVPlacement(rotm, pos_Guider1, logicGuider, "Guider1", logicalWorld, false, 0, checkOverlaps);
  new G4PVPlacement(rotm, pos_Guider2, logicGuider, "Guider2", logicalWorld, false, 0, checkOverlaps);
  
//  End of setting geometry for light guide;

  //构建 Al2O3
  shape_z1 =  22./2.*mm, shape_z2 = 22./2.*mm, shape_y1=86./2.*mm, shape_y2=145.5/2.*mm, shape_x=340.5/2.0*mm;
  G4Material* Al2O3 = fMaterial->Getfreflect();

  G4Trd* solid = new G4Trd("Al2O3", shape_z1, shape_z2,shape_y1,shape_y2, shape_x);
  G4SubtractionSolid* Al2O3solid = new G4SubtractionSolid("Trd-Trd",solid,solidDector,0,G4ThreeVector(-0.0*mm,-0.*mm,-1.*mm) );

  G4LogicalVolume* logicAl2O3 = new G4LogicalVolume(Al2O3solid, Al2O3, "Al2O3");

  pos1 = G4ThreeVector(-1.*mm, 0, -15.*mm),pos2 = G4ThreeVector(-1.*mm, 0., 15.*mm);

  //G4VPhysicalVolume* Al2O31phy =  new G4PVPlacement(rotm, pos1, logicAl2O3, "Al2O31", logicalWorld, false, 0, checkOverlaps);
  //G4VPhysicalVolume* Al2O32phy = new G4PVPlacement(rotm, pos2, logicAl2O3, "Al2O32", logicalWorld, false, 1, checkOverlaps);
  
  //边猜边看啊，师兄我看到这里都要疯啦！
  G4double fPolish = 1.;
  G4double fReflectivity = 1.;

  G4OpticalSurface* Al2O3Surface = new G4OpticalSurface("PhotonDetSurface",
  glisur,
  ground,
  dielectric_metal,
  fPolish);

  G4MaterialPropertiesTable* Al2O3SurfaceProperty =
  new G4MaterialPropertiesTable();

  G4double p_mppc[] = {1.70*eV, 3.47*eV};
  const G4int nbins = sizeof(p_mppc)/sizeof(G4double);
  G4double refl_mppc[] = {fReflectivity,fReflectivity};
  assert(sizeof(refl_mppc) == sizeof(p_mppc));
  G4double effi_mppc[] = {1, 1};
  assert(sizeof(effi_mppc) == sizeof(p_mppc));

  Al2O3SurfaceProperty->AddProperty("REFLECTIVITY",p_mppc,refl_mppc,nbins);
  Al2O3SurfaceProperty->AddProperty("EFFICIENCY",p_mppc,effi_mppc,nbins);

  Al2O3Surface->SetMaterialPropertiesTable(Al2O3SurfaceProperty);

  new G4LogicalSkinSurface("Al2O3Surface",logicAl2O3,Al2O3Surface);

}

void muonDetectorConstruction::ConstructPMT(G4LogicalVolume* logicalWorld)
{

  G4Material* Quartz = fMaterial->GetfPMT();

  G4double PMT_thick   =   1.0*mm; // Thickness of PMT window
  G4double PMT_x    =  20./2.*mm, PMT_y=84./2.*mm; // Radius of curvature of PMT window
  G4ThreeVector PMTpos1 = G4ThreeVector(340.5/2.0*mm,0.0*cm,15 *mm);
  G4ThreeVector PMTpos2 = G4ThreeVector(340.5/2.0*mm,0.0*cm,-15 *mm);

  G4double phi=90.*deg;
  G4ThreeVector u = G4ThreeVector(std::cos(phi),0., -std::sin(phi));
  G4ThreeVector v = G4ThreeVector(0.,1., 0.);
  G4ThreeVector w = G4ThreeVector( std::sin(phi),0., std::cos(phi));
  G4RotationMatrix* rotm = new G4RotationMatrix(u, v, w);

  G4Box* solidPMT = new G4Box("PMT_solid",PMT_x,PMT_y,PMT_thick);
  G4LogicalVolume* logicalPMT = new G4LogicalVolume(solidPMT,Quartz,"PMT_log",0,0,0);
  
  G4Colour green (0.0, 1.0, 0.0) ; // green
  G4VisAttributes* PMTVisAtt= new G4VisAttributes(green);
  logicalPMT->SetVisAttributes(PMTVisAtt);
  
  new G4PVPlacement(rotm,PMTpos1,logicalPMT,"PMT1",logicalWorld,false,0,checkOverlaps);
  new G4PVPlacement(rotm,PMTpos2,logicalPMT,"PMT2",logicalWorld,false,1,checkOverlaps);

  G4double fPolish = 0.;
  G4double fReflectivity = 0.;

  G4OpticalSurface* photonDetSurface = new G4OpticalSurface("PhotonDetSurface",
  glisur,
  ground,
  dielectric_metal,
  fPolish);

  G4MaterialPropertiesTable* photonDetSurfaceProperty =
  new G4MaterialPropertiesTable();

  G4double p_mppc[] = 
  {
    1.70*eV,1.73*eV,1.76*eV,1.79*eV,1.82*eV,
    1.85*eV,1.88*eV,1.91*eV,1.94*eV,1.97*eV,
    2.00*eV,2.03*eV,2.06*eV,2.09*eV,2.12*eV,
    2.15*eV,2.18*eV,2.21*eV,2.24*eV,2.27*eV,
    2.30*eV,2.33*eV,2.36*eV,2.39*eV,2.42*eV,
    2.45*eV,2.48*eV,2.51*eV,2.54*eV,2.57*eV,
    2.60*eV,2.63*eV,2.66*eV,2.69*eV,2.72*eV,
    2.75*eV,2.78*eV,2.81*eV,2.84*eV,2.87*eV,
    2.90*eV,2.93*eV,2.96*eV,2.99*eV,3.02*eV,
    3.05*eV,3.08*eV,3.11*eV,3.14*eV,3.17*eV,
    3.20*eV,3.23*eV,3.26*eV,3.29*eV,3.32*eV,
    3.35*eV,3.38*eV,3.41*eV,3.44*eV,3.47*eV};

  const G4int nbins = sizeof(p_mppc)/sizeof(G4double);
  G4double refl_mppc[] = 
  {fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,
    fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,
    fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,
    fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,
    fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,
    fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity,fReflectivity};

  assert(sizeof(refl_mppc) == sizeof(p_mppc));
  G4double effi_mppc[] =    
  {1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1};
  assert(sizeof(effi_mppc) == sizeof(p_mppc));

  photonDetSurfaceProperty->AddProperty("REFLECTIVITY",p_mppc,refl_mppc,nbins);
  photonDetSurfaceProperty->AddProperty("EFFICIENCY",p_mppc,effi_mppc,nbins);

  photonDetSurface->SetMaterialPropertiesTable(photonDetSurfaceProperty);

  new G4LogicalSkinSurface("PhotonDetSurface",logicalPMT,photonDetSurface);
}

#include "EnergyTimeSD.hh"
#include "pmtSD.hh"
// 设置敏感探测器 记录 能量沉积 位置
#include <G4SDManager.hh>
#include <G4MultiFunctionalDetector.hh>
#include <G4PSEnergyDeposit.hh>
#include <G4VPrimitiveScorer.hh>
void muonDetectorConstruction::ConstructSDandField()
{
//	注册敏感探测器；
  G4SDManager* sdManager = G4SDManager::GetSDMpointer();
  sdManager->SetVerboseLevel(2);

  EnergyTimeSD* muondectorEn = new EnergyTimeSD("muondectorEn");
  SetSensitiveDetector("muondector",muondectorEn);
  sdManager->AddNewDetector(muondectorEn);

  pmtSD*  PMT_ET = new pmtSD("PMT_ET");
  SetSensitiveDetector("PMT_log",PMT_ET);
  sdManager->AddNewDetector(PMT_ET);

}
