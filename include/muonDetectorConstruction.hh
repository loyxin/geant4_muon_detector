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
#include "globals.hh"

#include "G4RunManager.hh"

#include "G4tgbVolumeMgr.hh"
#include "G4tgrMessenger.hh"

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
     * @brief 注册敏感探测器
     * @details 注册 pmt(PMTSD) muon detector(EnergyTimeSD) 敏感探测器
     */
    void ConstructSDandField() override;
private:
  G4tgrMessenger* fMessenger;

};

#endif
