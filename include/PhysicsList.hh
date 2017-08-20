#ifndef PhysicsList_hh
#define PhysicsList_hh

#include "G4VModularPhysicsList.hh"

class G4VPhysicsConstructor;
class G4StepLimiter;

class PhysicsList: public G4VModularPhysicsList
{
public:
  // 初始化 private 变量
  // 注册一些 physics list
  PhysicsList();
  virtual ~PhysicsList();

  void ConstructParticle();
  // 设置不同粒子的 cut
  // 调用 SetCutFor(Gamma Electron positron) 函数
  void SetCuts();
  void SetCutForGamma(G4double);
  void SetCutForElectron(G4double);
  void SetCutForPositron(G4double);

  //构建 process
  void ConstructProcess();

  void AddStepMax();
  G4StepLimiter* GetStepMaxProcess() {return fStepMaxProcess;};

private:

  G4double fCutForGamma;
  G4double fCutForElectron;
  G4double fCutForPositron;


  G4StepLimiter* fStepMaxProcess;

};


#endif
