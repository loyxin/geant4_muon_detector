// 作用：构建 physics list 参考underground physics
#ifndef MUONPHYSICS
#define MUONPHYSICS

#include <G4VUserPhysicsList.hh>
#include <globals.hh>


#include "G4OpWLS.hh"
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"

#include "G4OpMieHG.hh"
#include "G4OpRayleigh.hh"
#include "G4OpAbsorption.hh"
#include "G4OpBoundaryProcess.hh"

#include "G4VPhysicsConstructor.hh"
#include "G4LossTableManager.hh"

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

  private:

    G4OpWLS*             fWLSProcess;
    G4Cerenkov*          fCerenkovProcess;
    G4Scintillation*     fScintProcess;
    G4OpAbsorption*      fAbsorptionProcess;
    G4OpRayleigh*        fRayleighScattering;
    G4OpMieHG*           fMieHGScatteringProcess;
    G4OpBoundaryProcess* fBoundaryProcess;
 
    G4bool fAbsorptionOn;

  public:
    G4OpWLS* GetWLSProcess() {return fWLSProcess;}
    G4Cerenkov* GetCerenkovProcess() {return fCerenkovProcess;}
    G4Scintillation* GetScintillationProcess() {return fScintProcess;}
    G4OpAbsorption* GetAbsorptionProcess() {return fAbsorptionProcess;}
    G4OpRayleigh* GetRayleighScatteringProcess() {return fRayleighScattering;}
    G4OpMieHG* GetMieHGScatteringProcess() {return fMieHGScatteringProcess;}
    G4OpBoundaryProcess* GetBoundaryProcess() { return fBoundaryProcess;}

    void SetNbOfPhotonsCerenkov(G4int);

};

#endif
