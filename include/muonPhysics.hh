// 作用：构建 physics list 参考underground physics
#ifndef MUONPHYSICS
#define MUONPHYSICS

#include <G4VUserPhysicsList.hh>
#include <globals.hh>

class muonPhysics: public G4VUserPhysicsList
{
public:
  // 初始化 private 变量
  muonPhysics();
  ~muonPhysics();

public:
  // 设置不同粒子的 Cuts
  virtual void SetCuts();


protected:
  // Construct particle and physics
  // 调用 private 的各个构建粒子函数
  virtual void ConstructParticle();
  // 调用 Construct （General EM Had op）AddTransportation 函数
  // 构建 process
  virtual void ConstructProcess();

  // these methods Construct physics processes and register them
  virtual void ConstructGeneral();
  virtual void ConstructEM();
  virtual void ConstructHad();
  virtual void ConstructOp();

  // 调用 muonMaxTimeCuts muonMinEkineCuts
  virtual void AddTransportation();

private:
  G4int VerboseLevel;
  G4int OpVerbLevel;

  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;

  // these methods Construct particles
  void ConstructMyBosons();
  void ConstructMyLeptons();
  void ConstructMyHadrons();
  void ConstructMyShortLiveds();

};

#endif
