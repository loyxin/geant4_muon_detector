/**
 * @file muonSteppingAction.hh
 * @brief stepping action 暂时没有做什么动作
 * @author loyxin
 * @version 1.0
 * @date 2017-09-10
 */
#ifndef MUONSTEPPINGACTION_h
#define MUONSTEPPINGACTION_h 1

#include <G4UserSteppingAction.hh>
#include <globals.hh>

class muonEventAction;
/**
   @brief stepping action 暂时没有做什么动作
  */
class muonSteppingAction : public G4UserSteppingAction
{
  public:
    muonSteppingAction(muonEventAction*  eventAction);
    virtual ~muonSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    muonEventAction*  fEventAction;
};

#endif