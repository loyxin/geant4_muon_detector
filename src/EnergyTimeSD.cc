<<<<<<< HEAD
/**
 * @file EnergyTimeSD.cc
 * @brief 设置敏感探测器保存哪些数据
 * @details muon 击中敏感探测器，保存时间，能量，位置和击中哪一个探测器信息
 * 敏感探测器挂载在敏感探测器管理类格式为 name/energy_time
 * @author loyxin
 * @version 1.0
 * @date 2017-09-10
 */
=======
>>>>>>> parent of 1c568a5... add doxygen
#include "EnergyTimeSD.hh"

#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>

EnergyTimeSD::EnergyTimeSD(G4String name) :
  G4VSensitiveDetector(name)
{
    collectionName.insert("energy_time");
}
#include <G4OpticalPhoton.hh>
#include <G4MuonPlus.hh>
#include <G4MuonMinus.hh>
G4bool EnergyTimeSD::ProcessHits(G4Step* aStep, G4TouchableHistory* /*ROhist*/)
{
    if (aStep == NULL) return false;
    G4Track* theTrack = aStep->GetTrack();
  
<<<<<<< HEAD
    
=======

>>>>>>> parent of 1c568a5... add doxygen
    if(theTrack->GetDefinition()
       !=G4MuonMinus::MuonMinus() && theTrack->GetDefinition()
       !=G4MuonPlus::MuonPlus() ) return false;//判断是否是 muon 子
    
    G4double aDep = aStep->GetTotalEnergyDeposit();
    G4double time = aStep->GetPostStepPoint()->GetGlobalTime();
    G4ThreeVector position = aStep->GetPostStepPoint()->GetPosition();
    G4String name = aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName();

    EnergyTimeHit* hit = new EnergyTimeHit();
    hit->SetTime(time);
    hit->SetDeltaEnergy(aDep);
    hit->SetPosition(position);
    hit->SetName(name);

    fHitsCollection->insert(hit);

    return true;
}

void EnergyTimeSD::Initialize(G4HCofThisEvent* hcof)
{
<<<<<<< HEAD
     
=======
>>>>>>> parent of 1c568a5... add doxygen
    fHitsCollection = new EnergyTimeHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fHitsCollectionId < 0)
    {
        fHitsCollectionId = G4SDManager::GetSDMpointer()->GetCollectionID(GetName() + "/" + collectionName[0]);
    }
    hcof->AddHitsCollection(fHitsCollectionId, fHitsCollection);//注册 Hit collection
}
