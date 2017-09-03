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
	 * @brief 构造函数
	 * @details 探测器名字设置
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
	 * @details 将数据保存到 Hit 容器
	 */
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist) override;

private:
    EnergyTimeHitsCollection* fHitsCollection { nullptr };
    // 默认 id = -1, 如果 id = -1 说明还没有向管理类注册 Hit 容器
    G4int fHitsCollectionId { -1 };
};

#endif
