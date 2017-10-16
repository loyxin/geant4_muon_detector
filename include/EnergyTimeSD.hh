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
/**
 * @brief 探测器的敏感探测器类
 */
class EnergyTimeSD : public G4VSensitiveDetector
{
public:
    /**
    * @brief  构造函数 探测器hit collection名字设置
    * @details 注册管理类时插入 energy_time
    * 
    * @param name 敏感探测器的名字
    */
    EnergyTimeSD(G4String name);
    /**
     * @brief 初始化敏感探测器
     * @details 将敏感探测器的 id 和 Hit 容器注册到敏感探测器管理类中
     */
    void Initialize(G4HCofThisEvent*) override;

protected:
	/**
	 * @brief 击中敏感探测器处理
	 * @details 保存 muon 的时间，能量，位置，和击中的探测器的名字
	 */
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist) override;

private:
    EnergyTimeHitsCollection* fHitsCollection { nullptr };
    /** 
     * @brief 默认 id = -1, 如果 id = -1 说明还没有向管理类注册 Hit 容器
     */
    G4int fHitsCollectionId { -1 };
};

#endif
