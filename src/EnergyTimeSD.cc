/**
 * @brief 设置敏感探测器保存哪些数据
 * @details muon 击中敏感探测器，保存时间，能量，位置和击中哪一个探测器信息
 * 敏感探测器挂载在敏感探测器管理类格式为 name/energy_time
 */
#include "EnergyTimeSD.hh"

#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>
/**
 * @brief 敏感探测器名字设置
 * @details 注册管理类时插入 energy_time
 * 
 * @param name 敏感探测器的名字
 */
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
  
    //判断是否是 muon 子
    if(theTrack->GetDefinition()
       !=G4MuonMinus::MuonMinus() && theTrack->GetDefinition()
       !=G4MuonPlus::MuonPlus() ) return false;
    
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
    //注册 Hit collection 
    fHitsCollection = new EnergyTimeHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fHitsCollectionId < 0)
    {
        fHitsCollectionId = G4SDManager::GetSDMpointer()->GetCollectionID(GetName() + "/" + collectionName[0]);
    }
    hcof->AddHitsCollection(fHitsCollectionId, fHitsCollection);
}
