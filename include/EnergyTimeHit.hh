/**
 * @file EnergyTimeHit.hh
 * @brief 设置 muon detector Hit 容器
 * @details Hit 容器保存能量，时间，位置，探测器名字
 * @author loyxin
 * @version 1.0
 * @date 2017-09-10
 */
#ifndef ENERGYTIMEHIT_HH
#define ENERGYTIMEHIT_HH

#include <G4VHit.hh>
#include <G4THitsMap.hh>
#include <G4ThreeVector.hh>
/**
 * @brief 设置 muon detector Hit 容器
 * @details Hit 容器保存能量，时间，位置，探测器名字
 */
class EnergyTimeHit : public G4VHit
{
public:
    /**
     * @brief Memory allocation and de-allocation
     */
    inline void* operator new(size_t);
    inline void  operator delete(void*);
    /**
     * @brief 设置能量
     * @param deltaE 在 sensitive类中的ProcessHit()中的从step得到
     */
    void SetDeltaEnergy(G4double deltaE) { fDeltaEnergy = deltaE; }
    /**
     * @brief 设置时间
     * @param time 在 sensitive类中的ProcessHit()中的从step得到
     */
    void SetTime(G4double time) { fTime = time; }
    /**
     * @brief 设置位置
     * @param pos 在 sensitive类中的ProcessHit()中的从step得到
     */
    void SetPosition(G4ThreeVector pos) { fPosition = pos; }
    /**
     * @brief 设置探测器名字
     * @details 因为有两个探测器用一个 logical Volume 所以用这个标记
     * @param name 在 sensitive类中的ProcessHit()中的从step得到
     */
    void SetName(G4String name){fname=name;}
    /**
     * @brief 得到 hit 中能量信息
     * @details 在 eventAction 有用到
     */
    G4double GetDeltaEnergy() const { return fDeltaEnergy; }
    /**
     * @brief 得到 hit 中时间信息
     * @details 在 eventAction 有用到
     */
    G4double GetTime() const { return fTime; }
    /**
     * @brief 得到 hit 中位置信息
     * @details 在 eventAction 有用到
     */
    G4ThreeVector GetPosition() const { return fPosition; }
    /**
     * @brief 得到 hit 中探测器信息
     * @details 在 eventAction 有用到
     */
    G4String GetName()const{return fname;}
private:
    G4double fDeltaEnergy;//保存能量
    G4double fTime;//保存时间
    G4ThreeVector fPosition;//保存位置
    G4String fname;//保存探测器名字
};

using EnergyTimeHitsCollection 
    = G4THitsCollection<EnergyTimeHit>;// 方便写代码，用EnergyTimeHitsCollection告诉是这个 energytime 的 hit

extern G4ThreadLocal G4Allocator<EnergyTimeHit> *hitAllocator;

inline void* EnergyTimeHit::operator new(size_t)
{
  if (!hitAllocator)
  {
      hitAllocator = new G4Allocator<EnergyTimeHit>;
  }
  return hitAllocator->MallocSingle();
}

inline void EnergyTimeHit::operator delete(void *aHit)
{
    if (!hitAllocator)
    {
        hitAllocator = new G4Allocator<EnergyTimeHit>;
    }
    hitAllocator->FreeSingle((EnergyTimeHit*) aHit);
}

#endif
