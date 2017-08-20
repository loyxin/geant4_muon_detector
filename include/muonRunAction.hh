// 作用：设置 run action
// 暂无
#ifndef MUONRUNACTION_HH
#define MUONRUNACTION_HH

#include "G4UserRunAction.hh"

class G4Run;

class muonRunAction : public G4UserRunAction
{
  public:
    muonRunAction();
    virtual ~muonRunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

};

#endif
