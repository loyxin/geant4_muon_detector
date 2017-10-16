/**
 * @file muonEventAction.cc
 * @brief 输出数据到 csv 文件
 * @author loyxin
 * @version 1.0
 * @date 2017-09-10
 */
#include "muonEventAction.hh"

#include <G4SDManager.hh>
#include <G4THitsMap.hh>
#include <G4SystemOfUnits.hh>
#include <G4Event.hh>

#include "Analysis.hh"
#include "EnergyTimeHit.hh"
#include "PMThit.hh"
using namespace std;

muonEventAction::muonEventAction() : G4UserEventAction()
{}

muonEventAction::~muonEventAction()
{}
/**
 * @brief 获得敏感探测器的 id, 输出数据
 * 
 */
void muonEventAction::EndOfEventAction(const G4Event* event)
{
    G4int eventID = event->GetEventID();

    G4cout << "--------------End of EventAction--------------"<<eventID<<G4endl;

    G4SDManager* sdm = G4SDManager::GetSDMpointer();
    G4AnalysisManager* analysis = G4AnalysisManager::Instance();

    G4HCofThisEvent* hcofEvent = event->GetHCofThisEvent();

    if(!hcofEvent) return;

    if(muondetectorEnId < 0)
    {
      muondetectorEnId = sdm->GetCollectionID("muondectorEn/energy_time");
      G4cout << "EventAction: muonDetector energy scorer ID: " << muondetectorEnId << G4endl;

    }

    if( PMT_Id < 0)
    {
      PMT_Id = sdm->GetCollectionID("PMT_ET/pmt_energy_time");
      G4cout << "EventAction: PMT pmt_energy_time scorer ID: " << PMT_Id << G4endl;
    }
    if( PMT_Id > 0 )
    {

        pmtHitsCollection* hitCollection =
        dynamic_cast<pmtHitsCollection*>(hcofEvent->GetHC(PMT_Id));

        if (hitCollection)
        {
            for (auto hit: *hitCollection->GetVector())
            {
                /**
                * @details 第一列 能量 第二列 时间 第三列 如果是 探测器 ‘PMT1' 则为 1， 探测器 ’PMT2‘ 则为 2
                * 第四列 event id
                */

                analysis->FillNtupleDColumn(1, 0, hit->GetDeltaEnergy() / MeV);
                analysis->FillNtupleDColumn(1,1, hit->GetTime() / ns);
                if(hit->GetName()=="PMT1") // value 1
                    analysis->FillNtupleDColumn(1,2,1);
                if(hit->GetName()=="PMT2") //value 2
                    analysis->FillNtupleDColumn(1,2,2);

                analysis->FillNtupleDColumn(1,3, eventID);
                analysis->AddNtupleRow(1);
            }
        }

    }

    if( muondetectorEnId > -1 )
    {

        EnergyTimeHitsCollection* muhitCollection =
        dynamic_cast<EnergyTimeHitsCollection*>(hcofEvent->GetHC(muondetectorEnId));

        if (muhitCollection)
        {
            for (auto hit: *muhitCollection->GetVector())
            {
                /**
                * @details 第一列 能量 第二列 深度信息 第三列 如果是 探测器 ‘muondector1' 则为 1， 探测器 ’muondector2‘ 则为 2
                * 第四列 event id
                */
                analysis->FillNtupleDColumn(2, 0, hit->GetDeltaEnergy() / MeV);
                G4ThreeVector position = hit->GetPosition();
                analysis->FillNtupleDColumn(2,1, position.getZ() / mm);
                analysis->FillNtupleDColumn(2,3, eventID);
                if(hit->GetName()=="muondector1")
                    analysis->FillNtupleDColumn(2,2,1);
                if(hit->GetName()=="muondector2")
                    analysis->FillNtupleDColumn(2,2,2);
                analysis->AddNtupleRow(2);
            }
        }
   
    }

}
