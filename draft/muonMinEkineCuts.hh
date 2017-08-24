// 继承muonSpecialCuts

#ifndef MUONMINEKINECUTS_HH
#define MUONMINEKINECUTS_HH

#include <G4ios.hh>
#include <globals.hh>
#include "muonSpecialCuts.hh"


class muonMinEkineCuts : public muonSpecialCuts
{
  public:

     muonMinEkineCuts(const G4String& processName ="muonMinEkineCuts" );

     virtual ~muonMinEkineCuts();

     // PostStep GPIL
     virtual G4double PostStepGetPhysicalInteractionLength(
                             const G4Track& track,
                             G4double   previousStepSize,
                             G4ForceCondition* condition
                            );


  private:

  // hide assignment operator as private
      muonMinEkineCuts(muonMinEkineCuts&);
      muonMinEkineCuts& operator=(const muonMinEkineCuts& right);

};

#endif // MUONMINEKINECUTS_HH
