/**
 * @file PMTSD.cc
 * @brief 设置敏感探测器保存哪些数据
 * @details muon 击中 pmt ，保存时间，能量，位置和击中哪一个 pmt 信息
 * 敏感探测器挂载在敏感探测器管理类格式为 name/pmt_energy_time
 * @author loyxin
 * @version 1.0
 * @date 2017-09-10
 */
#include "PMTSD.hh"

#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>
/**
 * @brief 设置敏感探测器保存哪些数据
 * @details muon 击中 pmt ，保存时间，能量，位置和击中哪一个 pmt 信息
 * 敏感探测器挂载在敏感探测器管理类格式为 name/pmt_energy_time
 * @param name pmt 的名字
 */

PMTSD::PMTSD(G4String name) :
  G4VSensitiveDetector(name)
{
    collectionName.insert("pmt_energy_time");
}
#include <G4OpticalPhoton.hh>


G4bool PMTSD::ProcessHits(G4Step* aStep, G4TouchableHistory* /*ROhist*/)
{

    if (aStep == NULL) return false;

    G4Track* theTrack = aStep->GetTrack();
    
    if(theTrack->GetDefinition()
    !=G4OpticalPhoton::OpticalPhoton() ) return false;// 确定是否是光子
    

    PMThit* hit = new PMThit();

    G4double Energy = aStep->GetPreStepPoint()->GetTotalEnergy();
    G4double time = aStep->GetPreStepPoint()->GetGlobalTime();
    G4ThreeVector position = aStep->GetPreStepPoint()->GetPosition();
    G4String name;
    G4int number = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo();
    G4cout<<number<<G4endl;

    hit->SetTime(time);
    hit->SetDeltaEnergy(Energy);
    hit->SetPosition(position);
    if(number==2)
        name = "PMT2";
    else
        name = "PMT1";
    hit->SetName(name);


    fHitsCollection->insert(hit);
    
    return true;
}

void PMTSD::Initialize(G4HCofThisEvent* hcof)
{
    fHitsCollection = new pmtHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fHitsCollectionId < 0)
    {
        fHitsCollectionId = G4SDManager::GetSDMpointer()->GetCollectionID(GetName() + "/" + collectionName[0]);
    }
    hcof->AddHitsCollection(fHitsCollectionId, fHitsCollection);
}
