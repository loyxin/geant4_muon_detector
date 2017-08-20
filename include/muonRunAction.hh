// 作用：设置 run action
// 暂无
#ifndef MUONRUNACTION_HH
#define MUONRUNACTION_HH

#include <G4UserRunAction.hh>
#include <G4Run.hh>
#include <G4ParticleDefinition.hh>
#include <G4Accumulable.hh>

class G4Run;

class muonRunAction : public G4UserRunAction
{
  public:
    muonRunAction();
    virtual ~muonRunAction();

    virtual void EndOfRunAction(const G4Run* run);

};

#endif
