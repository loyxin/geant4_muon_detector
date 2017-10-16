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

    G4StepPoint* thePrePoint  = aStep->GetPreStepPoint();
    G4StepPoint* thePostPoint = aStep->GetPostStepPoint();

    G4VPhysicalVolume* thePrePV  = thePrePoint->GetPhysicalVolume();
    G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();

    G4String thePrePVname  = " ";
    G4String thePostPVname = " ";

    if (thePostPV) {
        thePrePVname  = thePrePV->GetName();
        thePostPVname = thePostPV->GetName();
     }

     if(thePostPVname!="PMT1" && thePostPVname!="PMT2" && 
     thePrePVname!="PMT1" && thePrePVname!="PMT2" ) return false;

     

     PMThit* hit = new PMThit();

     G4double aDep = aStep->GetTotalEnergyDeposit();
     G4double time = aStep->GetPostStepPoint()->GetGlobalTime();
     G4ThreeVector position = aStep->GetPostStepPoint()->GetPosition();
     G4String name = aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName();

    if(thePostPVname=="PMT1"|| thePostPVname=="PMT2") {
        hit->SetTime(time);
        hit->SetDeltaEnergy(aDep);
        hit->SetPosition(position);
        hit->SetName(thePostPVname);
    }

    if(thePrePVname=="PMT1"|| thePrePVname=="PMT2") {
        hit->SetTime(time);
        hit->SetDeltaEnergy(aDep);
        hit->SetPosition(position);
        hit->SetName(thePrePVname);
    }

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
