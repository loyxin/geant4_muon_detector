#ifndef MUONMATERIAL_HH 
#define MUONMATERIAL_HH 1

#include "globals.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

class muonMaterial{
public:
    muonMaterial();
    ~muonMaterial();
    static muonMaterial* GetInstance();
    G4Material* GetMaterial(const G4String);
    G4Material* Getfdetector(){return fdetector;}
    G4Material* GetfPMT(){return fPMT;}
    G4Material* Getfreflect(){return freflect;}
    G4Material* GetfAir(){return fAir;}
private:  
    void CreateMaterials();

private:

    static muonMaterial* fInstance;

    G4NistManager*     fNistMan;

    G4Material*        fdetector;
    G4Material*        fPMT;
    G4Material*        freflect;
    G4Material*        fAir;
};


#endif