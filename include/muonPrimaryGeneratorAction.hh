/**
 * @file muonPrimaryGeneratorAction.hh
 * @brief 设置 Gun 的参数
 * @author loyxin
 * @version 1.0
 * @date 2017-09-10
 */
#ifndef MUONPRIMARYGENERATORACTION_HH
#define MUONPRIMARYGENERATORACTION_HH

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>

class G4Event;
class G4ParticleGun;

class muonPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    // 初始化 fParticleGun 设置默认参数
    // mu- 方向 0 0 -1 能量 4 GeV
    /**
     * @brief 初始化 fParticleGun 设置默认参数
     * @details 设置枪打出 mu- 方向 0 0 -1 能量 150 MeV
     */
    muonPrimaryGeneratorAction();
    virtual ~muonPrimaryGeneratorAction();
    // 设置 event 开始的 fParticleGun 的位置
    /**
     * @brief 设置 event 开始的 fParticleGun 的位置
     * @details 0 0 0.1m
     */
    virtual void GeneratePrimaries(G4Event* anEvent) override;

    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
private:
    G4ParticleGun* fParticleGun;
};


#endif
