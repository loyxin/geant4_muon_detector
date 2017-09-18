/**
 * @file EnergyTimeSD.hh
 * @brief 探测器的敏感探测器类
 * @author loyxin
 * @version 1.0
 * @date 2017-09-10
 */
#ifndef ENERGYTIMESD_HH
#define ENERGYTIMESD_HH

#include <G4VSensitiveDetector.hh>

#include "EnergyTimeHit.hh"

class EnergyTimeSD : public G4VSensitiveDetector
{
public:
<<<<<<< HEAD
    /**
    * @brief  构造函数 探测器hit collection名字设置
    * @details 注册管理类时插入 energy_time
    * 
    * @param name 敏感探测器的名字
    */
=======
>>>>>>> parent of 1c568a5... add doxygen
    EnergyTimeSD(G4String name);

    void Initialize(G4HCofThisEvent*) override;

protected:
<<<<<<< HEAD
	/**
	 * @brief 击中敏感探测器处理
	 * @details 保存 muon 的时间，能量，位置，和击中的探测器的名字
	 */
=======
>>>>>>> parent of 1c568a5... add doxygen
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist) override;

private:
    EnergyTimeHitsCollection* fHitsCollection { nullptr };
<<<<<<< HEAD
    /** 
     * @brief 默认 id = -1, 如果 id = -1 说明还没有向管理类注册 Hit 容器
     */
=======
>>>>>>> parent of 1c568a5... add doxygen
    G4int fHitsCollectionId { -1 };
};

#endif
