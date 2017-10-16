#include "muonMaterial.hh"
#include <G4SystemOfUnits.hh>
#include <G4MaterialPropertiesTable.hh>

muonMaterial* muonMaterial::fInstance=0;

muonMaterial::muonMaterial(){
    fNistMan = G4NistManager::Instance();

    fNistMan->SetVerbose(2);

    CreateMaterials();
}

muonMaterial::~muonMaterial(){
    delete fdetector;
    delete fPMT;
    delete freflect;
    delete fPMMA;
}

muonMaterial* muonMaterial::GetInstance(){
    if (fInstance == 0)
    {
      fInstance = new muonMaterial();
    }
  return fInstance;
}


G4Material* muonMaterial::GetMaterial(const G4String material){

    G4Material* mat =  fNistMan->FindOrBuildMaterial(material);

    if (!mat) mat = G4Material::GetMaterial(material);
    if (!mat) 
    {
        std::ostringstream o;
        o << "Material " << material << " not found!";
        G4Exception("MuonMaterial::GetMaterial","",
                    FatalException,o.str().c_str());
    }

  return mat;
}

#include <G4Element.hh>
void muonMaterial::CreateMaterials(){
    // Materials Definition
    // Air world
    fAir = fNistMan->FindOrBuildMaterial("G4_AIR");

    // detector C_10 H_14
    fdetector=new G4Material("anthracene",1.25*g/cm3,2);

    G4Element* elH=new G4Element("Hydrogen","H",1.,1.01*g/mole);
    G4Element* elC=new G4Element("Carbon","C",6.,12.01*g/mole);
  
    fdetector->AddElement(elH,10);
    fdetector->AddElement(elC,14);

    // Get nist material manager
  
    // Ready for PMMA;
    G4NistManager* nist = G4NistManager::Instance();
    
    // Prepare for PMMA;
    std::vector<G4int> natoms;
    std::vector<G4String> elements;
    
    elements.push_back("C");     natoms.push_back(5);
    elements.push_back("H");     natoms.push_back(8);
    elements.push_back("O");     natoms.push_back(2);
    
    fPMMA = nist->ConstructNewMaterial("PMMA", elements, natoms, 1.190*g/cm3);
	
    // PMT 	
    fPMT = fNistMan->FindOrBuildMaterial("G4_Pyrex_Glass");


    // freflection
    freflect = fNistMan->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");


    //
    // ------------ Generate & Add Material Properties Table ------------
    //
    //737 nm - 356 nm
    G4double photonEnergy[] =
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

    nEntries = sizeof(photonEnergy)/sizeof(G4double);

    //--------------------------------------------------
    // Air
    //--------------------------------------------------

    G4double refractiveIndex[] =
    { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00};

    assert(sizeof(refractiveIndex) == sizeof(photonEnergy));


    G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();

    mpt->AddProperty("RINDEX", photonEnergy, refractiveIndex, nEntries);

    fAir->SetMaterialPropertiesTable(mpt);

    //--------------------------------------------------
    // freflection Al2O3
    //--------------------------------------------------

	
	G4double Al2O3refractiveIndex[60];
	for(int i=0; i<60; i++){
		Al2O3refractiveIndex[i] = 1.76;
	}

    assert(sizeof(Al2O3refractiveIndex) == sizeof(photonEnergy));
	
	G4double absAl2O3[60];
	for(int i=0; i<60; i++){
		absAl2O3[i] = 1.0*m;
	}
	
    
    assert(sizeof(absAl2O3) == sizeof(photonEnergy));

    G4MaterialPropertiesTable* mptAl2O3 = new G4MaterialPropertiesTable();
    mptAl2O3->AddProperty("RINDEX", photonEnergy, Al2O3refractiveIndex, nEntries);
    mptAl2O3->AddProperty("ABSLENGTH",photonEnergy,absAl2O3,nEntries);

    freflect ->SetMaterialPropertiesTable(mptAl2O3);

    //--------------------------------------------------
    // detector C_10 H_14
    //--------------------------------------------------  
    G4double C10H14refractiveIndex[] =
    { 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3,
        1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3,
        1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3,
        1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3,
        1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3,
        1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3};

    assert(sizeof(C10H14refractiveIndex) == sizeof(photonEnergy));
    
    G4double absC10H14[] =
    {3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,
        3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,
        3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,
        3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,
        3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,
        3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m,3.0*m};
  
    assert(sizeof(absC10H14) == sizeof(photonEnergy));

    G4MaterialPropertiesTable* mptC10H14 = new G4MaterialPropertiesTable();
    mptC10H14->AddProperty("RINDEX", photonEnergy, C10H14refractiveIndex, nEntries);
    mptC10H14->AddProperty("ABSLENGTH",photonEnergy,absC10H14,nEntries);
    mptC10H14->AddConstProperty("SCINTILLATIONYIELD",10./keV);
    mptC10H14->AddConstProperty("RESOLUTIONSCALE",1.0);
    mptC10H14->AddConstProperty("FASTTIMECONSTANT", 10.*ns);

    fdetector->SetMaterialPropertiesTable(mptC10H14);  

    // --------------------------------------------------
    // PMT 
    // -------------------------------------------------- 
    G4double SiO2refractiveIndex[] =
    { 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3,
        1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3,
        1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3,
        1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3,
        1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3,
        1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3};

    assert(sizeof(SiO2refractiveIndex) == sizeof(photonEnergy));
    
    G4MaterialPropertiesTable* mptSiO2 = new G4MaterialPropertiesTable();
    mptSiO2->AddProperty("RINDEX", photonEnergy, SiO2refractiveIndex, nEntries);
    mptSiO2->AddProperty("ABSLENGTH", photonEnergy, absC10H14, nEntries);
    mptSiO2->AddConstProperty("SCINTILLATIONYIELD",10./keV);
    mptSiO2->AddConstProperty("RESOLUTIONSCALE",1.0);
    mptSiO2->AddConstProperty("FASTTIMECONSTANT", 10.*ns);

    fPMT ->SetMaterialPropertiesTable(mptSiO2);     
}