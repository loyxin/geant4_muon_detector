// 作用：设置Event action
// 暂无
#ifndef MUONEVENTACTION_HH
#define MUONEVENTACTION_HH

#include <G4UserEventAction.hh>
#include <globals.hh>

class muonRunAction;

class muonEventAction : public G4UserEventAction
{
  public:
    muonEventAction();
    virtual ~muonEventAction();

    virtual void EndOfEventAction(const G4Event* anEvent) override;
	private:

		G4int muondetectorEnId { -1 };
    G4int PMT_Id{-1};
};

#endif
